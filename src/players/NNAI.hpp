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
    std::vector<std::string> playfieldData;

public:
    NNAI( Side side );
    virtual void init() override;
    virtual void draw( sf::RenderWindow& window ) override;
    virtual void scored( Side side ) override;
    virtual void reflected( Side side ) override;

private:
    void calculateNextMove();
    std::string getSideString();
};

#endif //PONG_NNAI_HPP
