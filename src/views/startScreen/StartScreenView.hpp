//
// Created by Denis Wagner on 1/15/19.
//

#ifndef PONG_STARTSCREENVIEW_HPP
#define PONG_STARTSCREENVIEW_HPP

#include <Node.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../playfield/PlayfieldView.hpp"

class StartScreenView : public Node {
    sf::Text title;
    sf::Text instructions;
    sf::Font font;
    bool     fullscreen = false;

    std::shared_ptr<PlayfieldView> playfield;

public:
    StartScreenView( std::shared_ptr<PlayfieldView> playfield );
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;
};

#endif //PONG_STARTSCREENVIEW_HPP
