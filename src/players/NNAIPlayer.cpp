//
// Created by Denis Wagner on 2/26/19.
//

#include "NNAIPlayer.hpp"
#include "../views/playfield/PlayfieldView.hpp"

// Medium: ~60 trainings with ~6.000 Data Entries
// Pro: ~300 trainings with ~35.000 Data Entries
// Nearly Perfect: ~570 trainings ~75.000 Data Entries
// Nearly Perfect2: ~1200 trainings ~165.000 Data Entries

NNAIPlayer::NNAIPlayer( Side side, Skill skill )
        : Paddle( side ), skill( skill )
{
}

void NNAIPlayer::init()
{
    Paddle::init();
    playfield = static_cast<PlayfieldView*>(getParent());

    neuralNetwork.load( "../data/save/neuralNetwork" + getSkillString() + "Left.xml" );
}

void NNAIPlayer::eventHandler( const sf::Event& event )
{
}

void NNAIPlayer::draw( sf::RenderWindow& window )
{
    // decisions will be calculated each frame
    calculateNextMove();

    // actually draw the paddle
    Paddle::draw( window );
}

void NNAIPlayer::calculateNextMove()
{
    const sf::Vector2f ballPosition   = playfield->getBall().getPosition();
    const sf::Vector2f ballMoveVector = playfield->getBall().getMoveVector();
    const float        ballRadius     = playfield->getBall().getBallRadius();

    // calculate the middle point of the ball
    const float ballMiddlePositionX   = ballPosition.x + ballRadius;
    const float ballMiddlePositionY   = ballPosition.y + ballRadius;
    // calculate the middle point of the paddle
    const float paddleMiddlePositionY = getPosition().y + getPaddleHeight() / 2;

    try
    {
        // create input vector
        OpenNN::Vector<double> inputs{ ballMiddlePositionX, ballMiddlePositionY, ballMoveVector.x, ballMoveVector.y };

        // calculate the decision
        OpenNN::Vector<double> outputs = neuralNetwork.get_multilayer_perceptron_pointer()
                                                      ->calculate_outputs( inputs.to_row_matrix() );

        // get result
        double newPaddleMiddlePositionY = outputs.get_first();

        // make the next move
        if ( paddleMiddlePositionY < newPaddleMiddlePositionY - getSpeed() )
        {
            nextMoveDown = true;
            nextMoveUp   = false;
        }
        else if ( paddleMiddlePositionY > newPaddleMiddlePositionY + getSpeed() )
        {
            nextMoveUp   = true;
            nextMoveDown = false;
        }
        else
        {
            nextMoveUp   = false;
            nextMoveDown = false;
        }
    }
    catch ( std::exception& e )
    {
        e.what();
    }
}

std::string NNAIPlayer::getSkillString()
{
    switch ( skill )
    {
        case Skill::EASY: return "Easy";
        case Skill::MEDIUM: return "Medium";
        case Skill::HARD: return "Hard";
    }
}

