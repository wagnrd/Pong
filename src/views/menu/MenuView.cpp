//
// Created by Denis Wagner on 1/17/19.
//

#include "MenuView.hpp"

void MenuView::init()
{
    application->getWindow()->setFramerateLimit( 30 );

    const float     windowMiddleWidth     = application->getWindowWidth() / 2;
    const float     windowMiddleHeight    = application->getWindowHeight() / 2;
    const float     backgroundWidth       = 800;
    const float     backgroundHeight      = 400;
    const float     backgroundBorderWidth = 15;
    constexpr float backgroundOffset      = 33;
    fontTitle.loadFromFile( "../bit5x5.ttf" );
    fontInstruction.loadFromFile( "../bit9x9.otf" );

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
    title.setFont( fontTitle );
    title.setCharacterSize( 130 );

    constexpr float titleOffset     = 120;
    float           textMiddleWidth = title.getLocalBounds().width / 2;
    float           textHeight      = title.getLocalBounds().height;

    title.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight - textHeight - titleOffset );

    // init inistruction text
    instructions.setString( "Enter - Resume game\n"
                            "Esc - Title screen" );
    instructions.setFont( fontInstruction );
    instructions.setLineSpacing( 1.3 );
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
