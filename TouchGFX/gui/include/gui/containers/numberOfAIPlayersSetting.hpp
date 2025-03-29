#ifndef NUMBEROFAIPLAYERSSETTING_HPP
#define NUMBEROFAIPLAYERSSETTING_HPP

#include <gui_generated/containers/numberOfAIPlayersSettingBase.hpp>

class numberOfAIPlayersSetting : public numberOfAIPlayersSettingBase
{
public:
    numberOfAIPlayersSetting();
    virtual ~numberOfAIPlayersSetting() {}

    virtual void initialize();

    virtual void changeNumberOfPlayers(uint8_t num_of_AI_players);

    virtual void hideArrow(uint8_t arrow);
    virtual void showArrow(uint8_t arrow);
    virtual void handleColorCircles(uint8_t num_of_players, uint8_t num_of_real_players);
    virtual void hideText();
    virtual void showText();

protected:
    typedef enum{
   		ARROW_LEFT,
   		ARROW_RIGHT
   	}Arrow;
};

#endif // NUMBEROFAIPLAYERSSETTING_HPP
