#ifndef STARTGAME_HPP
#define STARTGAME_HPP

#include <gui_generated/containers/startGameBase.hpp>

class startGame : public startGameBase
{
public:
    startGame();
    virtual ~startGame() {}

    virtual void initialize();
protected:
};

#endif // STARTGAME_HPP
