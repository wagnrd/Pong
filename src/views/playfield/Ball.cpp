//
// Created by Denis Wagner on 1/14/19.
//

#include <iostream>
#include "../../../SFMLMath/SFMLMath.hpp"
#include "Ball.hpp"
#include "PlayfieldView.hpp"

void Ball::init()
{
    playfieldView = static_cast<PlayfieldView*>(parent);
    leftPaddle    = playfieldView->getLeftPaddle();
    rightPaddle   = playfieldView->getRightPaddle();

    circle.setRadius( ballRadius );
    circle.setPosition( application->getWindowWidth() / 2 - ballRadius,
                        application->getWindowHeight() / 2 - ballRadius );

    waitCounter = 0;

    // init moveVector for better debugging
    //moveVector = sf::Vector2f( ballSpeed, 0 );
    sf::rotate( moveVector, randomAngle( rng ) );
    //sf::rotate( moveVector, 150 );
}

void Ball::draw( sf::RenderWindow& window )
{
    // wait a couple of frames to not scare the player with balls coming out of nowhere
    // 60 frames = 1 second -> 120 frames = 2 seconds
    /*
    if ( ++waitCounter < 60 )
        return;
    else
        waitCounter = 60; // clamp to not cause an overflow
        */

    // detect ball out of playfield and reset/return
    sf::Vector2f    ballVector      = circle.getPosition();
    const float     windowWidth     = application->getWindowWidth();
    const float     windowHeight    = application->getWindowHeight();
    const float     ballDiameter    = 2 * ballRadius;
    constexpr float angleCorrection = 10;

    if ( ballVector.x + ballDiameter < leftPaddle->getPaddleWidth() + leftPaddle->getWallOffset() )
    {
        // notify paddles, that the ball went out of playfield
        leftPaddle->scored( Side::RIGHT );
        rightPaddle->scored( Side::RIGHT );

        playfieldView->incrementScore( Side::RIGHT );
        init();

        return;
    }
    else if ( ballVector.x > windowWidth - rightPaddle->getPaddleWidth() - rightPaddle->getWallOffset() )
    {
        // notify paddles, that the ball went out of playfield
        leftPaddle->scored( Side::LEFT );
        rightPaddle->scored( Side::LEFT );

        playfieldView->incrementScore( Side::LEFT );
        init();

        return;
    }

    // calculate reflection
    if ( collisionTop )
    {
        const double angle       = sf::getAngleBetween( moveVector, wallDirectionVector );
        double       offsetAngle = 0;

        // detect and correct ball angles that are too steep
        if ( angle < 105 && angle > 90 )
            offsetAngle = -angleCorrection;
        else if ( angle <= 90 && angle > 75 )
            offsetAngle = angleCorrection;

        sf::invert( sf::rotate( moveVector, 180 - 2 * angle + offsetAngle ) );
        collisionTop = false;
    }

    if ( collisionBottom )
    {
        const double angle       = sf::getAngleBetween( moveVector, wallDirectionVector );
        double       offsetAngle = 0;

        // detect and correct ball angles that are too steep
        if ( angle < 105 && angle > 90 )
            offsetAngle = angleCorrection;
        else if ( angle <= 90 && angle > 75 )
            offsetAngle = -angleCorrection;

        sf::invert( sf::rotate( moveVector, 180 + 2 * angle + offsetAngle ) );
        collisionBottom = false;
    }

    if ( collisionLeft )
    {
        const double angle = sf::getAngleBetween( moveVector, paddleDirectionVector );
        sf::invert( sf::rotate( moveVector, 180 + 2 * angle ) );
        collisionLeft = false;

        // notify paddles, that a collision occured
        leftPaddle->reflected( Side::LEFT );
        rightPaddle->reflected( Side::LEFT );
    }

    if ( collisionRight )
    {
        const double angle = sf::getAngleBetween( moveVector, paddleDirectionVector );
        sf::invert( sf::rotate( moveVector, 180 - 2 * angle + randomOffsetAngle( rng ) ) );
        collisionRight = false;

        // notify paddles, that a collision occured
        rightPaddle->reflected( Side::RIGHT );
    }

    // actually move the ball with the updated moveVector
    circle.move( moveVector );

    // detect wall collision and prevent clipping through
    ballVector = circle.getPosition();   // update after moving

    if ( ballVector.y < 0 )
    {
        ballVector.y = 0;
        collisionTop = true;
    }
    else if ( ballVector.y + ballDiameter > windowHeight )
    {
        ballVector.y = windowHeight - ballDiameter;
        collisionBottom = true;
    }

    // detect paddle collision and prevent clipping through
    sf::Vector2f  leftPaddleVector  = leftPaddle->getPosition();
    sf::Vector2f  rightPaddleVector = rightPaddle->getPosition();
    constexpr int ballTolerance     = 7;   // how much of the ball can clip through the edges of the paddle

    if ( ballVector.x <= leftPaddleVector.x + leftPaddle->getPaddleWidth() &&
         ballVector.x + ballDiameter >= leftPaddleVector.x + ballSpeed &&
         ballVector.y + ballRadius + ballTolerance > leftPaddleVector.y &&
         ballVector.y + ballTolerance < leftPaddleVector.y + leftPaddle->getPaddleHeight() )
    {
        ballVector.x = leftPaddleVector.x + leftPaddle->getPaddleWidth();
        collisionLeft = true;
    }

    if ( ballVector.x + ballDiameter >= rightPaddleVector.x &&
         ballVector.x + ballDiameter <= rightPaddleVector.x + ballSpeed &&
         ballVector.y + ballRadius + ballTolerance > rightPaddleVector.y &&
         ballVector.y + ballTolerance < rightPaddleVector.y + rightPaddle->getPaddleHeight() )
    {
        ballVector.x = rightPaddleVector.x - ballDiameter;
        collisionRight = true;
    }

    // apply the adjusted position to the ball
    circle.setPosition( ballVector );

    window.draw( circle );
}

const sf::Vector2f& Ball::getPosition()
{
    return circle.getPosition();
}

float Ball::getBallRadius()
{
    return ballRadius;
}

const sf::Vector2f& Ball::getMoveVector()
{
    return moveVector;
}
