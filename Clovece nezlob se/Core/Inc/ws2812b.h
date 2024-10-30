/*
 * ws2812b.h
 *
 *  Created on: Oct 30, 2024
 *      Author: Adam Zatloukal
 */

#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

// Macros
#define NUM_OF_LEDS 1

// Functions
void set_LED_color(int LED_index, uint8_t Red, uint8_t Green, uint8_t Blue);
void send_data(void);

#endif /* INC_WS2812B_H_ */
