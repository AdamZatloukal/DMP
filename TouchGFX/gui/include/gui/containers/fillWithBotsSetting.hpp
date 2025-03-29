#ifndef FILLWITHBOTSSETTING_HPP
#define FILLWITHBOTSSETTING_HPP

#include <gui_generated/containers/fillWithBotsSettingBase.hpp>

class fillWithBotsSetting : public fillWithBotsSettingBase
{
public:
    fillWithBotsSetting();
    virtual ~fillWithBotsSetting() {}

    virtual void initialize();

    virtual void setButtonState(uint8_t button_state);
protected:
};

#endif // FILLWITHBOTSSETTING_HPP
