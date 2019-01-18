//
// Created by Denis Wagner on 1/17/19.
//

#ifndef PONG_ARROWKEYPLAYER_HPP
#define PONG_ARROWKEYPLAYER_HPP

#include "../views/playfield/Paddle.hpp"

class ArrowKeyPlayer : public Paddle {
public:
    ArrowKeyPlayer( Side side );
    virtual void eventHandler( const sf::Event& event ) override;
};

#endif //PONG_ARROWKEYPLAYER_HPP
