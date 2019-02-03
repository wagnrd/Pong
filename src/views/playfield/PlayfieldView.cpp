//
// Created by Denis Wagner on 1/14/19.
//

#include <iostream>
#include "PlayfieldView.hpp"

PlayfieldView::PlayfieldView( std::shared_ptr<Paddle> leftPaddle, std::shared_ptr<Paddle> rightPaddle )
        : paddle1( std::move( leftPaddle ) ), paddle2( std::move( rightPaddle ) )
{
}

void PlayfieldView::init()
{
    application->getWindow()->setFramerateLimit( 60 );

    if ( !isInitialized )
    {
        constexpr int   numberOfRectangles = 19;
        constexpr float rectangleWidth     = 20;
        const float     rectangleHeight    = application->getWindowHeight() / ( ( numberOfRectangles * 2 ) - 1 );

        for ( int i = 0; i <= numberOfRectangles; ++i )
        {
            sf::RectangleShape rectangle( sf::Vector2f( rectangleWidth, rectangleHeight ) );
            rectangle.setPosition( application->getWindowWidth() / 2 - rectangleWidth / 2, rectangleHeight * i * 2 );

            middleLineRectangles.emplace_back( std::move( rectangle ) );
        }

        ball.initChild( application, this );
        paddle1->initChild( application, this );
        paddle2->initChild( application, this );
        leftScore.initChild( application, this );
        rightScore.initChild( application, this );

        isInitialized = true;
    }
}

void PlayfieldView::reset()
{
    middleLineRectangles.clear();
    isInitialized = false;
    init();
}

void PlayfieldView::eventHandler( const sf::Event& event )
{
    if ( event.key.code == sf::Keyboard::Escape )
        application->setNode( "MenuView" );

    paddle2->eventHandler( event );
    paddle1->eventHandler( event );
}

void PlayfieldView::draw( sf::RenderWindow& window )
{
    window.clear( sf::Color::Black );

    paddle1->draw( window );
    paddle2->draw( window );
    ball.draw( window );
    leftScore.draw( window );
    rightScore.draw( window );

    // draw middle line
    for ( auto rectangle : middleLineRectangles )
        window.draw( rectangle );
}

void PlayfieldView::incrementScore( Side side )
{
    if ( side == Side::LEFT )
        leftScore.incrementScore( 1 );
    else
        rightScore.incrementScore( 1 );
}

Ball& PlayfieldView::getBall()
{
    return ball;
}
