/*
 * milis.h
 *
 *  Created on: Dec 28, 2024
 *      Author: zatlo
 */

#ifndef APPLICATION_USER_CORE_INC_MILIS_H_
#define APPLICATION_USER_CORE_INC_MILIS_H_

void delay(int animation_delay_event);

extern volatile int miliseconds;

extern uint32_t last_toggle_time;
extern uint32_t last_toggle;
extern uint32_t last_toggle_end;
extern uint32_t last_toggle_overlap;

void handle_selected_pawn_delay(void);
void handle_settings_animation_delay(void);
void handle_settings_animation_start_delay(void);
void handle_settings_animation_end_delay(void);
void handle_overlap_animation(uint8_t overlap_index);

#endif /* APPLICATION_USER_CORE_INC_MILIS_H_ */
