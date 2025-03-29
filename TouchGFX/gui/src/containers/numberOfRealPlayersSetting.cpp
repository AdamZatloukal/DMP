#include <gui/containers/numberOfRealPlayersSetting.hpp>

numberOfRealPlayersSetting::numberOfRealPlayersSetting()
{

}

void numberOfRealPlayersSetting::initialize()
{
    numberOfRealPlayersSettingBase::initialize();
}

void numberOfRealPlayersSetting::changeNumberOfPlayers(uint8_t num_of_players){
	Unicode::snprintf(realPlayerTextCounterBuffer, REALPLAYERTEXTCOUNTER_SIZE, "%d", num_of_players);
	realPlayerTextCounter.invalidate();
}

/*
 * Hides arrowLeft & arrowRight
 * Parameters:
 * arrow - ARROW_LEFT (0) or ARROW_RIGHT (1)
 */
void numberOfRealPlayersSetting::hideArrow(uint8_t arrow){
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
void numberOfRealPlayersSetting::showArrow(uint8_t arrow){
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
void numberOfRealPlayersSetting::handleColorCircles(uint8_t num_of_players){
	Circle* circles[] = {&redCircle, &blueCircle, &yellowCircle, &greenCircle};
	uint8_t player = 0;

	// Makes all circles invisible
	for(uint8_t i = 0; i < 4 ;++i){
		circles[i]->setVisible(false);
		circles[i]->invalidate();
	}

	// Return if there is nothing to draw
	if(num_of_players == 0){
		return;
	}

	// Makes visible only some of the circles (depends on how many players are playing)
	do{
		circles[player]->setVisible(true);
		circles[player]->invalidate();

		player++;
	}while(player < num_of_players);
}

void numberOfRealPlayersSetting::hideText(){
	realPlayerTextCounter.setVisible(false);
	realPlayerTextCounter.invalidate();
}

void numberOfRealPlayersSetting::showText(){
	realPlayerTextCounter.setVisible(true);
	realPlayerTextCounter.invalidate();
}
