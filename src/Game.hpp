//
// Created by Denis Wagner on 1/11/19.
//

#ifndef PONG_GAME_HPP
#define PONG_GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <Application.hpp>

class Game : public Application {
public:
    Game( std::string windowText, float windowWidth, float windowHeight );
    virtual void init() override;
};

#endif //PONG_GAME_HPP
