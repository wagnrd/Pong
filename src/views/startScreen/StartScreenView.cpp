//
// Created by Denis Wagner on 1/15/19.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "StartScreenView.hpp"

StartScreenView::StartScreenView( std::shared_ptr<PlayfieldView> playfield )
        : playfield( playfield )
{
}

void StartScreenView::init()
{
    application->getWindow()->setFramerateLimit( 1 );

    // hard reset PlayfielView so a new game starts
    playfield->reset();

    const float windowMiddleWidth  = application->getWindowWidth() / 2;
    const float windowMiddleHeight = application->getWindowHeight() / 2;
    font.loadFromFile( "../bit5x5.ttf" );

    // init title text
    title.setString( "PONG" );
    title.setFont( font );
    title.setCharacterSize( 160 );

    float textMiddleWidth = title.getLocalBounds().width / 2;
    float textHeight      = title.getLocalBounds().height;

    title.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight - textHeight - 130 );

    // init inistruction text
    instructions.setString( "Enter - Start game\n"
                            "F - Toggle fullscreen\n"
                            "Esc - Exit/Pause game" );
    instructions.setFont( font );
    instructions.setCharacterSize( 50 );

    textMiddleWidth = instructions.getLocalBounds().width / 2;

    instructions.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight );
}

void StartScreenView::eventHandler( const sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Enter )
        {
            application->setNode( "Playfield" );
        }
        else if ( event.key.code == sf::Keyboard::F )
        {
            fullscreen = !fullscreen;
            application->setFullscreen( fullscreen );
            application->getWindow()->setFramerateLimit( 1 );
            init();
        }
        else if ( event.key.code == sf::Keyboard::Escape )
        {
            application->getWindow()->close();
        }
    }
}

void StartScreenView::draw( sf::RenderWindow& window )
{
    window.clear( sf::Color::Black );

    window.draw( title );
    window.draw( instructions );
}
