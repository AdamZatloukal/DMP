#include <gui/screen1_screen/Screen1View.hpp>
#include  <main.h>
#include  <milis.h>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent(){
	/*
	 * DONE FOR TESTING POURPOSES!!!
	switch (game_info.current_event){
		case ROLL_DICE:		// Dice screen
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen3ScreenNoTransition();
			break;
		case SELECT_PAWN:		// Select pawn screen
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen4ScreenNoTransition();
			break;
		case MENU:		// Menu
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen2ScreenNoTransition();
			break;
		case FINISH_GAME:
			game_info.finish_milis = miliseconds;
			static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen5ScreenNoTransition();
			break;
		default:
			break;

	}
	*/
}
