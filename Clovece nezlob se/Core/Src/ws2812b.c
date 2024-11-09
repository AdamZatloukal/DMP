#include "main.h"
#include "ws2812b.h"

extern TIM_HandleTypeDef htim1;					//makes htim1 a global variable


uint8_t channel;
uint16_t number_of_leds = NUM_OF_LEDS_BOARD;
uint8_t LED_data[NUM_OF_LEDS_BOARD][3];
uint16_t PWM_DCL[24 * NUM_OF_LEDS_BOARD + 50];
uint8_t PWM_completed = 0;
int LED_index = 0;

/*
 * Sets channel of the timer
 * Parameters:
 * channel - Sets the PWM channel of timer 1
 * 			1 - TIM_CHANNEL_1
 * 			2 - TIM_CHANNEL_2
 * 			3 - TIM_CHANNEL_3
 */
void set_PWM_channel(uint8_t channel){
	if(channel == 1){
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1,(uint32_t*)PWM_DCL, LED_index);
	}
	else if(channel == 2){
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t*) PWM_DCL, LED_index);
	}
	else if(channel == 3){
		HAL_TIMEx_PWMN_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t*) PWM_DCL, LED_index);
	}
	while(PWM_completed == 0){};
	PWM_completed = 0;
}

/*
 * Sets the number of LEDS based on the PWM channel¨
 * to reduce the number of iterations in send_data
 * Parameters:
 * channel - sets the PWM channel output of TIM1
 */
uint8_t set_num_of_leds(uint8_t channel){
	switch(channel){
		case 1:
			return NUM_OF_LEDS_BOARD;
		case 2:
			return NUM_OF_LEDS_START;
		case 3:
			return NUM_OF_LEDS_END;
		default:
			return NUM_OF_LEDS_BOARD;
	}
}

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
 * Parameters:
 * channel - sets the PWM channel output of TIM1
*/
void send_data(uint8_t channel){
	uint32_t color_bits;
	LED_index = 0;
	int i;
	int j;

	number_of_leds = set_num_of_leds(channel);

	for(i =0; i < number_of_leds; i++){
		color_bits = (LED_data[i][1]<<16) | (LED_data[i][0]<<8) | (LED_data[i][2]);		// Shifts the bits into the position that is in the datasheet (GRB)


		for(j = 23; j >= 0; j--){		// Iterates 24 times to go thorough each bit of color_bits
			if(color_bits & (1 << j)){	// Creates a 24b mask where only jth bit is 1 and compares it to color_bits - the result of the applied mask are 24 bits and if only 1 bit it 1 it is considered True
				PWM_DCL[LED_index] = 60;	// If the result is 1 than the bit gets assigned DCL of 64%
			}
			else{
				PWM_DCL[LED_index] = 30;	// If the result is 0 DCL is 32%
			}
			LED_index++;
		}
	}

	for(i = 0; i < 50; i++){		// Creates 50 values with the DCL of 0 to act as the reset pulse (ws2812b datasheet)
		PWM_DCL[LED_index] = 0;
		LED_index++;
	}
	set_PWM_channel(channel);
}

/*
 * Stops PWM when all data is sent
 * Sets the PWM_completed flag
 */
void HAL_TIM_PWM_PulseFinishedCallback( TIM_HandleTypeDef *htim){
	if(channel == 1){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	}
	else if(channel == 2){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_2);
	}
	else if(channel == 3){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
	}

	PWM_completed = 0;
}
