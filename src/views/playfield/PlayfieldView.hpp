//
// Created by Denis Wagner on 1/14/19.
//

#ifndef PONG_PLAYFIELDVIEW_HPP
#define PONG_PLAYFIELDVIEW_HPP

#include <Node.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ScoreDisplay.hpp"
#include "Side.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

class PlayfieldView : public Node {
    std::vector<sf::RectangleShape> middleLineRectangles;
    bool                            isInitialized = false;

    // nodes
    ScoreDisplay            leftScore{ Side::LEFT };
    ScoreDisplay            rightScore{ Side::RIGHT };
    std::shared_ptr<Paddle> leftPaddle;
    std::shared_ptr<Paddle> rightPaddle;
    Ball                    ball;

public:
    PlayfieldView( std::shared_ptr<Paddle> leftPaddle, std::shared_ptr<Paddle> rightPaddle );
    virtual void init() override;
    virtual void draw( sf::RenderWindow& window ) override;
    virtual void eventHandler( const sf::Event& event ) override;
    void reset();
    void incrementScore( Side side );
    Ball& getBall();
    void setLeftPaddle( std::shared_ptr<Paddle> leftPaddle );
    void setRightPaddle( std::shared_ptr<Paddle> rightPaddle );
    const std::shared_ptr<Paddle>& getLeftPaddle() const;
    const std::shared_ptr<Paddle>& getRightPaddle() const;
};

#endif //PONG_PLAYFIELDVIEW_HPP
