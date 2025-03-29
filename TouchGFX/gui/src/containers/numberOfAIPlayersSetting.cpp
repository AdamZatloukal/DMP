#include <gui/containers/numberOfAIPlayersSetting.hpp>

numberOfAIPlayersSetting::numberOfAIPlayersSetting()
{

}

void numberOfAIPlayersSetting::initialize()
{
    numberOfAIPlayersSettingBase::initialize();
}

void numberOfAIPlayersSetting::changeNumberOfPlayers(uint8_t num_of_AI_players){
	Unicode::snprintf(AIPlayerTextCounterBuffer, AIPLAYERTEXTCOUNTER_SIZE, "%d", num_of_AI_players);
	AIPlayerTextCounter.invalidate();
}

/*
 * Hides arrowLeft & arrowRight
 * Parameters:
 * arrow - ARROW_LEFT (0) or ARROW_RIGHT (1)
 */
void numberOfAIPlayersSetting::hideArrow(uint8_t arrow){
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
void numberOfAIPlayersSetting::showArrow(uint8_t arrow){
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
void numberOfAIPlayersSetting::handleColorCircles(uint8_t num_of_players, uint8_t num_of_real_players){
	Circle* circles[] = {&redCircle, &blueCircle, &yellowCircle, &greenCircle};
	uint8_t player = num_of_real_players;

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

void numberOfAIPlayersSetting::hideText(){
	AIPlayerTextCounter.setVisible(false);
	AIPlayerTextCounter.invalidate();
}

void numberOfAIPlayersSetting::showText(){
	AIPlayerTextCounter.setVisible(true);
	AIPlayerTextCounter.invalidate();
}
