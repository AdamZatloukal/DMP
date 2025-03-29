#include <gui/containers/playerResultContainer.hpp>
#include <ColorUtils.hpp>
#include<touchgfx/Utils.hpp>

playerResultContainer::playerResultContainer()
{

}

void playerResultContainer::initialize()
{
    playerResultContainerBase::initialize();
}

/*
 * Sets color and text of the cirlce and text widgets
 * Parameters:
 * player - based on the player sets its color
 * position - from the struct of the player
 */
void playerResultContainer::setResultPositionTextAndColor(uint8_t player, uint8_t position){
	setCircleColor(playerColorCirclePainter, playerColorCircle, player);

	Unicode::snprintf(positionTextBuffer, POSITIONTEXT_SIZE, "%d", position);
	positionText.invalidate();
}

