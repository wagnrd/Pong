//
// Created by Denis Wagner on 1/14/19.
//

#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <Node.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <boost/math/constants/constants.hpp>
#include <random>
#include "Paddle.hpp"

class PlayfieldView;

class Ball : public Node {
    PlayfieldView* playfieldView;

    const float     ballRadius   = 10;
    const float     ballSpeed    = 15;
    sf::CircleShape circle;
    int             waitCounter;

    std::mt19937_64                        rng;
    std::uniform_real_distribution<double> randomAngle{ 0, 360 };
    std::normal_distribution<double>       randomOffsetAngle{ 0, 10 };

    sf::Vector2f wallDirectionVector{ 1, 0 };
    sf::Vector2f paddleDirectionVector{ 0, 1 };
    sf::Vector2f moveVector{ ballSpeed, 0 };
    bool         collisionTop    = false;
    bool         collisionBottom = false;
    bool         collisionLeft   = false;
    bool         collisionRight  = false;

    std::shared_ptr<Paddle> leftPaddle;
    std::shared_ptr<Paddle> rightPaddle;

public:
    virtual void init() override;
    virtual void draw( sf::RenderWindow& window ) override;
    float getBallRadius();
    const sf::Vector2f& getPosition();
    const sf::Vector2f& getMoveVector();
};

#endif //PONG_BALL_HPP
