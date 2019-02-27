//
// Created by Denis Wagner on 1/14/19.
//

#ifndef PONG_PADDLE_HPP
#define PONG_PADDLE_HPP

#include <Node.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Side.hpp"

class Paddle : public Node {
    sf::RectangleShape rectangle;
    const float        paddleWidth  = 25;
    const float        paddleHeight = 100;
    const float        wallOffset   = 20;
    const float        speed        = 15;

protected:
    Side side;
    bool nextMoveUp                 = false;
    bool nextMoveDown               = false;

public:
    Paddle( Side side );
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;
    virtual void scored( Side side );
    virtual void reflected( Side side );

    void moveDown();
    void moveUp();
    const float getPaddleWidth() const;
    const float getPaddleHeight() const;
    const sf::Vector2f& getPosition() const;
    float getSpeed();
    float getWallOffset();
};

#endif //PONG_PADDLE_HPP
