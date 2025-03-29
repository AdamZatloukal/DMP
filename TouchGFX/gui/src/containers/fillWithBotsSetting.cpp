#include <gui/containers/fillWithBotsSetting.hpp>

fillWithBotsSetting::fillWithBotsSetting()
{

}

void fillWithBotsSetting::initialize()
{
    fillWithBotsSettingBase::initialize();
}

void fillWithBotsSetting::setButtonState(uint8_t button_state){
	if(button_state == 1){
		toggleBotsButton.forceState(true);
	}
	else{
		toggleBotsButton.forceState(false);
	}

	toggleBotsButton.invalidate();
}
