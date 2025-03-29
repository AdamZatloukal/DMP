#include <gui/screen6_screen/Screen6View.hpp>
#include <clovece_nezlob_se.h> // Needed for player_struct
#include <main.h>		// We need the game_info struct from it
#include <milis.h> 		// Used for getting time
#include <touchgfx/Utils.hpp>
#include <math.h>
#include <gui/screen5_screen/Screen5View.hpp>

Screen6View::Screen6View()
{

}

void Screen6View::setupScreen()
{
    Screen6ViewBase::setupScreen();

    // Only show stats of players that are playing


    if(game_info.number_of_players == 2){
    	thirdPlayerTimeText.setVisible(false);
    	thirdPlayerEndTimeTextCounter.setVisible(false);
    	secondPlayerTimeText.setVisible(false);
    	secondPlayerEndTimeTextCounter.setVisible(false);
    	secondPlayerTimeText.invalidate();
		secondPlayerEndTimeTextCounter.invalidate();
    	thirdPlayerTimeText.invalidate();
    	thirdPlayerEndTimeTextCounter.invalidate();
    }
    if(game_info.number_of_players == 3){
		thirdPlayerTimeText.setVisible(false);
		thirdPlayerEndTimeTextCounter.setVisible(false);
		thirdPlayerTimeText.invalidate();
		thirdPlayerEndTimeTextCounter.invalidate();

    }


    tick = 0;
    last_tick_event = 0;
    iterations = 0;

    setGameStats();
}

void Screen6View::tearDownScreen()
{
    Screen6ViewBase::tearDownScreen();
}

void Screen6View::scrollUp(){
	static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen5ScreenNoTransition();
}

void Screen6View::restartGame(){
	NVIC_SystemReset();
}

void Screen6View::handleTickEvent(){
	tick++;
	handleBoxAnimation();
}

void Screen6View::handleBoxAnimation(){
	// Changes the visibility of the box every 2/3 of a second
	if(tick - last_tick_event >= 40){
		last_tick_event = tick;

		if(iterations % 2 == 0){
			upButtonBox.setVisible(true);
			centerButtonBox.setVisible(true);
		}
		else{
			upButtonBox.setVisible(false);
			centerButtonBox.setVisible(false);
		}

		upButtonBox.invalidate();
		centerButtonBox.invalidate();

		iterations++;
	}
}

void Screen6View::setGameStats(){
	// Set number of total rolls
	Unicode::snprintf(numOfRollsTextCounterBuffer, NUMOFROLLSTEXTCOUNTER_SIZE, "%d", game_info.number_of_rolls);
	numOfRollsTextCounter.invalidate();

	// Set number of set pawns
	Unicode::snprintf(numOfPawnsSetOnBoardTextCounterBuffer, NUMOFPAWNSSETONBOARDTEXTCOUNTER_SIZE, "%d", game_info.number_of_set_pawns);
	numOfPawnsSetOnBoardTextCounter.invalidate();

	// Set number of kicked pawns
	Unicode::snprintf(numOfPawnsKickedTextCounterBuffer, NUMOFPAWNSKICKEDTEXTCOUNTER_SIZE, "%d", game_info.number_of_kicked_pawns);
	numOfPawnsKickedTextCounter.invalidate();

	// Set total time
	int total_time_seconds = game_info.finish_milis / 1000;
	int total_time_minutes = total_time_seconds / 60;
	total_time_seconds = total_time_seconds % 60;

	Unicode::snprintf(totalGameTimeTextCounterBuffer1, TOTALGAMETIMETEXTCOUNTERBUFFER1_SIZE, "%d", total_time_minutes);
	Unicode::snprintf(totalGameTimeTextCounterBuffer2, TOTALGAMETIMETEXTCOUNTERBUFFER2_SIZE, "%d", total_time_seconds);

	totalGameTimeTextCounter.invalidate();

	// Set first player finish time
	Player* player_struct = select_player(game_info.results[0]); // Gets the struct of the player that finished first
	int milis_player1 = player_struct->finished_time;

	int first_player_secs = milis_player1 / 1000;
	int first_player_mins = first_player_secs / 60;
	first_player_secs = first_player_secs % 60;

	Unicode::snprintf(firstPlayerEndTimeTextCounterBuffer1, FIRSTPLAYERENDTIMETEXTCOUNTERBUFFER1_SIZE, "%d", first_player_mins);
	Unicode::snprintf(firstPlayerEndTimeTextCounterBuffer2, FIRSTPLAYERENDTIMETEXTCOUNTERBUFFER2_SIZE, "%d", first_player_secs);
	firstPlayerEndTimeTextCounter.invalidate();

	// Set second player finish
	player_struct = select_player(game_info.results[1]); // Gets the struct of the player that finished second
	int milis_player2 = player_struct->finished_time;

	int second_player_secs = milis_player2 / 1000;
	int second_player_mins = second_player_secs / 60;
	second_player_secs = second_player_secs % 60;

	Unicode::snprintf(secondPlayerEndTimeTextCounterBuffer1, SECONDPLAYERENDTIMETEXTCOUNTERBUFFER1_SIZE, "%d", second_player_mins);
	Unicode::snprintf(secondPlayerEndTimeTextCounterBuffer2, SECONDPLAYERENDTIMETEXTCOUNTERBUFFER2_SIZE, "%d", second_player_secs);
	secondPlayerEndTimeTextCounter.invalidate();

	// Set third player finish
	player_struct = select_player(game_info.results[2]); // Gets the struct of the player that finished second
	int milis_player3 = player_struct->finished_time;

	int third_player_secs = milis_player3 / 1000;
	int third_player_mins = third_player_secs / 60;
	third_player_secs = third_player_secs % 60;

	Unicode::snprintf(thirdPlayerEndTimeTextCounterBuffer1, THIRDPLAYERENDTIMETEXTCOUNTERBUFFER1_SIZE, "%d", third_player_mins);
	Unicode::snprintf(thirdPlayerEndTimeTextCounterBuffer2, THIRDPLAYERENDTIMETEXTCOUNTERBUFFER2_SIZE, "%d", third_player_secs);
	thirdPlayerEndTimeTextCounter.invalidate();

}
