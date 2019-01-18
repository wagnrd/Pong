//
// Created by Denis Wagner on 1/17/19.
//

#ifndef PONG_WSPLAYER_HPP
#define PONG_WSPLAYER_HPP

#include "../views/playfield/Paddle.hpp"

class WSPlayer : public Paddle {
public:
    WSPlayer( Side side );
    virtual void eventHandler( const sf::Event& event ) override;
};

#endif //PONG_WSPLAYER_HPP
