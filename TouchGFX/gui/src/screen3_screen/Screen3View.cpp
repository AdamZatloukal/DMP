#include <gui/screen3_screen/Screen3View.hpp>
#include <ColorUtils.hpp>	// For switching playerBox color

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
    game_info.current_event = ROLL_DICE;
    tick = 0;
    hasRolled = 0;

	setBoxColor(playerBox, game_info.current_player);

	// Rolls the dice if the current player is AI
	player_struct = select_player(game_info.current_player);
	if(player_struct->is_ai_player){
		delay_event = AI_ROLL;

		AIText.setVisible(true);
		AIText.invalidate();
	}


}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::handleTickEvent(){	// Called 60x per second (60Hz)
	if(delay_event == ROLL){
		delay_event = tick < 60 ? ROLL : NONE;	// Takes 1 second to be true
		tick++;

		if(delay_event == NONE){
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen4ScreenNoTransition();	//go to screen 4
		}
	}
	if(delay_event == AI_ROLL){		// This means if AI there will be 0.5s delay to roll and .5 delay to switch screens
		delay_event = tick < 30 ? AI_ROLL : NONE;
		tick++;

		if(delay_event == NONE){
			handleRollDice();
		}
	}
}

void Screen3View::rollDice()
{
	if(player_struct->is_ai_player){
		return;
	}
	handleRollDice(); // The routine is in a function just so it can be used when AI players play
}

void Screen3View::handleRollDice(){
	// Allows you to only roll once per turn
	if(!hasRolled){
		uint8_t number = roll_dice(1, 6);
		hasRolled = 1;
		game_info.rolled_number = number;	// Used in main.c

		diceAnimatedImage.setVisible(false);

		switch(number){
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
		diceAnimatedImage.invalidate();

		delay_event = ROLL;	// 1 second delay
	}
}
