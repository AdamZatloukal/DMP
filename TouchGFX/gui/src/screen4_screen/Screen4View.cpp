#include <gui/screen4_screen/Screen4View.hpp>
#include <touchgfx/Utils.hpp>



/*
 * The pawn numbering in everything display related is 1 - 4
 * In everything WS2812B related pawn numbering is 0 - 3
 */

Screen4View::Screen4View()
{

}

/*
 * Executes once when the screen is initialized
 * ----------------  Function  ----------------
 * Updates game flags
 * Initializes counter variable
 * Sets the background color according to the current player (ColorUtils.cpp)
 * Shows the rolled number in the upper right corner
 * Updates counter if the selected pawn is in finish -> updates text counter -> sets alpha of the correct pawnImage
 *
 */
void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
    game_info.current_event = SELECT_PAWN;
    player_struct = select_player(game_info.current_player);
    counter = 1;
    tick = 0;

    // Set the background color according to the current player
    setBoxColor(playerBox, game_info.current_player);

    // Show the rolled number
    switch(game_info.rolled_number){
    	case 1:
    		diceResultImage1.setVisible(true);
    		diceResultImage1.invalidate();
    		break;
    	case 2:
    		diceResultImage2.setVisible(true);
    		diceResultImage2.invalidate();
    		break;
    	case 3:
    		diceResultImage3.setVisible(true);
    		diceResultImage3.invalidate();
    		break;
    	case 4:
    		diceResultImage4.setVisible(true);
    		diceResultImage4.invalidate();
    		break;
    	case 5:
    		diceResultImage5.setVisible(true);
			diceResultImage5.invalidate();
			break;
    	case 6:
    		diceResultImage6.setVisible(true);
			diceResultImage6.invalidate();
			break;
    }

    // If the pawn is in finish move to the next pawn
    while(player_struct->position[counter - 1] == IN_FINISH_POSITION){
    	counter++;
    }

    // Update text counter
    Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
	textCounter.invalidate();

	// Set high alpha to the pawn we ended on
	setPawnAlpha(counter);

	game_info.selected_pawn = counter - 1; // Fixes a bug where the overlap animation wouldn't play when the while loop above executes (a pawn is already in finish)

	if(player_struct->is_ai_player){
		//Execute AI pawn selection logic
		game_info.selected_pawn = handle_ai_player_movement();

		setPawnAlpha(game_info.selected_pawn + 1);	// Weird numbering - can reach no. 5 - fixed
		counter = game_info.selected_pawn + 1;
		Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
		textCounter.invalidate();


		delay_event = AI_PAWN_SELECTION;
		last_tick_event = tick;

		AIText.setVisible(true);
		AIText.invalidate();
	}
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}

/*
 * Updates screen and data when hardware button "right" is pressed
 * ----------------  Function  ----------------
 * Counter increment
 * Checks if the selected pawn is in finish
 * Updates text counter
 * Sets the alpha of pawn images
 * Updates game info
 */
void Screen4View::incrementPawn(){
	if(player_struct->is_ai_player){
		return;
	}

	do{
		counter++;

		// Wrap around if we go beyond the last pawn
		if(counter > 4){
			counter = 1;
		}
	}while(player_struct->position[counter - 1] == IN_FINISH_POSITION);	// Skip pawns that reached the end


	Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
	textCounter.invalidate();

	// The if statement prevents alpha blinking of finished pawns ALPHA BLINKING IS STILL AND ISSUE - ver. 3 still an issue but is now managable (isnt easy to notice)
	setPawnAlpha(counter);


	game_info.selected_pawn = counter - 1;

	delay_event = ARROW_RIGHT_ANIMATION;
	last_tick_event = tick;

	imageRight.setVisible(false);	// Part of arrow animation
	imageRight.invalidate();
}

/*
 * Updates screen and data when hardware button "left" is pressed
 * ----------------  Function  ----------------
 * Counter decrement
 * Checks if the selected pawn is in finish
 * Updates text counter
 * Sets the alpha of pawn images
 * Updates game info
 */
void Screen4View::decrementPawn(){
	if(player_struct->is_ai_player){
		return;
	}

	do{
		counter--;

		// Wrap if we go beyond the first pawn
		if(counter < 1){
			counter = 4;
		}
	}while(player_struct->position[counter - 1] == IN_FINISH_POSITION);		// Skip finished pawns

	Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
	textCounter.invalidate();

	setPawnAlpha(counter);

	game_info.selected_pawn = counter - 1;

	delay_event = ARROW_LEFT_ANIMATION;
	last_tick_event = tick;

	imageLeft.setVisible(false);	// Part of arrow animation
	imageLeft.invalidate();
}

/*
 * Updates screen and data when hardware button "middle" is pressed
 * ----------------  Function  ----------------
 * Updates game info
 * Updates game flag
 * Transition to screen 1 (!!!screen 1 is the main hub from which you can go to all screens - kind of redundant!!!)
 */
void Screen4View::selectPawn(){
	if(player_struct->is_ai_player){
		return;
	}
	game_info.selected_pawn = counter - 1;
	game_info.current_event = PAWN_SELECTED;

	static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
}

/*
 * Executes 60x per second (60Hz)
 * ----------------  Function  ----------------
 * Makes finished pawns not accessible
 */
void Screen4View::handleTickEvent(){
	// Switch to results screen when the game stage is finish
	if(game_info.game_stage == FINISH){
		game_info.finish_milis = miliseconds;
		static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen5ScreenNoTransition();
	}

	// Skip this screen if we don't roll a 6 and there is no pawn on board
	if(game_info.rolled_number != 6 && (player_struct->pawns_at_start + player_struct->pawns_in_finish == 4)){
		game_info.selected_pawn = counter - 1;
		game_info.current_event = PAWN_SELECTED;

		static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
	}


	tick++;
	// Delay event (for arrow left & right)
	handleArrowAnimation(delay_event);

	// If the pawn is in finish you cannot access it
	// Not the best way to handle it since we check for finish 60 times per second
	for(uint8_t pawn = 0; pawn < 4; pawn++){
		// Save the position of the iterated pawn
		uint8_t pawn_position = player_struct->position[pawn];

		// Sets the visibility to low if the pawn is in finish
		if(pawn_position == IN_FINISH_POSITION){
			switch(pawn){
				case 0:
					pawnImage1.setAlpha(50);
					pawnImage1.invalidate();
					break;
				case 1:
					pawnImage2.setAlpha(50);
					pawnImage2.invalidate();
					break;
				case 2:
					pawnImage3.setAlpha(50);
					pawnImage3.invalidate();
					break;
				case 3:
					pawnImage4.setAlpha(50);
					pawnImage4.invalidate();
					break;
			}
		}
	}
}

/*
 * Sets alpha of pawnImages
 * ----------------  Function  ----------------
 * Based on the pawn makes alpha adjustments
 * Contains logic to prevent alpha blinking (changing alpha of images that are already in finish)
 */
void Screen4View::setPawnAlpha(uint8_t pawn){
	Image* pawnImages[] = {&pawnImage1, &pawnImage2, &pawnImage3, &pawnImage4};		// Pointer array of all pawn images

	for(uint8_t i = 0; i < 4; ++i){	// Apparently ++i is better to use then i++
		if(player_struct->position[i] != IN_FINISH_POSITION){
			pawnImages[i]->setAlpha((pawn == i + 1) ? 255 : 150); // Sets the alpha of images that are not in finish
		}
		pawnImages[i]->invalidate();
	}
}


void Screen4View::handleArrowAnimation(uint8_t arrow){
	if(delay_event == AI_PAWN_SELECTION){
		if(tick - last_tick_event >= 20){	// .4 s delay
			game_info.current_event = PAWN_SELECTED;
			delay_event = NO_ANIMATION;

			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
		}
	}

	Image* arrowImages[] = {&imageLeft, &imageRight};
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

		arrowImages[image]->setVisible(true);
		arrowImages[image]->invalidate();

		delay_event = NO_ANIMATION;
	}
}
