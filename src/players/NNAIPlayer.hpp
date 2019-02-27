//
// Created by Denis Wagner on 2/26/19.
//

#ifndef PONG_NNAIPLAYER_HPP
#define PONG_NNAIPLAYER_HPP

#include "../views/playfield/Paddle.hpp"
#include "../../OpenNN/opennn/neural_network.h"
#include "Skill.hpp"

class PlayfieldView;

class NNAIPlayer : public Paddle {
    OpenNN::NeuralNetwork neuralNetwork;
    Skill                 skill;
    PlayfieldView* playfield;

public:
    NNAIPlayer( Side side, Skill skill );
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;

    std::string getSkillString();
    void calculateNextMove();
};

#endif //PONG_NNAIPLAYER_HPP
