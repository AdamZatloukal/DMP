/*
 * clovece_nezlob_se.h
 *
 *  Created on: Nov 17, 2024
 *      Author: Adam Zatloukal
 */

#ifndef INC_CLOVECE_NEZLOB_SE_H_
#define INC_CLOVECE_NEZLOB_SE_H_


/*--------------------- Structs ---------------------*/

/*
 * Each player has a struct with these parameters
 * position - the current position on the board of each figure
 * positions_moved - how many positions a figure has moved - needed to calculate when the figure reaches the end
 * at_start - how many figures are still at start
 * color - color of each player
 */
typedef struct{
	uint8_t position[4];
	uint8_t positions_moved[4];		// Probably wont be used since we will use start and end pos for each player
	uint8_t figures_at_start;
	uint8_t color[3];
	uint8_t selected_figure;
	uint8_t board_start_position;
	uint8_t board_end_position;
}Player;


typedef struct{
	Player player1;		//Red
	Player player2;		//Blue
	Player player3;		//Yellow
	Player player4;		//Green
}PlayerData;


/*--------------------- Enums ---------------------*/

typedef enum{
	BOARD = 1,
	START = 2,
	END   = 3
}Channels;

typedef enum{
	RED =   0,
	GREEN = 1,
	BLUE =  2
}Color;

typedef enum{
	AT_START_POSITION = 254,
	IN_FINISH_POSITION = 255
}Start_end_positions;


/*--------------------- Macros ---------------------*/

#define PLAYER1_START_HOME 0
#define PLAYER2_START_HOME 4
#define PLAYER3_START_HOME 8
#define PLAYER4_START_HOME 12


/*--------------------- Function declarations ---------------------*/

uint8_t set_color(uint8_t player, Color color);
void init_board(uint8_t number_of_players);
void init_player(uint8_t player);

uint8_t roll_dice(uint8_t min, uint8_t max);
Player* select_player(uint8_t player);
void select_figure(uint8_t player, uint8_t figure);
void move_figure(uint8_t player, uint8_t number);

#endif /* INC_CLOVECE_NEZLOB_SE_H_ */
