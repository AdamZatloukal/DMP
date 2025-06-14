#include <gui/screen5_screen/Screen5View.hpp>

Screen5View::Screen5View()
{

}

void Screen5View::setupScreen()
{
    Screen5ViewBase::setupScreen();

    // Sets the values of results
    tick = 0;
    iteration = 0;
    last_tick_event = 0;

    for(int player = 1; player <= game_info.number_of_players; ++player){
    	Player* player_struct = select_player(player);

    	// If the player hasnt finished it means he is last -> set the player number as the last index in the results array (depends on the number of players)
    	if(!player_struct->is_finished){
    		game_info.results[game_info.number_of_players - 1] = player;
    	}
		else{
			game_info.results[player_struct->finish_position - 1] = player;	// For example if a player finished third the player number would be at index [2]
		}
    }

    playerResultContainer* result_containers[4] = {&playerResultContainer1, &playerResultContainer2, &playerResultContainer3, &playerResultContainer4};

    // Show only containers of how many players are playing
	for(int container = 0; container < 4; ++container){
		if(container + 1 > game_info.number_of_players){
			result_containers[container]->setVisible(false);
		}
	}

    /*
     * 1st - index 0, 2nd index 1, ...
     */
    // Iterates over each container
    for(int container = 0; container < game_info.number_of_players; ++container){
    	//Sets the player from results (1st - 0, 2nd - 1, ...)
    	uint8_t player = game_info.results[container];
    	result_containers[container]->setResultPositionTextAndColor(player, container + 1);
    }
}

void Screen5View::tearDownScreen()
{
    Screen5ViewBase::tearDownScreen();
}

void Screen5View::scrollDown(){
	static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen6ScreenNoTransition(); // REMOVE!!! THIS IS JUST FOR DEBUGGING POURPOSES
}

void Screen5View::handleTickEvent(){
	tick++;
	handleBoxAnimation();
}


void Screen5View::handleBoxAnimation(){

	/*
	 * every 2/3 of a second changes the box visibility
	 */
	if(tick - last_tick_event >= 40){
		last_tick_event = tick;

		if(iteration % 2 == 0){
			downButtonBox.setVisible(true);
		}
		else{
			// Hide bow
			downButtonBox.setVisible(false);
		}

		downButtonBox.invalidate();

		iteration++;
	}
}
