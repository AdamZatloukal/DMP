/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef enum{
	ROLL_DICE = 0,
	SELECT_PAWN = 1,
	MENU = 2,
	NONE = 3,
	PAWN_SELECTED = 4,
	FINISH_GAME = 5
}Events;

typedef enum{
	INITIALIZATION,
	IN_PROGRESS,
	FINISH
}GameStage;

typedef struct{
	uint8_t current_event;
	uint8_t selected_pawn;
	uint8_t current_player;
	uint8_t number_of_players;
	uint8_t rolled_number;
	uint8_t game_stage;
	uint8_t number_of_ai_players;	// Start from player 1 normal players then when we run out of real players fill with ai if its turned on
	int number_of_set_pawns;
	int number_of_kicked_pawns;
	int number_of_rolls;
	uint8_t results[4];		// Formar: [0] 1st player, [1] 2nd player, ...
	int finish_milis;
}GameInfo;

extern GameInfo game_info;
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void init_game(uint8_t num_of_player);

void handle_initialization(void);
void handle_in_progress(void);
void handle_finish(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_USER_Pin GPIO_PIN_13
#define BUTTON_USER_GPIO_Port GPIOC
#define DISPLAY_TEARING_EFFECT_Pin GPIO_PIN_0
#define DISPLAY_TEARING_EFFECT_GPIO_Port GPIOA
#define DISPLAY_TEARING_EFFECT_EXTI_IRQn EXTI0_1_IRQn
#define DISPLAY_RESET_Pin GPIO_PIN_1
#define DISPLAY_RESET_GPIO_Port GPIOA
#define BUTTON_LEFT_Pin GPIO_PIN_0
#define BUTTON_LEFT_GPIO_Port GPIOB
#define BUTTON_RIGHT_Pin GPIO_PIN_1
#define BUTTON_RIGHT_GPIO_Port GPIOB
#define BUTTON_UP_Pin GPIO_PIN_12
#define BUTTON_UP_GPIO_Port GPIOB
#define DISPLAY_DCX_Pin GPIO_PIN_14
#define DISPLAY_DCX_GPIO_Port GPIOB
#define FLASH_CS_Pin GPIO_PIN_8
#define FLASH_CS_GPIO_Port GPIOA
#define DISPLAY_CSX_Pin GPIO_PIN_9
#define DISPLAY_CSX_GPIO_Port GPIOA
#define BUTTON_CENTER_Pin GPIO_PIN_7
#define BUTTON_CENTER_GPIO_Port GPIOC
#define BUTTON_DOWN_Pin GPIO_PIN_4
#define BUTTON_DOWN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
