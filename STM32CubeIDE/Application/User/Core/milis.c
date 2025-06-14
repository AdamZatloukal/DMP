#include <main.h>
#include <milis.h>
#include <clovece_nezlob_se.h>
#include <ws2812b.h>
#include <stdbool.h>


uint32_t last_toggle_time = 0;
uint32_t last_toggle = 0;
uint32_t last_toggle_end = 0;
uint32_t last_toggle_overlap = 0;
uint32_t last_toggle_select = 0;
bool is_select_triggered = false;

volatile int miliseconds = 0;

extern TIM_HandleTypeDef htim7;

void delay(int animation_delay_event){
	switch(animation_delay_event){
		case SELECTED_PAWN:
			handle_selected_pawn_delay();
			break;

		case SETTINGS_ANIMATION_DELAY:
			handle_settings_animation_delay();
			break;

		case SETTINGS_ANIMATION_START_DELAY:
			handle_settings_animation_start_delay();
			break;

		case SETTINGS_ANIMATION_END_DELAY:
			handle_settings_animation_end_delay();
			break;
		default:
			break;
	}
}

/*
 * Handles the selected pawn animation
 * (upper layer function is in clovece_nezlob_se.c)
 */
void handle_selected_pawn_delay(void){
	Player* player_struct = select_player(game_info.current_player);
	uint8_t* selected_pawn = &player_struct->selected_pawn;

	static uint8_t last_selected_pawn = 255;		// defined on the first execute of this function
	static uint8_t last_brightness = 1; 			//0 - no light, 1 - light

	// Makes sure the Pixel lights up when the last animation stage was brightness 0 and selected pawn changed
	if(*selected_pawn != last_selected_pawn){
		set_brightness_individually(player_struct->position[last_selected_pawn], BOARD, 200);
		send_data(BOARD);

		last_selected_pawn = *selected_pawn;

		return;	// So we dont have to worry about the rest of the function executing
	}

	// Blinking animation with 500 ms delay
	if(player_struct->position[*selected_pawn] != AT_START_POSITION && player_struct->position[*selected_pawn] != IN_FINISH_POSITION){
		if(miliseconds - last_toggle_time >= 500){
			last_toggle_time = miliseconds;

			if(last_brightness == 1){
				set_brightness_individually(player_struct->position[*selected_pawn], BOARD, 0);
				last_brightness = 0;
			}
			else{
				set_brightness_individually(player_struct->position[*selected_pawn], BOARD, 200);
				last_brightness = 1;
			}
			send_data(BOARD);
		}
	}
}

void handle_settings_animation_delay(void){
	// When the game starts we want to turn off every Pixel
	if(game_info.game_stage != INITIALIZATION){
		turn_on_all_led(BOARD, 0, 0, 0);
		set_brightness(BOARD, 0);
		send_data(BOARD);
		return;
	}

	// If the flag is set to true the rest of this function wont execute -> it is set true after pressing center button on Screen2 and will be set to back false after 300 ms
	is_select_triggered = miliseconds - last_toggle_select >=  500 ? false : true;


	static uint32_t last_toggle = 0;
	static int board_i = 0;
	static int num_of_switches = 0;
	static uint8_t board_i_player_4 = 32;


	// Toggle between animation states
	if(miliseconds - last_toggle >= 40){
		last_toggle = miliseconds;

		if(num_of_switches % 2 == 0){
			set_LED_color(board_i + 2, BOARD, set_color(1, RED), set_color(1, GREEN), set_color(1 , BLUE));
			set_LED_color(board_i + 12, BOARD, set_color(2, RED), set_color(2, GREEN), set_color(2, BLUE));
			set_LED_color(board_i + 22, BOARD, set_color(3, RED), set_color(3, GREEN), set_color(3, BLUE));
			set_LED_color(board_i_player_4, BOARD, set_color(4, RED), set_color(4, GREEN), set_color(4, BLUE));

			set_brightness_individually(board_i + 2, BOARD, 200);
			set_brightness_individually(board_i + 12, BOARD, 200);
			set_brightness_individually(board_i + 22, BOARD, 200);
			set_brightness_individually(board_i_player_4, BOARD, 200);

		}
		else if(num_of_switches % 2 != 0){
			set_brightness_individually(board_i + 2, BOARD, 0);
			set_brightness_individually(board_i + 12, BOARD, 0);
			set_brightness_individually(board_i + 22, BOARD, 0);
			set_brightness_individually(board_i_player_4, BOARD, 0);
		}

		// EXPERIMENTAL!!!!
		if(is_select_triggered){
			set_brightness(BOARD, 0);
		}

		send_data(BOARD);

		board_i++;
		board_i_player_4++;

		if(board_i == 10){
			board_i = 0;
			board_i_player_4 = 32;
			num_of_switches++;
		}

		board_i_player_4 = board_i_player_4 == 40 ? 0 : board_i_player_4; // Wraps to the start of the board

	}
}

void handle_settings_animation_start_delay(void){
	if(game_info.game_stage != INITIALIZATION){
		turn_on_all_led(START, 0, 0, 0);
		set_brightness(START, 0);
		send_data(START);
		return;
	}

	// If the flag is set to true the rest of this function wont execute -> it is set true after pressing center button on Screen2 and will be set to back false after 300 ms
	is_select_triggered = miliseconds - last_toggle_select >=  500 ? false : true;

	static uint8_t step1 = 0;
	static uint8_t step2 = 1;

	static int previous_step1 = -1;
	static int previous_step2 = -1;

	static uint32_t last_toggle = 0;

	step1 = step1 > 3 ? 0 : step1;
	step2 = step2 > 3 ? 0 : step2;

	static int colorIndex[4][4] = {{0,3,2,1},{5,4,7,6},{9,10,11,8},{13,12,15,14}};
	static int color[4][3] =  {{255, 0, 0},{0, 0, 255},{255, 255, 0},{0, 255, 0}};

	if(miliseconds - last_toggle >= 120){
		last_toggle = miliseconds;

		for(int player = 0; player < 4; player++){
			if(previous_step1 >= 0){
				set_LED_color(colorIndex[player][previous_step1], START, 0, 0, 0);
				set_brightness_individually(colorIndex[player][previous_step1], START, 0);
			}

			if(previous_step2 >= 0 ){
				set_LED_color(colorIndex[player][previous_step2], START, 0, 0, 0);
				set_brightness_individually(colorIndex[player][previous_step2], START, 0);
			}

			set_LED_color(colorIndex[player][step1], START, color[player][0], color[player][1], color[player][2]);
			set_LED_color(colorIndex[player][step2], START, color[player][0], color[player][1], color[player][2]);

			set_brightness_individually(colorIndex[player][step1], START, 200);
			set_brightness_individually(colorIndex[player][step2], START, 30);

		}


		if(is_select_triggered){
			set_brightness(START, 255);
		}
		send_data(START);

		previous_step1 = step1;
		previous_step2 = step2;

		step1++;
		step2++;
	}
}

void handle_settings_animation_end_delay(void){
	if(game_info.game_stage != INITIALIZATION){
		turn_on_all_led(END, 0, 0, 0);
		set_brightness(END, 0);
		send_data(END);
		return;
	}

	// If the flag is set to true the rest of this function wont execute -> it is set true after pressing center button on Screen2 and will be set to back false after 300 ms
	is_select_triggered = miliseconds - last_toggle_select >=  500 ? false : true;

	static int colorIndex[4][4] = {{0,1,2,3},{4,5,6,7},{11,10,9,8},{15,14,13,12}};
	static int color[4][3] =  {{255, 0, 0},{0, 0, 255},{255, 255, 0},{0, 255, 0}};

	static uint8_t step1 = 0;
	static uint8_t step2 = 1;

	static int previous_step1 = -1;
	static int previous_step2 = -1;


	step1 = step1 > 3 ? 0 : step1;
	step2 = step2 > 3 ? 0 : step2;


	if(miliseconds - last_toggle_end >= 120){
		last_toggle_end = miliseconds;

		for(int player = 0; player < 4; player++){
			if(previous_step1 >= 0){
				set_LED_color(colorIndex[player][previous_step1], END, 0, 0, 0);
				set_brightness_individually(colorIndex[player][previous_step1], END, 0);
			}

			if(previous_step2 >= 0 ){
				set_LED_color(colorIndex[player][previous_step2], END, 0, 0, 0);
				set_brightness_individually(colorIndex[player][previous_step2], END, 0);
			}

			set_LED_color(colorIndex[player][step1], END, color[player][0], color[player][1], color[player][2]);
			set_LED_color(colorIndex[player][step2], END, color[player][0], color[player][1], color[player][2]);

			set_brightness_individually(colorIndex[player][step1], END, 200);
			set_brightness_individually(colorIndex[player][step2], END, 30);
		}

		if(is_select_triggered){
			set_brightness(END, 255);
		}

		send_data(END);

			previous_step1 = step1;
			previous_step2 = step2;

			step1++;
			step2++;
	}
}

void handle_overlap_animation(uint8_t overlap_index){
	static int switches = 0;

	if(miliseconds - last_toggle_overlap >=500){
		last_toggle_overlap = miliseconds;

		if(switches % 2 == 0){
			set_brightness_individually(overlap_index, BOARD, 200);
			send_data(BOARD);
		}
		else{
			set_brightness_individually(overlap_index, BOARD, 50);
			send_data(BOARD);
		}
		switches++;
	}
}

void select_board_animation(void){
	is_select_triggered = true;
	last_toggle_select = miliseconds;
}

/*
 * Timer 7 callback after 1 ms (period of the TIM)
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    miliseconds++;
}



