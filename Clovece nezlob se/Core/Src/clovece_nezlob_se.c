#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "ws2812b.h"
#include "clovece_nezlob_se.h"
#include "main.h"

uint8_t num_of_players;

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
		set_LED_color(position, START, set_color(player, 0), set_color(player, 0), set_color(player, 0));		// sets all the led_data to 0
	}
	for(int position = start_pos; position < start_pos + player_struct->figures_at_start; position++){
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

		for(int figure = 0; figure < 4; figure++){
			player_struct->position[figure] = AT_START_POSITION;
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

	// Amount of figures init
	player_data.player1.figures_at_start = 4;		//to do: add custom number of figures
	player_data.player2.figures_at_start = 4;
	player_data.player3.figures_at_start = 4;
	player_data.player4.figures_at_start = 4;

	player_data.player1.figures_in_finish = 0;
	player_data.player2.figures_in_finish = 0;
	player_data.player3.figures_in_finish = 0;
	player_data.player4.figures_in_finish = 0;

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




/*--------------------- Dice, figure movement ---------------------*/

/*
 * Placeholder function currently
 * Generates pseudo random numbers using a seed
 */
uint8_t roll_dice(uint8_t min, uint8_t max){
	srand(time(0));

	return (rand() % max) + min;		//placeholder for random numbers
}

/*
 * Selects the figure
 * !!!Placeholder function currently!!!
 * Parameters:
 * figure - (0 - 3)
 */
void select_figure(uint8_t player, uint8_t figure){			// add logic for buttons for now (take a look at the display)
	switch(player){
		case 1:
			 player_data.player1.selected_figure = figure;
			 break;
		case 2:
			 player_data.player2.selected_figure = figure;
			 break;
		case 3:
			 player_data.player3.selected_figure = figure;
			 break;
		case 4:
			 player_data.player4.selected_figure = figure;
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
 * Handles all movement of figures on the board
 * Parameters:
 * player - player whose turn currently is
 * number - number that was rolled
 *
 * Notes:
 * Position 254 -> START
 * Position 255 -> END
 */
void move_figure(uint8_t player, uint8_t number){
	Player* player_struct = select_player(player);
	uint8_t* figure_position = &player_struct->position[player_struct->selected_figure];


	// Removes the figure from start and puts it on the board
	if(number == 6 && *figure_position == AT_START_POSITION){
		*figure_position = player_struct->board_start_position;
		player_struct->figures_at_start--;

		init_player(player);		//updated the figures at start	-> add blinking or fade animation when you move figure from home
		set_LED_color(*figure_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE)); //puts the figure on the board

	}
	// Figure movement on the board
	else{
		for(int step = 0; step < number; step++){
			if(*figure_position == 39){
				*figure_position = 0;

				set_LED_color(*figure_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
				set_LED_color(39, BOARD, set_color(player, 0), set_color(player, 0), set_color(player, 0));
			}
			else{
				(*figure_position)++;

				set_LED_color(*figure_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
				set_LED_color(*figure_position - 1, BOARD, set_color(player, 0), set_color(player, 0), set_color(player, 0));
			}

			set_position_of_all_figures();
			kick_out_figure(player_struct, player);

			set_brightness(BOARD, 100);
			send_data(BOARD);

			HAL_Delay(1000);
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
 * Sets the position of all figures
 * Used when 2 figures overlap to light up the figure that the other figure went over
 * !!!This function doesn't send the data but only sets the RGB values for each position!!!
 */
void set_position_of_all_figures(void){
	for(int player = 1; player <= num_of_players; player++){
		Player* player_struct = select_player(player);

		for(int figure = 0; figure < 4; figure++){
			uint8_t* figure_position = &player_struct->position[figure];

			if(*figure_position != AT_START_POSITION || *figure_position != IN_FINISH_POSITION){
				set_LED_color(*figure_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			}
		}
	}
}


/*
 * Checks if 2 figure that are not from the same player overlap
 * If they do the figure that was originally there gets kicked to the START
 * Parameters:
 * player - the player whose turn currently is
 */
void kick_out_figure(Player* player_struct, uint8_t player){
	for(int current_player = 1;  current_player < 5; current_player++){
		// Checks if the iterated player is the same as the player whose figure moved (you cannot kick out your own figure)
		if(current_player == player){
			continue;
		}
		// Figures overlap -> figure that was originally in that place gets kicked out
		else{
			Player* iterated_player_struct = select_player(current_player);

			for(int figure = 0; figure < 4; figure++){
				uint8_t* iterated_figure = &iterated_player_struct->position[figure];

				if(*iterated_figure == player_struct->position[player_struct->selected_figure]){
					set_LED_color(*iterated_figure, BOARD, set_color(current_player, 0), set_color(current_player, 0), set_color(current_player, 0));
					set_LED_color(player_struct->position[player_struct->selected_figure], BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));

					*iterated_figure = AT_START_POSITION;
					iterated_player_struct->figures_at_start++;

					init_player(current_player);		//Put the figure back to start

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
void check_finish_figure(Player* player_struct, uint8_t player){
	uint8_t* figure_position = player_struct->position[player_struct->selected_figure];

	// Checks if the player has reached the end position (+1 because you need to move the figure into the end home)
	if(*figure_position  == player_struct->board_end_position + 1){
		player_struct->figures_in_finish++;
		init_finish();
	}
}
/*
 * Add documentation
 */
void init_finish(Player* player_struct, uint8_t player){
	uint8_t* figure_position = player_struct->position[player_struct->selected_figure];

	set_LED_color(*figure_position, BOARD, set_color(player, 0), set_color(player, 0), set_color(player, 0));		//Turns of the LEDs last position on board

	if(player == 1 || player == 2){
		for(int position = player_struct->home_start_position; position < player_struct->home_start_position - 3; position--){
			//logic for setting the figure into home
		}
	}
	if(player == 3 || player == 4){
		for(int position = player_struct->home_start_position; position < player_struct->home_start_position + 3; position++){
			//logic for setting the figure into home
		}
	}
	*figure_position = IN_FINISH_POSITION;
}
