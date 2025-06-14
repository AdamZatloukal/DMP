#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

#include <main.h>
#include <clovece_nezlob_se.h>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();		//This function is called 60 times per second

    virtual void rollDice();
    virtual void handleRollDice();
    virtual void setImageVisibility(bool state, uint8_t number);

protected:
    typedef enum{
    	ROLL,
		AI_ROLL,
		NONE
    }DelayEvent;
    uint8_t delay_event = NONE;
    int tick;
    uint8_t hasRolled;
    Player* player_struct;
    uint8_t number_of_rolls = 0;
    bool can_roll_again = true;
};

#endif // SCREEN3VIEW_HPP
