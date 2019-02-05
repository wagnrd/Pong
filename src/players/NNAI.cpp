//
// Created by Denis Wagner on 2/3/19.
//

#include "../views/playfield/PlayfieldView.hpp"
#include "NNAI.hpp"

// TODO: Perform training when the oponent has scored (in function 'scored()')
// TODO: Get Notified after each ball reflection

NNAI::NNAI( Side side )
        : Paddle( side )
{
}

void NNAI::init()
{
    Paddle::init();

    playfield = static_cast<PlayfieldView*>(getParent());

    try
    {
        // Data set
        dataSet.set_data_file_name( "../playfieldData.dat" );
        dataSet.load_data();

        OpenNN::Variables* variablesPointer = dataSet.get_variables_pointer();

        // 5 inputs and 1 output
        variablesPointer->set( 5, 1 );

        // define in-/outputs
        variablesPointer->set_name( 0, "BallPositionX" );
        variablesPointer->set_name( 1, "BallPositionY" );
        variablesPointer->set_name( 2, "BallMoveX" );
        variablesPointer->set_name( 3, "BallMoveY" );
        variablesPointer->set_name( 4, "PaddlePositionY" );
        variablesPointer->set_name( 5, "PredictedPositionY" );

        OpenNN::Instances* instancesPointer = dataSet.get_instances_pointer();
        instancesPointer->set_training();

        OpenNN::Matrix<string> inputsInformation  = variablesPointer->get_inputs_information();
        OpenNN::Matrix<string> targetsInformation = variablesPointer->get_targets_information();

        // Neural network
        neuralNetwork.set( 5, 5, 1 );  // 5 input neurons, 5 hidden neurons, 1 output neuron

        OpenNN::Inputs* inputsPointer = neuralNetwork.get_inputs_pointer();
        inputsPointer->set_information( inputsInformation );

        neuralNetwork.construct_scaling_layer();

        OpenNN::ScalingLayer* scalingLayerPointer = neuralNetwork.get_scaling_layer_pointer();
        scalingLayerPointer->set_scaling_methods( OpenNN::ScalingLayer::NoScaling );

        OpenNN::MultilayerPerceptron* multilayerPerceptronPointer = neuralNetwork.get_multilayer_perceptron_pointer();
        multilayerPerceptronPointer->set_layer_activation_function( 1, OpenNN::PerceptronLayer::Logistic );

        OpenNN::Outputs* outputsPointer = neuralNetwork.get_outputs_pointer();
        outputsPointer->set_information( targetsInformation );

        // Training strategy
        trainingStrategy = OpenNN::TrainingStrategy( &neuralNetwork, &dataSet );

        OpenNN::QuasiNewtonMethod* quasiNewtonMethodPointer = trainingStrategy.get_quasi_Newton_method_pointer();
        quasiNewtonMethodPointer->set_minimum_loss_decrease( 1.0e-4 );

        ////// ACTUAL TRAINING //////
        //dataSet.load_data();
        //OpenNN::TrainingStrategy::Results trainingStrategyResults = trainingStrategy.perform_training();
    }
    catch ( std::exception& e )
    {
        cerr << e.what() << endl;
    }
}

void NNAI::draw( sf::RenderWindow& window )
{
    // decisions will be calculated each frame
    calculateNextMove();

    // actually draw the paddle
    Paddle::draw( window );
}

void NNAI::calculateNextMove()
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
        OpenNN::Vector<double> inputs{ ballMiddlePositionX, ballMiddlePositionY, ballMoveVector.x, ballMoveVector.y,
                                       paddleMiddlePositionY };

        // calculate the decision
        OpenNN::Vector<double> outputs = neuralNetwork.calculate_outputs( OpenNN::Matrix<double>{ inputs } );

        // get result
        double newPaddleMiddlePositionY = outputs.get_first();

        // make the next move
        if ( paddleMiddlePositionY <= newPaddleMiddlePositionY - getSpeed() )
        {
            nextMoveDown = true;
            nextMoveUp   = false;
        }
        else if ( paddleMiddlePositionY >= newPaddleMiddlePositionY + getSpeed() )
        {
            nextMoveUp   = true;
            nextMoveDown = false;
        }
        else
        {
            nextMoveUp   = false;
            nextMoveDown = false;
        }

        // update playfieldData vector
        playfieldData.emplace_back( std::to_string( ballMiddlePositionX ) + " " +
                                    std::to_string( ballMiddlePositionY ) + " " +
                                    std::to_string( ballMoveVector.x ) + " " +
                                    std::to_string( ballMoveVector.y ) + " " +
                                    std::to_string( paddleMiddlePositionY ) + " " +
                                    std::to_string( newPaddleMiddlePositionY ) );
    }
    catch ( std::exception& e )
    {
        e.what();
    }
}

void NNAI::scored( Side side )
{
    if ( side == Side::LEFT )
        return;

    std::string realBallPosition = std::to_string( playfield->getBall().getPosition().y );

    std::fstream playfieldDataFile;
    playfieldDataFile.open( "../playfieldData.dat", ios::out );

    // add the ending ball position as training label
    if ( !playfieldDataFile )
    {
        std::cerr << "File 'playfieldData.dat' couldn't be found. Exiting..." << std::endl;
        application->getWindow()->close();
    }

    for ( auto dataEntry : playfieldData )
        playfieldDataFile << dataEntry << " " << realBallPosition << "\n";

    // clear old data from playfieldData vector
    playfieldData.clear();
}
