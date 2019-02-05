//
// Created by Denis Wagner on 1/17/19.
//

#include "MenuView.hpp"

void MenuView::init()
{
    application->getWindow()->setFramerateLimit( 1 );

    const float     windowMiddleWidth     = application->getWindowWidth() / 2;
    const float     windowMiddleHeight    = application->getWindowHeight() / 2;
    const float     backgroundWidth       = 800;
    const float     backgroundHeight      = 385;
    const float     backgroundBorderWidth = 18;
    constexpr float backgroundOffset      = 36;
    font.loadFromFile( "../bit5x5.ttf" );

    // init background
    outerBackground.setSize( sf::Vector2f( backgroundWidth, backgroundHeight ) );
    outerBackground.setPosition( windowMiddleWidth - backgroundWidth / 2,
                                 windowMiddleHeight - backgroundHeight / 2 - backgroundOffset );
    outerBackground.setFillColor( sf::Color::White );
    innerBackground.setSize(
            sf::Vector2f( backgroundWidth - 2 * backgroundBorderWidth, backgroundHeight - 2 * backgroundBorderWidth ) );
    innerBackground.setPosition( windowMiddleWidth - ( backgroundWidth - 2 * backgroundBorderWidth ) / 2,
                                 windowMiddleHeight - ( backgroundHeight - 2 * backgroundBorderWidth ) / 2 -
                                 backgroundOffset );
    innerBackground.setFillColor( sf::Color::Black );

    // init title text
    title.setString( "Pause" );
    title.setFont( font );
    title.setCharacterSize( 130 );

    constexpr float titleOffset     = 130;
    float           textMiddleWidth = title.getLocalBounds().width / 2;
    float           textHeight      = title.getLocalBounds().height;

    title.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight - textHeight - titleOffset );

    // init inistruction text
    instructions.setString( "Enter - Resume game\n"
                            "Esc - Title screen" );
    instructions.setFont( font );
    instructions.setCharacterSize( 50 );

    textMiddleWidth = instructions.getLocalBounds().width / 2;

    instructions.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight );
}

void MenuView::eventHandler( const sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed )
    {

        if ( event.key.code == sf::Keyboard::Enter )
        {
            application->setNode( "Playfield" );
        }
        else if ( event.key.code == sf::Keyboard::Escape )
        {
            application->setNode( "StartScreen" );
        }
    }
}

void MenuView::draw( sf::RenderWindow& window )
{
    window.draw( outerBackground );
    window.draw( innerBackground );
    window.draw( title );
    window.draw( instructions );
}
