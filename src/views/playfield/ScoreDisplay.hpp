//
// Created by Denis Wagner on 1/14/19.
//

#ifndef PONG_SCOREDISPLAY_HPP
#define PONG_SCOREDISPLAY_HPP

#include <Node.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Side.hpp"

class ScoreDisplay : public Node {
    sf::Text text;
    sf::Font scoreFont;
    Side     side;
    int      score;

public:
    ScoreDisplay( Side side );
    virtual void draw( sf::RenderWindow& window ) override;
    virtual void init() override;

    void setScore( int score );
    void incrementScore( int deltaScore );
    int getScore();
};

#endif //PONG_SCOREDISPLAY_HPP
