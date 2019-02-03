//
// Created by Denis Wagner on 2/3/19.
//

#ifndef PONG_NNAI_HPP
#define PONG_NNAI_HPP

#include "../views/playfield/Paddle.hpp"
#include "../../OpenNN/opennn/data_set.h"
#include "../../OpenNN/opennn/neural_network.h"
#include "../../OpenNN/opennn/training_strategy.h"

class NNAI : public Paddle {
    OpenNN::DataSet          dataSet;
    OpenNN::NeuralNetwork    neuralNetwork;
    OpenNN::TrainingStrategy trainingStrategy;
    PlayfieldView* playfield;

public:
    NNAI( Side side );
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;

private:
    void calculateNextMove();
    void trainGatheredData();
};

#endif //PONG_NNAI_HPP
