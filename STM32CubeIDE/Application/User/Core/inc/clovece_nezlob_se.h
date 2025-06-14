/*
 * clovece_nezlob_se.h
 *
 *  Created on: Nov 17, 2024
 *      Author: Adam Zatloukal
 */

#ifndef INC_CLOVECE_NEZLOB_SE_H_
#define INC_CLOVECE_NEZLOB_SE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


/*--------------------- Structs ---------------------*/

/*
 * Each player has a struct with these parameters
 * position - the current position on the board of each pawn
 * positions_moved - how many positions a pawn has moved - needed to calculate when the pawn reaches the end		UPDATE
 * at_start - how many pawns are still at start
 * color - color of each player
 * etc
 */
typedef struct{
	uint8_t position[4];
	uint8_t pawns_at_start;
	uint8_t pawns_in_finish;
	uint8_t color[3];
	uint8_t selected_pawn;
	uint8_t board_start_position;
	uint8_t board_end_position;
	uint8_t home_start_position;
	uint8_t finish_position;
	bool is_ai_player;
	bool is_finished;
	int finished_time;
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
}Colors;

typedef enum{
	AT_START_POSITION = 254,
	IN_FINISH_POSITION = 255
}Start_end_positions;

typedef enum{
	SELECTED_PAWN,
	SETTINGS_ANIMATION_DELAY,
	SETTINGS_ANIMATION_START_DELAY,
	SETTINGS_ANIMATION_END_DELAY
}AnimationDelayEvents;


/*--------------------- Macros ---------------------*/

#define PLAYER1_START_HOME 0
#define PLAYER2_START_HOME 4
#define PLAYER3_START_HOME 8
#define PLAYER4_START_HOME 12


/*--------------------- Function declarations ---------------------*/

uint8_t set_color(uint8_t player, Colors color);
void init_board(uint8_t number_of_players);
void init_player(uint8_t player);

uint8_t roll_dice(uint8_t min, uint8_t max);
Player* select_player(uint8_t player);
void select_pawn(uint8_t player, uint8_t pawn);
void move_pawn(uint8_t player, uint8_t number);
void set_position_of_all_pawns(void);
void kick_out_pawn(Player* player_struct, uint8_t player);
void check_finish_pawn(Player* player_struct, uint8_t player);
void init_finish(Player* player_struct, uint8_t player);
void check_for_overlap(void);
void overlap_animation(void);
void selected_pawn_animation(uint8_t player);
void pawn_kick_set_board_animation(uint8_t player);
void pawn_kick_set_start_animation(uint8_t i, uint8_t player, char* state);
void pawn_finish_animation(uint8_t player);
void player_finish_animation(uint8_t player);
void init_random(void);
void sync_info(void);
uint8_t handle_ai_player_movement(void);
void check_player_finish(Player* player_struct);
void check_end_game(void);
void pawn_kick_board_animation(uint8_t iterated_player, uint8_t iterated_pawn);
void pawn_set_board_animation(uint8_t player);

#ifdef __cplusplus
}
#endif

#endif /* INC_CLOVECE_NEZLOB_SE_H_ */
