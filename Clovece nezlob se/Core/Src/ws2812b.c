#include "main.h"
#include "ws2812b.h"
#include "string.h"
#include "math.h"

extern TIM_HandleTypeDef htim1;					//makes htim1 a global variable

typedef struct{
	uint8_t led_data[NUM_OF_LEDS_BOARD][3];
	uint8_t led_mod[NUM_OF_LEDS_BOARD][3];
	uint16_t pwm_dcl[24 * NUM_OF_LEDS_BOARD + 50];
}CH1_data;

typedef struct{
	uint8_t led_data[NUM_OF_LEDS_START][3];
	uint8_t led_mod[NUM_OF_LEDS_START][3];
	uint16_t pwm_dcl[24 * NUM_OF_LEDS_START + 50];
}CH2_data;

typedef struct{
	uint8_t led_data[NUM_OF_LEDS_END][3];
	uint8_t led_mod[NUM_OF_LEDS_END][3];
	uint16_t pwm_dcl[24 * NUM_OF_LEDS_END + 50];
}CH3_data;

typedef struct{
	CH1_data ch1;
	CH2_data ch2;
	CH3_data ch3;
}Channel_data;

uint8_t channel;
uint16_t number_of_leds = NUM_OF_LEDS_BOARD;
uint8_t pwm_completed = 0;
int led_index = 0;
float scale_factors[256];

Channel_data channel_data;		//Creates an instance of Channel_data struct

/*
 * Sets channel of the timer
 * Parameters:
 * channel - Sets the PWM channel of timer 1
 * 			1 - TIM_CHANNEL_1
 * 			2 - TIM_CHANNEL_4
 * 			3 - TIM_CHANNEL_3
 */
void set_PWM_channel(uint8_t channel){
	if(channel == 1){
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1,(uint32_t*)set_data_array(channel), led_index);
	}
	else if(channel == 2){
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*) set_data_array(channel), led_index);
	}
	else if(channel == 3){
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t*) set_data_array(channel), led_index);
	}
	while(pwm_completed == 0){};
	pwm_completed = 0;
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
 * led_index - index of the LED
 * channel - channel of TIM1
 * 			1 - board
 * 			2 - start
 * 			3 - end
 * Red 	   - value of Red (0 - 255)
 * Green     - value of Green (0 - 255)
 * Blue	   - value of Blue (0 - 255)
*/
void set_LED_color(int led_index,uint8_t channel,uint8_t Red, uint8_t Green, uint8_t Blue){
	if(channel == 1){
		channel_data.ch1.led_data[led_index][0] = Red;
		channel_data.ch1.led_data[led_index][1] = Green;
		channel_data.ch1.led_data[led_index][2] = Blue;
	}
	else if(channel == 2){
		channel_data.ch2.led_data[led_index][0] = Red;
		channel_data.ch2.led_data[led_index][1] = Green;
		channel_data.ch2.led_data[led_index][2] = Blue;
	}
	else if(channel == 3){
		channel_data.ch3.led_data[led_index][0] = Red;
		channel_data.ch3.led_data[led_index][1] = Green;
		channel_data.ch3.led_data[led_index][2] = Blue;
	}
}

/*
 * Puts the data into correct position and each bit
 * gets assigned DCL which is then sent using PWM on timer 1
 * Parameters:
 * channel - sets the PWM channel output of TIM1
*/
void send_data(uint8_t channel){
	uint32_t color_bits;
	led_index = 0;

	number_of_leds = set_num_of_leds(channel);

	for(int i = 0; i < number_of_leds; i++){
#if USE_BRIGHTNESS
		if(channel == 1){
			color_bits = (channel_data.ch1.led_mod[i][1]<<16) | (channel_data.ch1.led_mod[i][0]<<8) | (channel_data.ch1.led_mod[i][2]);
		}
		else if(channel == 2){
			color_bits = (channel_data.ch2.led_mod[i][1]<<16) | (channel_data.ch2.led_mod[i][0]<<8) | (channel_data.ch2.led_mod[i][2]);
		}
		else if(channel == 3){
			color_bits = (channel_data.ch3.led_mod[i][1]<<16) | (channel_data.ch3.led_mod[i][0]<<8) | (channel_data.ch3.led_mod[i][2]);
		}
#else
		if(channel == 1){
			color_bits = (channel_data.ch1.led_data[i][1]<<16) | (channel_data.ch1.led_data[i][0]<<8) | (channel_data.ch1.led_data[i][2]);		// Shifts the bits into the position that is in the datasheet (GRB)
		}
		else if(channel == 2){
			color_bits = (channel_data.ch2.led_data[i][1]<<16) | (channel_data.ch2.led_data[i][0]<<8) | (channel_data.ch2.led_data[i][2]);
		}
		else if(channel == 3){
			color_bits = (channel_data.ch3.led_data[i][1]<<16) | (channel_data.ch3.led_data[i][0]<<8) | (channel_data.ch3.led_data[i][2]);
		}
#endif


		for(int j = 23; j >= 0; j--){		// Iterates 24 times to go thorough each bit of color_bits
			if(color_bits & (1 << j)){	// Creates a 24b mask where only jth bit is 1 and compares it to color_bits - the result of the applied mask are 24 bits and if only 1 bit it 1 it is considered True
				set_data_array_value(led_index, channel, "high");	// If the result is 1 than the bit gets assigned DCL of 64%
			}
			else{
				set_data_array_value(led_index, channel, "low");	// If the result is 0 DCL is 32%
			}
			led_index++;
		}
	}

	for(int i = 0; i < RESET_PULSE_COUNT; i++){		// Creates 50 values with the DCL of 0 to act as the reset pulse (ws2812b datasheet)
		set_data_array_value(led_index, channel, "none");
		led_index++;
	}
	set_PWM_channel(channel);
}

/*
 * Stops PWM when all data is sent
 * Sets the pwm_completed flag
 */
void HAL_TIM_PWM_PulseFinishedCallback( TIM_HandleTypeDef *htim){
	if(channel == 1){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);			//never gets called since the global channel variable is always 0
	}
	else if(channel == 2){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);
	}
	else if(channel == 3){
		HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_3);
	}

	pwm_completed = 1;
}

/*
 * Turn on all the LEDs
 * Parameters:
 * channel - TIM1 channel (1 - 3)
 * Red - (0 - 255)
 * Green - (0 - 255)
 * Blue - (0 - 255)
 */
void turn_on_all_led(uint8_t channel, uint8_t Red, uint8_t Green, uint8_t Blue){
	int i;

	for(i = 0; i < set_num_of_leds(channel); i++){
		set_LED_color(i, channel, Red, Green, Blue);
	}
}

/*
 * Sets the DCL of a bit based on it´s channel and level
 * Parameters:
 * led_index - LED number
 * channel - TIM1 PWM channel (1 - 3)
 * level - "high" - DCL = 60
 * 		   "low"  - DCL = 30
 */
void set_data_array_value(uint16_t led_index, uint8_t channel,char* level){
	uint8_t DCL;
	if (strcmp(level, "high") == 0){
		DCL = 64;
	}
	else if(strcmp(level, "low") == 0){
		DCL = 32;
	}
	else if(strcmp(level, "none") == 0){
		DCL = 0;
	}
	else{
		return;
	}

	switch(channel){
		case 1:
			channel_data.ch1.pwm_dcl[led_index] = DCL;
			break;
		case 2:
			channel_data.ch2.pwm_dcl[led_index] = DCL;
			break;
		case 3:
			channel_data.ch3.pwm_dcl[led_index] = DCL;
			break;
		default:
			break;
	}
}

/*
 * Returns the PWM_DCL array baed on the channel
 * Parameters:
 * channel - TIM1 PWM channel (1 - 3)
 */
uint16_t* set_data_array(uint8_t channel){
	switch(channel){
		case 1:
			return channel_data.ch1.pwm_dcl;
		case 2:
			return channel_data.ch2.pwm_dcl;
		case 3:
			return channel_data.ch3.pwm_dcl;
		default:
			return channel_data.ch1.pwm_dcl;
	}
}



/*
 * Sets the brightness of all LEDs
 * Parameters:
 * channel - TIM1 channel (1 - 3)
 * brightness - brightness value (0 - 255)
 */
void set_brightness(uint8_t channel, uint8_t brightness){
#if USE_BRIGHTNESS
	float scale_factor = scale_factors[brightness];

	for(int i = 0; i < set_num_of_leds(channel); i++){
		for(int j = 0; j < 3; j++){
			if(channel == 1){
				channel_data.ch1.led_mod[i][j] = (int)(channel_data.ch1.led_data[i][j] * scale_factor);
			}
			else if(channel == 2){
				channel_data.ch2.led_mod[i][j] = (int)(channel_data.ch2.led_data[i][j] * scale_factor);
			}
			else if(channel == 3){
				channel_data.ch3.led_mod[i][j] = (int)(channel_data.ch3.led_data[i][j] * scale_factor);
			}
		}
	}
#endif
}

/*
 * Sets the brightness of an individual LED
 * Parameters:
 * led_index  - LED you want to change the brightness of
 * channel - TIM1 channel (1 - 3)
 * brightness - brightness value (0 - 255)
 */
void set_brightness_individually(uint8_t led_index,uint8_t channel, uint8_t brightness){
#if USE_BRIGHTNESS
	float scale_factor = scale_factors[brightness];

	for(int j = 0; j < 3; j++){
			if(channel == 1){
				channel_data.ch1.led_mod[led_index][j] = (int)(channel_data.ch1.led_data[led_index][j] * scale_factor);
			}
			else if(channel == 2){
				channel_data.ch2.led_mod[led_index][j] = (int)(channel_data.ch2.led_data[led_index][j] * scale_factor);
			}
			else if(channel == 3){
				channel_data.ch3.led_mod[led_index][j] = (int)(channel_data.ch3.led_data[led_index][j] * scale_factor);
			}
		}
#endif
}


/*
 * Initializes the brightness calculations
 * Results are put into a lookup table
 */
void init_brightness(void){
	float gamma = 2.2f;

	for(int brightness = 0; brightness < 256; brightness++){
		float normalized_brightness = brightness / 255.0f;
		scale_factors[brightness]= pow(normalized_brightness, gamma);
	}
}
