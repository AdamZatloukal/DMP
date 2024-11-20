#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "ws2812b.h"
#include "clovece_nezlob_se.h"
#include "main.h"



PlayerData player_data;
uint8_t num_of_players;


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

	// Board start and end positions
	player_data.player1.board_start_position = 2;
	player_data.player1.board_end_position = 1;

	player_data.player2.board_start_position = 12;
	player_data.player2.board_end_position = 11;

	player_data.player3.board_start_position = 22;
	player_data.player3.board_end_position = 21;

	player_data.player4.board_start_position = 32;
	player_data.player4.board_end_position = 31;
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
 * Add documentation
 */
uint8_t roll_dice(uint8_t min, uint8_t max){
	srand(time(0));

	return (rand() % max) + min;		//placeholder for random numbers
}

/*
 * Add documentation
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
 * Add documentation
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
 * Position 254 -> START
 * Position 255 -> END
 *	Pointer shenanigans
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
	else{
		for(int step = 0; step < number; step++){
			(*figure_position)++;


			set_LED_color(*figure_position, BOARD, set_color(player, RED), set_color(player, GREEN), set_color(player, BLUE));
			set_LED_color(*figure_position - 1, BOARD, set_color(player, 0), set_color(player, 0), set_color(player, 0));

			set_position_of_all_figures();

			set_brightness(BOARD, 100);
			send_data(BOARD);

			HAL_Delay(1000);
		}
	}
	set_brightness(START, 100); //placeholder brightness
	set_brightness(BOARD, 100);
	set_brightness(END, 100);

	send_data(START);
	send_data(BOARD);
	send_data(END);
}


/*
 * This function doesn't send the data but only sets the RGB values for each position
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
