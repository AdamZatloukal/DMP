#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void incrementValue();
    virtual void decrementValue();
    virtual void select();

    virtual void scrollUp();
    virtual void scrollDown();

    virtual void selectWidget(uint8_t widget);

    virtual void handleNumberOfPlayersTotal(uint8_t handle_type);
    virtual void handleFillWithBots(uint8_t button_state);
    virtual void handleNumberOfPlayersReal(uint8_t handle_type);
    virtual void handleNumberOfPlayersAI(uint8_t handle_type);

    virtual void handleArrowAnimation();

    virtual void handleTickEvent();


protected:
    uint8_t num_of_players = 4;
    uint8_t state = BUTTON_OFF;

    typedef enum{
		NUMBER_OF_PLAYERS_AI,		//0
		NUMBER_OF_PLAYERS_REAL,		//1
		TOGGLE_AI_PLAYERS,			//2
    	NUMBER_OF_PLAYERS_TOTAL,	//3
		START_GAME,					//4
    }CurrentWidget;

    typedef enum{
    	INCREMENT,
		DECREMENT
    }HandleType;

    typedef enum{
		ARROW_LEFT_ANIMATION,
		ARROW_RIGHT_ANIMATION,
		TEXT_ANIMATION,
		SCROLL_UP_ANIMATION,
		SCROLL_DOWN_ANIMATION,
		NO_ANIMATION
	}DelayEvent;

	typedef enum{
		BUTTON_ON,
		BUTTON_OFF
	}ButtonState;

	uint8_t delay_event = NO_ANIMATION;
	int tick;
	int last_tick_event;
	int iterations;

    uint8_t current_widget = NUMBER_OF_PLAYERS_TOTAL;
    int scroll_number = 4; // Depends on the number of setting widgets

    // These conditions must always be true
    uint8_t num_of_real_players = num_of_players;
    int num_of_AI_players = 0;

# define NUMBER_OF_SETTINGS 4 // 0 - 4
};

#endif // SCREEN2VIEW_HPP
