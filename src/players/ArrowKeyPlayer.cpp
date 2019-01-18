//
// Created by Denis Wagner on 1/17/19.
//

#include "ArrowKeyPlayer.hpp"

ArrowKeyPlayer::ArrowKeyPlayer( Side side )
        : Paddle( side )
{
}

void ArrowKeyPlayer::eventHandler( const sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Up )
            nextMoveUp = true;
        else if ( event.key.code == sf::Keyboard::Down )
            nextMoveDown = true;
    }
    else if ( event.type == sf::Event::KeyReleased )
    {
        if ( event.key.code == sf::Keyboard::Up )
            nextMoveUp = false;
        else if ( event.key.code == sf::Keyboard::Down )
            nextMoveDown = false;
    }
}
