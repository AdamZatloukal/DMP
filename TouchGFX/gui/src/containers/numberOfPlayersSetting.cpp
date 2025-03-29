#include <gui/containers/numberOfPlayersSetting.hpp>

numberOfPlayersSetting::numberOfPlayersSetting()
{

}

void numberOfPlayersSetting::initialize()
{
    numberOfPlayersSettingBase::initialize();
}

void numberOfPlayersSetting::changeNumberOfPlayers(uint8_t num_of_players){
	Unicode::snprintf(playerTextCounterBuffer, PLAYERTEXTCOUNTER_SIZE, "%d", num_of_players);
	playerTextCounter.invalidate();
}


/*
 * Hides arrowLeft & arrowRight
 * Parameters:
 * arrow - ARROW_LEFT (0) or ARROW_RIGHT (1)
 */
void numberOfPlayersSetting::hideArrow(uint8_t arrow){
	if(arrow == ARROW_LEFT){
		arrowLeft.setVisible(false);
		arrowLeft.invalidate();
	}
	else if(arrow == ARROW_RIGHT){
		arrowRight.setVisible(false);
		arrowRight.invalidate();
	}
}

/*
 * Shows arrowLeft & arrowRight
 * Parameters:
 * arrow - ARROW_LEFT (0) or ARROW_RIGHT (1)
 */
void numberOfPlayersSetting::showArrow(uint8_t arrow){
	if(arrow == ARROW_LEFT){
		arrowLeft.setVisible(true);
		arrowLeft.invalidate();
	}
	else if(arrow == ARROW_RIGHT){
		arrowRight.setVisible(true);
		arrowRight.invalidate();
	}
}

/*
 * Call in screen2View so you can get the number of players
 */
void numberOfPlayersSetting::handleColorCircles(uint8_t num_of_players){
	Circle* circles[] = {&redCircle, &blueCircle, &yellowCircle, &greenCircle};
	uint8_t player = 0;

	// Makes all circles invisible
	for(uint8_t i = 0; i < 4 ;++i){
		circles[i]->setVisible(false);
		circles[i]->invalidate();
	}


	// Makes visible only some of the circles (depends on how many players are playing)
	do{
		circles[player]->setVisible(true);
		circles[player]->invalidate();

		player++;
	}while(player < num_of_players);
}

void numberOfPlayersSetting::hideText(){
	playerTextCounter.setVisible(false);
	playerTextCounter.invalidate();
}

void numberOfPlayersSetting::showText(){
	playerTextCounter.setVisible(true);
	playerTextCounter.invalidate();
}
