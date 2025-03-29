#include <gui/screen2_screen/Screen2View.hpp>
#include <main.h>


/*
 * ARROW AND TEXT ANIMATION FOR NUM OF REAL AND AI PLAYERS!!!
 * MAKE SETTINGS NAVIGATION EASIER
 */

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();

    current_widget = START_GAME;
    selectWidget(current_widget);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::incrementValue(){
	switch(current_widget){
		case NUMBER_OF_PLAYERS_TOTAL:
			handleNumberOfPlayersTotal(INCREMENT);
			break;

		case TOGGLE_AI_PLAYERS:
			handleFillWithBots(BUTTON_ON);
			break;

		case NUMBER_OF_PLAYERS_REAL:
			handleNumberOfPlayersReal(INCREMENT);
			break;
		case NUMBER_OF_PLAYERS_AI:
			handleNumberOfPlayersAI(INCREMENT);
			break;
	}
}

void Screen2View::decrementValue(){
	switch(current_widget){
		case NUMBER_OF_PLAYERS_TOTAL:
			handleNumberOfPlayersTotal(DECREMENT);
			break;

		case TOGGLE_AI_PLAYERS:
			handleFillWithBots(BUTTON_OFF);
			break;

		case NUMBER_OF_PLAYERS_REAL:
			handleNumberOfPlayersReal(DECREMENT);
			break;
		case NUMBER_OF_PLAYERS_AI:
			handleNumberOfPlayersAI(DECREMENT);
			break;
	}
}

void Screen2View::select(){
	switch(current_widget){
		case NUMBER_OF_PLAYERS_TOTAL:
			game_info.number_of_players = num_of_players;

			// Select animation
			delay_event = TEXT_ANIMATION;
			last_tick_event = tick;
			numberOfPlayersSetting1.hideText();
			break;

		case START_GAME:
			init_game(num_of_players);
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
			break;

		case NUMBER_OF_PLAYERS_REAL:

			// Select animation
			delay_event = TEXT_ANIMATION;
			last_tick_event = tick;
			numberOfRealPlayersSetting1.hideText();
			break;

		case NUMBER_OF_PLAYERS_AI:
			game_info.number_of_ai_players = num_of_AI_players;

			// Select animation
			delay_event = TEXT_ANIMATION;
			last_tick_event = tick;
			numberOfAIPlayersSetting1.hideText();
			break;
	}
}

void Screen2View::scrollUp(){
	scroll_number++;

	if(scroll_number > NUMBER_OF_SETTINGS){
		scroll_number = NUMBER_OF_SETTINGS;
		return;
	}

	current_widget++;
	selectWidget(current_widget);

	scrollUpImage.setVisible(false);
	scrollUpImage.invalidate();

	delay_event = SCROLL_UP_ANIMATION;
	last_tick_event = tick;
}

void Screen2View::scrollDown(){
	scroll_number--;

	//AI players are OFF
	if(state == BUTTON_OFF && scroll_number < 2){
		scroll_number = 2;

		return;
	}

	if(scroll_number < 0){
		scroll_number = 0;
		return;
	}

	current_widget--;
	selectWidget(current_widget);

	scrollDownImage.setVisible(false);
	scrollDownImage.invalidate();

	delay_event = SCROLL_DOWN_ANIMATION;
	last_tick_event = tick;
}

/*
 * Makes the selected widget visible
 * !!!DOESNT handle widget logic!!!
 */
void Screen2View::selectWidget(uint8_t widget){
	// This sucks but it works

	switch(widget){
	case NUMBER_OF_PLAYERS_TOTAL:
		numberOfPlayersSetting1.setVisible(true);
		numberOfAIPlayersSetting1.setVisible(false);
		fillWithBotsSetting1.setVisible(false);
		numberOfRealPlayersSetting1.setVisible(false);
		startGame1.setVisible(false);
		break;

	case NUMBER_OF_PLAYERS_AI:
		numberOfPlayersSetting1.setVisible(false);
		numberOfAIPlayersSetting1.setVisible(true);
		fillWithBotsSetting1.setVisible(false);
		numberOfRealPlayersSetting1.setVisible(false);
		startGame1.setVisible(false);

		num_of_AI_players = num_of_players - num_of_real_players;
		numberOfAIPlayersSetting1.changeNumberOfPlayers(num_of_AI_players);

		numberOfAIPlayersSetting1.handleColorCircles(num_of_players, num_of_real_players);

		break;

	case TOGGLE_AI_PLAYERS:
		numberOfPlayersSetting1.setVisible(false);
		numberOfAIPlayersSetting1.setVisible(false);
		fillWithBotsSetting1.setVisible(true);
		numberOfRealPlayersSetting1.setVisible(false);
		startGame1.setVisible(false);
		break;

	case NUMBER_OF_PLAYERS_REAL:
		numberOfPlayersSetting1.setVisible(false);
		numberOfAIPlayersSetting1.setVisible(false);
		fillWithBotsSetting1.setVisible(false);
		numberOfRealPlayersSetting1.setVisible(true);
		startGame1.setVisible(false);

		num_of_real_players = num_of_players - num_of_AI_players;
		numberOfRealPlayersSetting1.changeNumberOfPlayers(num_of_real_players);

		numberOfRealPlayersSetting1.handleColorCircles(num_of_real_players);

		break;

	case START_GAME:
		numberOfPlayersSetting1.setVisible(false);
		numberOfAIPlayersSetting1.setVisible(false);
		fillWithBotsSetting1.setVisible(false);
		numberOfRealPlayersSetting1.setVisible(false);
		startGame1.setVisible(true);
		break;
	}

	numberOfPlayersSetting1.invalidate();
	numberOfAIPlayersSetting1.invalidate();
	fillWithBotsSetting1.invalidate();
	numberOfRealPlayersSetting1.invalidate();
	startGame1.invalidate();
}

void Screen2View::handleNumberOfPlayersTotal(uint8_t handle_type){
	// Change num of players total INCREMENT OPERATION
	if(handle_type == INCREMENT){
		num_of_players++;

		if(num_of_players > 4){
			num_of_players = 2;		// 2 is the minimum amount of players (2 real or 1 AI 1 real)
		}

		numberOfPlayersSetting1.changeNumberOfPlayers(num_of_players);	// numberOfPlayersSetting1 is an instance of the numberOfPlayersSetting -> we are calling a method of the class instance

		delay_event = ARROW_RIGHT_ANIMATION;
		last_tick_event = tick;

		numberOfPlayersSetting1.hideArrow(1);
		numberOfPlayersSetting1.handleColorCircles(num_of_players);
	}

	// Change num of players total DECREMENT OPERATION
	else{
		num_of_players--;
		if(num_of_players < 2){
				num_of_players = 4;
		}

		numberOfPlayersSetting1.changeNumberOfPlayers(num_of_players);

		delay_event = ARROW_LEFT_ANIMATION;
		last_tick_event = tick;

		numberOfPlayersSetting1.hideArrow(0);
		numberOfPlayersSetting1.handleColorCircles(num_of_players);
	}

	num_of_AI_players = 0;	// Reset num of AI players when the num of players is changed
}

void Screen2View::handleFillWithBots(uint8_t button_state){
	state = button_state;
	if(state == BUTTON_OFF){
		num_of_real_players = num_of_players;		// Prevents a hard fault
		num_of_AI_players = 0;
	}

	fillWithBotsSetting1.setButtonState(state);
}

void Screen2View::handleTickEvent(){
	tick++;

	// Delay event (for arrow left & right)
	handleArrowAnimation();
}

/*
 * It also handles textcounter animation so the name isnt totally right and should be renamed
 */
void Screen2View::handleArrowAnimation(){
	if(delay_event == SCROLL_UP_ANIMATION){
		if(tick - last_tick_event >= 15){
			scrollUpImage.setVisible(true);
			scrollUpImage.invalidate();

			delay_event = NO_ANIMATION;
		}
	}
	if(delay_event == SCROLL_DOWN_ANIMATION){
		if(tick - last_tick_event >= 15){
			scrollDownImage.setVisible(true);
			scrollDownImage.invalidate();

			delay_event = NO_ANIMATION;
		}
	}

	if(delay_event == TEXT_ANIMATION){
		if(tick - last_tick_event >= 20){
			switch(current_widget){
				case NUMBER_OF_PLAYERS_TOTAL:
					numberOfPlayersSetting1.showText();
					break;

				case NUMBER_OF_PLAYERS_REAL:
					numberOfRealPlayersSetting1.showText();
					break;

				case NUMBER_OF_PLAYERS_AI:
					numberOfAIPlayersSetting1.showText();
					break;

			}

			delay_event = NO_ANIMATION;
		}
	}

	uint8_t image;

	// If delay event is left -> 0 if not and delay event is arrow right -> 1 else NONE
	image = (delay_event == ARROW_LEFT_ANIMATION) ? 0
			: (delay_event == ARROW_RIGHT_ANIMATION) ? 1
			: NO_ANIMATION;

	// Return before the animation because we don't want an array out of bounds
	if(image == NO_ANIMATION){
		return;
	}
	// 15 tick delay -> is executes every 15 tick if the delay event is ARROW_LEFT_ANIMATION
	if(tick - last_tick_event >= 15){
		switch(current_widget){
			case NUMBER_OF_PLAYERS_TOTAL:
				numberOfPlayersSetting1.showArrow(image);
				break;

			case NUMBER_OF_PLAYERS_REAL:
				numberOfRealPlayersSetting1.showArrow(image);
				break;

			case NUMBER_OF_PLAYERS_AI:
				numberOfAIPlayersSetting1.showArrow(image);
				break;

		}

		delay_event = NO_ANIMATION;
	}
}

void Screen2View::handleNumberOfPlayersReal(uint8_t handle_type){
	if(handle_type == INCREMENT){
		// Update number of real and AI players
		num_of_real_players++;

		// Makes sure we never go lower than the total amount of players
		if(num_of_real_players > num_of_players){
			num_of_real_players = num_of_players;
		}

		delay_event = ARROW_RIGHT_ANIMATION;
		last_tick_event = tick;
		numberOfRealPlayersSetting1.hideArrow(1);

	}
	else{	// DECREMENT
		// Update number of real and AI players
		num_of_real_players--;

		// Makes sure we never go lower than the total amount of players
		if(num_of_real_players < 1){	// The minimum amount of real players when AI is on is 1 (2 total 1 real & 1 AI)
			num_of_real_players = 1;
		}

		delay_event = ARROW_LEFT_ANIMATION;
		last_tick_event = tick;
		numberOfRealPlayersSetting1.hideArrow(0);

	}

	num_of_AI_players = num_of_players - num_of_real_players;
	game_info.number_of_ai_players = num_of_AI_players;

	numberOfRealPlayersSetting1.changeNumberOfPlayers(num_of_real_players);
	numberOfAIPlayersSetting1.changeNumberOfPlayers(num_of_AI_players);	// Not created yet

	numberOfRealPlayersSetting1.handleColorCircles(num_of_real_players);
}

void Screen2View::handleNumberOfPlayersAI(uint8_t handle_type){
	if(handle_type == INCREMENT){
		// Update number of real and AI players
		num_of_AI_players++;

		// Makes sure we never go lower than the total amount of players
		if(num_of_AI_players > num_of_players){
			num_of_AI_players = num_of_players;
		}

		delay_event = ARROW_RIGHT_ANIMATION;
		last_tick_event = tick;
		numberOfAIPlayersSetting1.hideArrow(1);
	}
	else{	// DECREMENT
		// Update number of real and AI players
		num_of_AI_players--;

		// Makes sure we never go lower than the total amount of players
		if(num_of_AI_players < 0){
			num_of_AI_players = 0;
		}

		delay_event = ARROW_LEFT_ANIMATION;
		last_tick_event = tick;
		numberOfAIPlayersSetting1.hideArrow(0);
	}

	num_of_real_players = num_of_players - num_of_AI_players;

	game_info.number_of_ai_players = num_of_AI_players; // Updates the main gameinfo struct

	numberOfAIPlayersSetting1.changeNumberOfPlayers(num_of_AI_players);
	numberOfRealPlayersSetting1.changeNumberOfPlayers(num_of_real_players);

	numberOfAIPlayersSetting1.handleColorCircles(num_of_players, num_of_real_players);
}
