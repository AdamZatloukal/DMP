/*
 * ws2812b.h
 *
 *  Created on: Oct 30, 2024
 *      Author: Adam Zatloukal
 */

#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

// Macros
#define NUM_OF_LEDS_BOARD   40
#define NUM_OF_LEDS_START	16
#define NUM_OF_LEDS_END		16
#define USE_BRIGHTNESS		1
#define RESET_PULSE_COUNT   50

// Functions
void set_LED_color(int led_index,uint8_t channel,uint8_t Red, uint8_t Green, uint8_t Blue);
void send_data(uint8_t channel);
void set_PWM_channel(uint8_t channel);
uint8_t set_num_of_leds(uint8_t channel);
void turn_on_all_led(uint8_t channel, uint8_t Red, uint8_t Green, uint8_t Blue);
void set_data_array_value(uint16_t led_index, uint8_t channel,char* level);
uint16_t* set_data_array(uint8_t channel);
void set_brightness(uint8_t channel, uint8_t brightness);
void set_brightness_individually(uint8_t led_index,uint8_t channel, uint8_t brightness);
void init_brightness(void);


#endif /* INC_WS2812B_H_ */
