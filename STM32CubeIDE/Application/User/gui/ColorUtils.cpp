#include "ColorUtils.hpp"

/*
 * Sets the color of PlayerBox based on the current player
 * Parameters:
 * box - reference to box object you want to change the color of
 * player - player whose turn it is
 */
void setBoxColor(touchgfx::Box& box,uint8_t player){			// First argument is a reference to an already existing box object
	 switch (player){
	    case 1:
	        box.setColor(touchgfx::Color::getColorFromRGB(200, 0, 0)); 		// Player 1 - RED
	        break;
	    case 2:
	        box.setColor(touchgfx::Color::getColorFromRGB(0, 0, 200)); 		// Player 2 - BLUE
	        break;
	    case 3:
	        box.setColor(touchgfx::Color::getColorFromRGB(200, 200, 0)); 	// Player 3 - YELLOW
	        break;
	    case 4:
	        box.setColor(touchgfx::Color::getColorFromRGB(0, 200, 0)); 		// Player 4 - GREEN
	        break;
	    default:
	        break;
	    }

	 box.invalidate();
}

/*
 * Sets the color of a circle based on the player
 * Parameters:
 * circle_painter - circle painter object
 * circle - circle object
 * player - player whom colors we want the circle to be
 */
void setCircleColor(touchgfx::PainterRGB565& circle_painter ,touchgfx::Circle& circle, uint8_t player){
	switch(player){
		case 1:
			circle_painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
			break;
		case 2:
			circle_painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
			break;
		case 3:
			circle_painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 0));
			break;
		case 4:
			circle_painter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
			break;

	}

	circle.invalidate();
}
