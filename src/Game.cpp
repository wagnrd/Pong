//
// Created by Denis Wagner on 1/11/19.
//

#include "Game.hpp"
#include "views/playfield/PlayfieldView.hpp"
#include "views/startScreen/StartScreenView.hpp"
#include "views/menuView/MenuView.hpp"
#include "players/ArrowKeyPlayer.hpp"
#include "players/WSPlayer.hpp"

Game::Game( std::string windowText, float windowWidth, float windowHeight )
        : Application( std::move( windowText ), windowWidth, windowHeight )
{
}

void Game::init()
{
    auto arrowKeyPlayer = std::make_shared<ArrowKeyPlayer>( Side::RIGHT );
    auto wsPlayer       = std::make_shared<WSPlayer>( Side::LEFT );
    auto playfield      = std::make_shared<PlayfieldView>( wsPlayer, arrowKeyPlayer );

    addNode( "Playfield", playfield );
    addNode( "StartScreen", std::make_shared<StartScreenView>( playfield ) );
    addNode( "MenuView", std::make_shared<MenuView>() );
    setNode( "StartScreen" );
}

