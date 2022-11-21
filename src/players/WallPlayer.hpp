//
// Created by Denis Wagner on 21/11/22.
//

#ifndef PONG_WALLPLAYER_HPP
#define PONG_WALLPLAYER_HPP

#include "../views/playfield/Paddle.hpp"

class WallPlayer : public Paddle {
public:
    explicit WallPlayer(Side side);
};

#endif //PONG_WALLPLAYER_HPP