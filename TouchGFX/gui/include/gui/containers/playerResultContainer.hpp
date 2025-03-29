#ifndef PLAYERRESULTCONTAINER_HPP
#define PLAYERRESULTCONTAINER_HPP

#include <gui_generated/containers/playerResultContainerBase.hpp>

class playerResultContainer : public playerResultContainerBase
{
public:
    playerResultContainer();
    virtual ~playerResultContainer() {}

    virtual void initialize();

    virtual void setResultPositionTextAndColor(uint8_t player, uint8_t position);
protected:
};

#endif // PLAYERRESULTCONTAINER_HPP
