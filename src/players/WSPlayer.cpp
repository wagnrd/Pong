//
// Created by Denis Wagner on 1/17/19.
//

#include "WSPlayer.hpp"

WSPlayer::WSPlayer( Side side )
        : Paddle( side )
{
}

void WSPlayer::eventHandler( const sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::W )
            nextMoveUp = true;
        else if ( event.key.code == sf::Keyboard::S )
            nextMoveDown = true;
    }
    else if ( event.type == sf::Event::KeyReleased )
    {
        if ( event.key.code == sf::Keyboard::W )
            nextMoveUp = false;
        else if ( event.key.code == sf::Keyboard::S )
            nextMoveDown = false;
    }
}
