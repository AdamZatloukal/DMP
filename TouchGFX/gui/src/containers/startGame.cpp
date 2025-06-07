#include <gui/containers/startGame.hpp>

startGame::startGame()
{

}

void startGame::initialize()
{
    startGameBase::initialize();
}

void startGame::setJoystickBoxVisibility(bool visibility)
{
    joystickBox.setVisible(visibility);
    joystickBox.invalidate();
}