//
// Created by Denis Wagner on 2/18/19.
//

#include "SettingsView.hpp"
#include "../../players/WSPlayer.hpp"
#include "../../players/ArrowKeyPlayer.hpp"
#include "../../players/NNAI.hpp"
#include "../../players/NNAIPlayer.hpp"
#include "../../players/WallPlayer.hpp"

SettingsView::SettingsView( std::shared_ptr<PlayfieldView> playfieldView )
        : playfieldView( playfieldView )
{
}

void SettingsView::init()
{
    application->getWindow()->setFramerateLimit( 30 );

    const float windowMiddleWidth  = application->getWindowWidth() / 2;
    const float windowMiddleHeight = application->getWindowHeight() / 2;
    fontTitle.loadFromFile( "../bit5x5.ttf" );
    fontInstruction.loadFromFile( "../bit9x9.otf" );

    // title
    title.setString( "Settings" );
    title.setFont( fontTitle );
    title.setCharacterSize( 100 );

    float           textMiddleWidth = title.getLocalBounds().width / 2;
    float           textHeight      = title.getLocalBounds().height;
    constexpr float titleOffset     = 220;

    title.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight - textHeight - titleOffset );

    // instructions
    instructions.setCharacterSize( 43 );
    instructions.setLineSpacing( 1.3 );
    instructions.setFont( fontInstruction );
    instructions.setString( getInstructionsString() );

    constexpr float instructionOffset = 110;
    textMiddleWidth = instructions.getLocalBounds().width / 2;
    instructions.setPosition( windowMiddleWidth - textMiddleWidth, windowMiddleHeight - instructionOffset );
}

void SettingsView::eventHandler( const sf::Event& event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::F )
        {
            fullscreen = !fullscreen;
            application->setFullscreen( fullscreen );
            application->getWindow()->setFramerateLimit( 1 );
            init();
        }
        else if ( event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter )
        {
            application->setNode( "StartScreen" );
        }
        else if ( event.key.code == sf::Keyboard::Num1 )
        {
            if ( currentInstruction != 1 )
            {
                // Player vs. A.I. (Live training)
                playfieldView->setLeftPaddle( std::make_shared<NNAI>( Side::LEFT ) );
                playfieldView->setRightPaddle( std::make_shared<ArrowKeyPlayer>( Side::RIGHT ) );
                currentInstruction = 1;
            }
        }
        else if ( event.key.code == sf::Keyboard::Num2 )
        {
            if ( currentInstruction != 2 )
            {
                // Player vs. A.I. (Medium)
                playfieldView->setLeftPaddle( std::make_shared<NNAIPlayer>( Side::LEFT, Skill::EASY ) );
                playfieldView->setRightPaddle( std::make_shared<ArrowKeyPlayer>( Side::RIGHT ) );
                currentInstruction = 2;
            }
        }
        else if ( event.key.code == sf::Keyboard::Num3 )
        {
            if ( currentInstruction != 3 )
            {
                // Player vs. A.I. (Medium)
                playfieldView->setLeftPaddle( std::make_shared<NNAIPlayer>( Side::LEFT, Skill::MEDIUM ) );
                playfieldView->setRightPaddle( std::make_shared<ArrowKeyPlayer>( Side::RIGHT ) );
                currentInstruction = 3;
            }
        }
        else if ( event.key.code == sf::Keyboard::Num4 )
        {
            if ( currentInstruction != 4 )
            {
                // Player vs. A.I. (Hard)
                playfieldView->setLeftPaddle( std::make_shared<NNAIPlayer>( Side::LEFT, Skill::HARD ) );
                playfieldView->setRightPaddle( std::make_shared<ArrowKeyPlayer>( Side::RIGHT ) );
                currentInstruction = 4;
            }
        }
        else if ( event.key.code == sf::Keyboard::Num5 )
        {
            if ( currentInstruction != 5 )
            {
                // A.I. solo live training
                playfieldView->setLeftPaddle( std::make_shared<NNAI>( Side::LEFT ) );
                playfieldView->setRightPaddle( std::make_shared<WallPlayer>( Side::RIGHT ) );
                currentInstruction = 5;
            }
        }
        else if ( event.key.code == sf::Keyboard::Num6 )
        {
            if ( currentInstruction != 6 )
            {
                // Player vs. Player
                playfieldView->setLeftPaddle( std::make_shared<WSPlayer>( Side::LEFT ) );
                playfieldView->setRightPaddle( std::make_shared<ArrowKeyPlayer>( Side::RIGHT ) );
                currentInstruction = 6;
            }
        }
    }
}

void SettingsView::draw( sf::RenderWindow& window )
{
    window.clear();

    instructions.setString( getInstructionsString() );
    window.draw( instructions );
    window.draw( title );
}

std::string SettingsView::getInstructionsString()
{
    std::string tempText = "F - Toggle fullscreen\n"
                           "     (Not recommended for A.I.)\n\n";

    for ( int i = 0; i < enumeratingInstructions.size(); i++ )
    {
        tempText += "(" + std::to_string( i + 1 ) + ") ";

        if ( i == currentInstruction - 1 )
            tempText += instructionStartIndicator + enumeratingInstructions[i] + instructionEndIndicator;
        else
            tempText += enumeratingInstructions[i];

        tempText += '\n';
    }

    tempText += "\nESC/Enter - Back";

    return std::move( tempText );
}