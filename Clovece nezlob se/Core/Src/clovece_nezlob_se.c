#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ws2812b.h"
#include "clovece_nezlob_se.h"
#include "main.h"

uint8_t num_of_players;
uint8_t overlaping_positions[NUM_OF_LEDS_BOARD];

PlayerData player_data;


/*--------------------- Board Initialization ---------------------*/
/*
 * Returns R, G or B color value based on the player
 * Parameters:
 * player - (1 - 4)
 * color - RED = 0
 * 		   GREEN = 1
 * 		   BLUE = 2    ¨
 * 		   these are defined in an enum in clovece_nezlob_se.h
 */
uint8_t set_color(uint8_t player, Color color){
	switch(player){
		case 1:
			return player_data.player1.color[color];
		case 2:
			return player_data.player2.color[color];
		case 3:
			return player_data.player3.color[color];
		case 4:
			return player_data.player4.color[color];
		default:
			return 0;
	}
}

/*
 * Initialized the board for each player
 * Parameters:
 * player - player for whom we are initializing the board (1 - 4)
 */
void init_player(uint8_t player){
	uint8_t start_pos;
	Player* player_struct = select_player(player);

	switch(player){
		case 1:
			start_pos = PLAYER1_START_HOME;
			break;
		case 2:
			start_pos = PLAYER2_START_HOME;
			break;
		case 3:
			start_pos = PLAYER3_START_HOME;
			break;
		case 4:
			start_pos = PLAYER4_START_HOME;
			break;
	}

	for(int position = start_pos; position < start_pos + 4; position++){
		set_LED_color(position, START, set_color(0, 0), set_color(0, 0), set_color(0, 0));		// sets all the led_data to 0
	}
	for(int position = start_pos; position < start_pos + player_struct->pawns_at_start; position++){
		set_LED_color(position, START, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE)); //set the color based on the player
	}
}

/*
 * Sets the starting values of each player´s struct
 * Parameters:
 * number_of_players - amount of players playing the game (2 - 4)
 */
void init_player_data(uint8_t number_of_players){
	num_of_players = number_of_players;
	for(int player = 1; player <= 4; player++){
		Player* player_struct = select_player(player);

		for(int pawn = 0; pawn < 4; pawn++){
			player_struct->position[pawn] = AT_START_POSITION;
		}
	}
	// Color init
	player_data.player1.color[0] = 255;		// Red		//SET THE VALUES OF ONLY PLAYERS THAT ARE PLAYING
	player_data.player1.color[1] = 0;
	player_data.player1.color[2] = 0;

	player_data.player2.color[0] = 0;		// Blue
	player_data.player2.color[1] = 0;
	player_data.player2.color[2] = 255;

	player_data.player3.color[0] = 255;		// Yellow
	player_data.player3.color[1] = 255;
	player_data.player3.color[2] = 000;

	player_data.player4.color[0] = 0;		// Green
	player_data.player4.color[1] = 255;
	player_data.player4.color[2] = 0;

	// Amount of pawns init
	player_data.player1.pawns_at_start = 4;		//to do: add custom number of pawns
	player_data.player2.pawns_at_start = 4;
	player_data.player3.pawns_at_start = 4;
	player_data.player4.pawns_at_start = 4;

	player_data.player1.pawns_in_finish = 0;
	player_data.player2.pawns_in_finish = 0;
	player_data.player3.pawns_in_finish = 0;
	player_data.player4.pawns_in_finish = 0;

	// Board start and end positions
	player_data.player1.board_start_position = 2;
	player_data.player1.board_end_position = 1;

	player_data.player2.board_start_position = 12;
	player_data.player2.board_end_position = 11;

	player_data.player3.board_start_position = 22;
	player_data.player3.board_end_position = 21;

	player_data.player4.board_start_position = 32;
	player_data.player4.board_end_position = 31;

	// Set where home of each player begins
	player_data.player1.home_start_position = 3;
	player_data.player2.home_start_position = 7;
	player_data.player3.home_start_position = 8;
	player_data.player4.home_start_position = 12;
}

/*
 * Initializes the board for a game based on how many players are playing
 * Parameters:
 * num_of_player - (1 - 4)
 *
 * to do: init different game modes, rules, etc.
 */
void init_board(uint8_t number_of_players){
	init_player_data(number_of_players);
	for(int player = 1; player <= number_of_players; player++){
		init_player(player);
	}
	set_brightness(START, 100); //placeholder brightness
	send_data(START);
	send_data(BOARD);
}




/*--------------------- Dice, pawn movement ---------------------*/

/*
 * Placeholder function currently
 * Generates pseudo random numbers using a seed
 */
uint8_t roll_dice(uint8_t min, uint8_t max){
	srand(time(0));

	return (rand() % max) + min;		//placeholder for random numbers
}

/*
 * Selects the pawn
 * !!!Placeholder function currently!!!
 * Parameters:
 * pawn - (0 - 3)
 */
void select_pawn(uint8_t player, uint8_t pawn){			// add logic for buttons for now (take a look at the display)
	switch(player){
		case 1:
			 player_data.player1.selected_pawn = pawn;
			 break;
		case 2:
			 player_data.player2.selected_pawn = pawn;
			 break;
		case 3:
			 player_data.player3.selected_pawn = pawn;
			 break;
		case 4:
			 player_data.player4.selected_pawn = pawn;
			 break;
		default:
			break;

	}
}

/*
 * Selects player struct based on the input player
 * Parameters:
 * player - current player
 *
 * Notes:
 * Function returns a pointer to the struct -> store the returned value
 * in a Player pointer
 */
Player* select_player(uint8_t player){
	switch(player){
		case 1:
			return &player_data.player1;
		case 2:
			return &player_data.player2;
		case 3:
			return &player_data.player3;
		case 4:
			return &player_data.player4;
		default:
			return NULL;
	}
}

/*
 * Handles all movement of pawns on the board
 * Parameters:
 * player - player whose turn currently is
 * number - number that was rolled
 *
 * Notes:
 * Position 254 -> START
 * Position 255 -> END
 */
void move_pawn(uint8_t player, uint8_t number){
	Player* player_struct = select_player(player);
	uint8_t* pawn_position = &player_struct->position[player_struct->selected_pawn];


	// Removes the pawn from start and puts it on the board
	if(number == 6 && *pawn_position == AT_START_POSITION){
		*pawn_position = player_struct->board_start_position;
		player_struct->pawns_at_start--;

		init_player(player);		//updated the pawns at start	-> add blinking or fade animation when you move pawn from home
		pawn_kick_set_board_animation(player);

		set_LED_color(*pawn_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE)); //puts the pawn on the board

	}
	// pawn movement on the board
	else{
		for(int step = 0; step < number; step++){
			if(*pawn_position == 39){
				*pawn_position = 0;

				set_LED_color(*pawn_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
				set_LED_color(39, BOARD, set_color(0, 0), set_color(0, 0), set_color(0, 0));
			}
			else if(*pawn_position != IN_FINISH_POSITION && *pawn_position != AT_START_POSITION){
				(*pawn_position)++;

				set_LED_color(*pawn_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
				set_LED_color(*pawn_position - 1, BOARD, set_color(0, 0), set_color(0, 0), set_color(0, 0));
			}

			set_position_of_all_pawns();

			set_brightness(BOARD, 100);
			send_data(BOARD);

			kick_out_pawn(player_struct, player);

			set_LED_color(*pawn_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));

			check_finish_pawn(player_struct, player);

			set_brightness(BOARD, 100);
			send_data(BOARD);

			HAL_Delay(300);
		}
	}

	// Send the data to the LED strip
	set_brightness(START, 100); // 100 is placeholder brightness
	set_brightness(BOARD, 100); // some of these are probably redundant
	set_brightness(END, 100);

	send_data(START);
	send_data(BOARD);
	send_data(END);
}


/*
 * Sets the position of all pawns
 * Used when 2 pawns overlap to light up the pawn that the other pawn went over
 * !!!This function doesn't send the data but only sets the RGB values for each position!!!
 */
void set_position_of_all_pawns(void){
	for(int player = 1; player <= num_of_players; player++){
		Player* player_struct = select_player(player);

		for(int pawn = 0; pawn < 4; pawn++){
			uint8_t* pawn_position = &player_struct->position[pawn];

			if(*pawn_position != AT_START_POSITION || *pawn_position != IN_FINISH_POSITION){
				set_LED_color(*pawn_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			}
		}
	}
}


/*
 * Checks if 2 pawn that are not from the same player overlap
 * If they do the pawn that was originally there gets kicked to the START
 * Parameters:
 * player - the player whose turn currently is
 */
void kick_out_pawn(Player* player_struct, uint8_t player){
	for(int current_player = 1;  current_player < 5; current_player++){
		// Checks if the iterated player is the same as the player whose pawn moved (you cannot kick out your own pawn)
		if(current_player == player){
			continue;
		}
		// pawns overlap -> pawn that was originally in that place gets kicked out
		else{
			Player* iterated_player_struct = select_player(current_player);

			for(int pawn = 0; pawn < 4; pawn++){
				uint8_t* iterated_pawn = &iterated_player_struct->position[pawn];

				if(*iterated_pawn == player_struct->position[player_struct->selected_pawn] && *iterated_pawn != AT_START_POSITION && *iterated_pawn != IN_FINISH_POSITION && *iterated_pawn != iterated_player_struct->board_start_position){
					set_LED_color(*iterated_pawn, BOARD, 0, 0, 0);
					set_LED_color(player_struct->position[player_struct->selected_pawn], BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));

					pawn_kick_set_board_animation(current_player);

					*iterated_pawn = AT_START_POSITION;
					iterated_player_struct->pawns_at_start++;


					init_player(current_player);		//Put the pawn back to start

					set_brightness(START, 100);			// Updates the START
					send_data(START);
				}
			}
		}
	}
}

/*
 * Add documentation
 */
void check_finish_pawn(Player* player_struct, uint8_t player){
	uint8_t* pawn_position = &player_struct->position[player_struct->selected_pawn];

	// Checks if the player has reached the end position (+1 because you need to move the pawn into the end home)
	if(*pawn_position  == player_struct->board_end_position + 1){
		player_struct->pawns_in_finish++;
		init_finish(player_struct, player);

		set_brightness(END, 100);
		send_data(END);
	}
}
/*
 * Add documentation
 */
void init_finish(Player* player_struct, uint8_t player){
	uint8_t* pawn_position = &player_struct->position[player_struct->selected_pawn];

	set_LED_color(*pawn_position, BOARD, set_color(0, 0), set_color(0, 0), set_color(0, 0));		//Turns of the LEDs last position on board

	if(player == 1 || player == 2){
		for(int position = player_struct->home_start_position; position > player_struct->home_start_position - player_struct->pawns_in_finish; position--){
			set_LED_color(position, END, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
		}
	}
	if(player == 3 || player == 4){
		for(int position = player_struct->home_start_position; position < player_struct->home_start_position + player_struct->pawns_in_finish; position++){	// Probably use pawn_in_the_end
			set_LED_color(position, END, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
		}
	}
	*pawn_position = IN_FINISH_POSITION;
}


/*
 * Checks if there are any overlapping pawn
 * Call this function every time a pawn moves
 * Calloverlap_animation to display visual change
 */
void check_for_overlap(void){
	//	Iterates over each player and each pawn of that player to get its position
	for(int player = 1; player < 5; player++){
		Player* player_struct = select_player(player);

		for(int pawn = 0; pawn < 4; pawn++){
			uint8_t position = player_struct->position[pawn];

			//Stores the value of the position if its on the board
			if(position != AT_START_POSITION && position != IN_FINISH_POSITION){
				overlaping_positions[position]++;
			}
		}
	}
	for(int position = 0; position < sizeof(overlaping_positions); position++){
		overlaping_positions[position] = (overlaping_positions[position] == 1) ? 0 : overlaping_positions[position];
	}
}

/*
 * Animates overlapping pawns based on the result of
 * check_for_overlap()
 *
 * Brightness change indicates there are pawns that are overlapping
 */
void overlap_animation(void){
	for(int i = 0; i < sizeof(overlaping_positions); i++){

		// We only want to apply the animation to indexes that have 2 or more pawns
		if(overlaping_positions[i] != 0){
			set_brightness_individually(i, BOARD, 200);
			send_data(BOARD);
			HAL_Delay(500);
			set_brightness_individually(i, BOARD, 50);
			send_data(BOARD);
			HAL_Delay(500);
			set_brightness_individually(i, BOARD, 200);
			send_data(BOARD);
		}
	}
}

/*
 * Blinking animation that shows you the pawn you currently selected
 * Parameters:
 * player - (1 - 4)
 */
void selected_pawn_animation(uint8_t player){
	Player* player_struct = select_player(player);
	uint8_t* selected_pawn = &player_struct->selected_pawn;

	set_brightness_individually(player_struct->position[*selected_pawn], BOARD, 0);
	send_data(BOARD);
	HAL_Delay(1000);
	set_brightness_individually(player_struct->position[*selected_pawn], BOARD, 200);
	send_data(BOARD);
	HAL_Delay(1000);
}

/*
 * Blink animation when a pawn is set on the board
 * or kicked from it
 */
void pawn_kick_set_board_animation(uint8_t player){
	Player* player_struct = select_player(player);

	for(int i = 0; i < 7; i++){
		if(i % 2 == 0){
			HAL_Delay(200);
			set_LED_color(player_struct->position[player_struct->selected_pawn], BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			set_brightness_individually(player_struct->position[player_struct->selected_pawn], BOARD, 30);
			pawn_kick_set_start_animation(i, player, "low_brightness");
			send_data(BOARD);
		}
		else{
			HAL_Delay(250);
			set_LED_color(player_struct->position[player_struct->selected_pawn], BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			set_brightness_individually(player_struct->position[player_struct->selected_pawn], BOARD, 250);
			pawn_kick_set_start_animation(i, player, "high_brightness");
			send_data(BOARD);
		}
	}
	init_player(player);
}

/*
 * Part of pawn_kick_set_board_animation
 * Applies the animation to START
 */
void pawn_kick_set_start_animation(uint8_t i, uint8_t player, char* state){
	uint8_t start_pos;
	Player* player_struct = select_player(player);

	switch(player){
			case 1:
				start_pos = PLAYER1_START_HOME;
				break;
			case 2:
				start_pos = PLAYER2_START_HOME;
				break;
			case 3:
				start_pos = PLAYER3_START_HOME;
				break;
			case 4:
				start_pos = PLAYER4_START_HOME;
				break;
		}
	if(strcmp(state, "high_brightness") == 0){
		for(int position = start_pos; position < start_pos + player_struct->pawns_at_start + 1; position++){
			set_LED_color(position, START, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			set_brightness_individually(position, START, 250);
		}
	}
	else if(strcmp(state, "low_brightness") == 0){
		for(int position = start_pos; position < start_pos + player_struct->pawns_at_start + 1; position++){
			set_LED_color(position, START, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			set_brightness_individually(position, START, 30);
		}
	}
	send_data(START);
}


// Add animation for when end is reached
