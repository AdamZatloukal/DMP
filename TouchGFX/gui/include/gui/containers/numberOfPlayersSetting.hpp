#ifndef NUMBEROFPLAYERSSETTING_HPP
#define NUMBEROFPLAYERSSETTING_HPP

#include <gui_generated/containers/numberOfPlayersSettingBase.hpp>

class numberOfPlayersSetting : public numberOfPlayersSettingBase
{
public:
    numberOfPlayersSetting();
    virtual ~numberOfPlayersSetting() {}

    virtual void initialize();

    virtual void changeNumberOfPlayers(uint8_t num_of_players);
    virtual void hideArrow(uint8_t arrow);
    virtual void showArrow(uint8_t arrow);
    virtual void handleColorCircles(uint8_t num_of_players);
    virtual void hideText();
    virtual void showText();

protected:
    typedef enum{
    	ARROW_LEFT,
		ARROW_RIGHT
    }Arrow;
};

#endif // NUMBEROFPLAYERSSETTING_HPP
