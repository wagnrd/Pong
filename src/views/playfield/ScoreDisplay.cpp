//
// Created by Denis Wagner on 1/14/19.
//

#include <iostream>
#include "ScoreDisplay.hpp"

ScoreDisplay::ScoreDisplay( Side side )
        : side( side )
{
}

void ScoreDisplay::init()
{
    score = 0;
    text.setString( "0" );
    scoreFont.loadFromFile( "../bit5x3.ttf" );
    text.setFont( scoreFont );
    text.setCharacterSize( 180 );
}

void ScoreDisplay::draw( sf::RenderWindow& window )
{
    constexpr float middleOffset = 80;
    constexpr float topOffset    = -30;
    float           windowWidth  = application->getWindowWidth();

    if ( side == Side::LEFT )
    {
        float textWidth = text.getGlobalBounds().width;
        text.setPosition( windowWidth / 2 - ( textWidth + middleOffset ), topOffset );
    }
    else
    {
        text.setPosition( windowWidth / 2 + middleOffset, topOffset );
    }

    window.draw( text );
}

void ScoreDisplay::setScore( int score )
{
    this->score = score;
    text.setString( std::to_string( score ) );
}

void ScoreDisplay::incrementScore( int deltaScore )
{
    score += deltaScore;
    text.setString( std::to_string( score ) );
}

int ScoreDisplay::getScore()
{
    return score;
}
