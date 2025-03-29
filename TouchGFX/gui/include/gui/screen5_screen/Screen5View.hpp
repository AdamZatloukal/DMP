#ifndef SCREEN5VIEW_HPP
#define SCREEN5VIEW_HPP

#include <gui_generated/screen5_screen/Screen5ViewBase.hpp>
#include <gui/screen5_screen/Screen5Presenter.hpp>

#include <clovece_nezlob_se.h>
#include <main.h>
#include <ColorUtils.hpp>

class Screen5View : public Screen5ViewBase
{
public:
    Screen5View();
    virtual ~Screen5View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollDown();

    virtual void handleBoxAnimation();

    virtual void handleTickEvent();
protected:
    typedef enum{
    	SHOW_BOX,
		HIDE_BOX
    }BOX_STATE;

    Player* player_struct;
    int tick;
    int iteration;
    int last_tick_event;
};

#endif // SCREEN5VIEW_HPP
