//
// Created by Denis Wagner on 1/17/19.
//

#ifndef PONG_MENUVIEW_HPP
#define PONG_MENUVIEW_HPP

#include <SFML/Graphics/Text.hpp>
#include <Node.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MenuView : public Node {
    sf::RectangleShape outerBackground;
    sf::RectangleShape innerBackground;
    sf::Text           title;
    sf::Text           instructions;
    sf::Font           fontTitle;
    sf::Font           fontInstruction;

public:
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;
};

#endif //PONG_MENUVIEW_HPP
