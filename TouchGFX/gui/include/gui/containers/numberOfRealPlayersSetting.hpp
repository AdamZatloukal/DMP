#ifndef NUMBEROFREALPLAYERSSETTING_HPP
#define NUMBEROFREALPLAYERSSETTING_HPP

#include <gui_generated/containers/numberOfRealPlayersSettingBase.hpp>

class numberOfRealPlayersSetting : public numberOfRealPlayersSettingBase
{
public:
    numberOfRealPlayersSetting();
    virtual ~numberOfRealPlayersSetting() {}

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

#endif // NUMBEROFREALPLAYERSSETTING_HPP
