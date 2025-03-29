#ifndef SCREEN4VIEW_HPP
#define SCREEN4VIEW_HPP

#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>
#include <main.h>
#include <clovece_nezlob_se.h>
#include <ColorUtils.hpp>
#include <milis.h>

class Screen4View : public Screen4ViewBase
{
public:
    Screen4View();
    virtual ~Screen4View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void incrementPawn();
    virtual void decrementPawn();
    virtual void selectPawn();
    virtual void handleTickEvent();
    virtual void setPawnAlpha(uint8_t pawn);
    virtual void handleArrowAnimation(uint8_t arrow);

protected:
    typedef enum{
		ARROW_LEFT_ANIMATION,
		ARROW_RIGHT_ANIMATION,
		AI_PAWN_SELECTION,
		NO_ANIMATION
	}DelayEvent;

    int counter;
    int tick;
    int last_tick_event;
    uint8_t pawn_position;
    Player* player_struct;
    uint8_t delay_event = NO_ANIMATION;
};

#endif // SCREEN4VIEW_HPP
