//
// Created by Denis Wagner on 1/14/19.
//

#include "Paddle.hpp"

Paddle::Paddle( Side side )
        : side( side )
{
}

void Paddle::init()
{
    const float windowWidth  = application->getWindowWidth();
    const float windowHeight = application->getWindowHeight();

    rectangle.setSize( sf::Vector2f( paddleWidth, paddleHeight ) );

    if ( side == Side::LEFT )
        rectangle.setPosition( wallOffset, windowHeight / 2 - paddleHeight / 2 );
    else
        rectangle.setPosition( windowWidth - ( wallOffset + paddleWidth ), windowHeight / 2 - paddleHeight / 2 );
}

void Paddle::eventHandler( const sf::Event& event )
{
    Node::eventHandler( event );
}

void Paddle::draw( sf::RenderWindow& window )
{
    if ( nextMoveUp )
        moveUp();
    else if ( nextMoveDown )
        moveDown();

    window.draw( rectangle );
}

void Paddle::moveUp()
{
    rectangle.move( 0, -speed );

    const float rectangleY = rectangle.getPosition().y;
    const float rectangleX = rectangle.getPosition().x;

    if ( rectangleY < 0 )
        rectangle.setPosition( rectangleX, 0 );
}

void Paddle::moveDown()
{
    rectangle.move( 0, speed );

    const float windowHeight = application->getWindowHeight();
    const float rectangleY   = rectangle.getPosition().y;
    const float rectangleX   = rectangle.getPosition().x;

    if ( rectangleY + paddleHeight > windowHeight )
        rectangle.setPosition( rectangleX, windowHeight - paddleHeight );
}

const float Paddle::getPaddleWidth() const
{
    return paddleWidth;
}

const float Paddle::getPaddleHeight() const
{
    return paddleHeight;
}

const sf::Vector2f& Paddle::getPosition() const
{
    return rectangle.getPosition();
}

float Paddle::getSpeed()
{
    return speed;
}

void Paddle::scored( Side side )
{
}

void Paddle::reflected( Side side )
{
}

float Paddle::getWallOffset()
{
    return wallOffset;
}
