#include "main.h"
#include "ws2812b.h"

extern TIM_HandleTypeDef htim1;					//makes htim1 a global variable


uint8_t LED_data[NUM_OF_LEDS][3];				// Stores RGB decimal RGB values for each LED
uint16_t PWM_DCL[24 * NUM_OF_LEDS + 50];		// 24 bits (each RGB color has 8 bits) + 50 as the reset signal after all data for the LEDs are sent, holds the DCL value for each bit
uint8_t PWM_completed = 0;


/*
 * Sets the input values into the LED_data array
 * Parameters:
 * LED_index - index of the LED
 * Red 	   - value of Red (0 - 255)
 * Green     - value of Green (0 - 255)
 * Blue	   - value of Blue (0 - 255)
*/
void set_LED_color(int LED_index,uint8_t Red, uint8_t Green, uint8_t Blue){
	LED_data[LED_index][0] = Red;
	LED_data[LED_index][1] = Green;
	LED_data[LED_index][2] = Blue;
}

/*
 * Puts the data into correct position and each bit
 * gets assigned DCL which is then sent using PWM on timer 1
 * Parameters: void
*/
void send_data(void){
	uint32_t color_bits;
	int LED_index = 0;
	int i;
	int j;

	for(i =0; i < NUM_OF_LEDS; i++){
		color_bits = (LED_data[i][1]<<16) | (LED_data[i][0]<<8) | (LED_data[i][2]);		// Shifts the bits into the position that is in the datasheet (GRB)


		for(j = 23; j >= 0; j--){														// Iterates 24 times to go thorough each bit of color_bits
			if(color_bits & (1 << j)){													// Creates a 24b mask where only jth bit is 1 and compares it to color_bits - the result of the applied mask are 24 bits and if only 1 bit it 1 it is considered True
				PWM_DCL[LED_index] = 64;												// If the result is 1 than the bit gets assigned DCL of 64%
			}
			else{
				PWM_DCL[LED_index] = 32;												// If the result is 0 DCL is 32%
			}
			LED_index++;
		}
	}

	for(i = 0; i < 50; i++){															// Creates 50 values with the DCL of 0 to act as the reset pulse (ws2812b datasheet)
		PWM_DCL[LED_index] = 0;
		LED_index++;
	}
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1,(uint32_t*)PWM_DCL, LED_index);			// Sends the PWM pulses according to the values inside PWM_DCL
	while(PWM_completed == 0){};														// Waits until PWM is finished
	PWM_completed = 0;

}

void HAL_TIM_PWM_PulseFinishedCallback( TIM_HandleTypeDef *htim){
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	PWM_completed = 0;
}

