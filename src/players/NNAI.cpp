//
// Created by Denis Wagner on 2/3/19.
//

#include "../views/playfield/PlayfieldView.hpp"
#include "NNAI.hpp"

NNAI::NNAI( Side side )
        : Paddle( side )
{
}

void NNAI::init()
{
    Paddle::init();

    playfield = static_cast<PlayfieldView*>(getParent());

    // clear playfieldDataRight.dat
    fstream playfieldDataFile;
    playfieldDataFile.open( "../data/playfieldData" + getSideString() + ".dat", ios::out | ios::trunc );
    playfieldDataFile.close();

    try
    {
        // Data set
        OpenNN::Variables* variablesPointer = dataSet.get_variables_pointer();

        // 4 inputs and 1 output
        variablesPointer->set( 4, 1 );

        // define in-/outputs
        variablesPointer->set_name( 0, "BallPositionX" );
        variablesPointer->set_name( 1, "BallPositionY" );
        variablesPointer->set_name( 2, "BallMoveX" );
        variablesPointer->set_name( 3, "BallMoveY" );
        variablesPointer->set_name( 4, "RealBallPosition" );

        OpenNN::Instances* instancesPointer = dataSet.get_instances_pointer();
        instancesPointer->set_training();

        OpenNN::Matrix<string> inputsInformation  = variablesPointer->get_inputs_information();
        OpenNN::Matrix<string> targetsInformation = variablesPointer->get_targets_information();

        // Neural network
        neuralNetwork.set( 4, 20, 1 );  // 20 hidden neurons work great
        //neuralNetwork.randomize_parameters_uniform( -100, 100 );
        neuralNetwork.get_multilayer_perceptron_pointer()
                     ->set_layer_activation_function( 0, OpenNN::PerceptronLayer::ActivationFunction::SoftSign );
        /*
        neuralNetwork.get_multilayer_perceptron_pointer()
                     ->set_layer_activation_function( 1, OpenNN::PerceptronLayer::ActivationFunction::RectifiedLinear );
        /
        neuralNetwork.get_multilayer_perceptron_pointer()
                     ->set_layer_activation_function( 2, OpenNN::PerceptronLayer::ActivationFunction::SoftSign );
        //*/
        // SoftSign is very good

        OpenNN::Inputs* inputsPointer = neuralNetwork.get_inputs_pointer();
        inputsPointer->set_information( inputsInformation );

        OpenNN::Outputs* outputsPointer = neuralNetwork.get_outputs_pointer();
        outputsPointer->set_information( targetsInformation );

        // Training strategy
        trainingStrategy = OpenNN::TrainingStrategy( &neuralNetwork, &dataSet );
        trainingStrategy.set_loss_method( OpenNN::TrainingStrategy::LossMethod::MEAN_SQUARED_ERROR );
        trainingStrategy.set_training_method( OpenNN::TrainingStrategy::TrainingMethod::QUASI_NEWTON_METHOD );

        OpenNN::QuasiNewtonMethod* quasiNewtonMethodPointer = trainingStrategy.get_quasi_Newton_method_pointer();
        quasiNewtonMethodPointer->set_display_period( 60 );
        quasiNewtonMethodPointer->set_maximum_epochs_number( 60 ); // 50 works great
        quasiNewtonMethodPointer->get_learning_rate_algorithm_pointer()
                                ->set_training_rate_method(
                                        OpenNN::LearningRateAlgorithm::LearningRateMethod::GoldenSection );
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

        // update playfieldData vector
        playfieldData.push_back(
                std::to_string( ballMiddlePositionX ) + " " + std::to_string( ballMiddlePositionY ) + " " +
                std::to_string( ballMoveVector.x ) + " " + std::to_string( ballMoveVector.y ) );
    }
    catch ( std::exception& e )
    {
        e.what();
    }
}

void NNAI::scored( Side side )
{
    if ( side == this->side )
    {
        playfieldData.clear();
        return;
    }

    std::string realBallPosition = std::to_string(
            playfield->getBall().getPosition().y + playfield->getBall().getBallRadius() );

    std::fstream playfieldDataFile;
    playfieldDataFile.open( "../data/playfieldData" + getSideString() + ".dat", ios::app );

    // add the ending ball position as training label
    for ( auto dataEntry : playfieldData )
        playfieldDataFile << dataEntry << " " << realBallPosition << "\n";


    ////// ACTUAL TRAINING //////
    // Training strategy
    dataSet.set_data_file_name( "../data/playfieldData" + getSideString() + ".dat" );
    dataSet.load_data();

    try
    {
        OpenNN::TrainingStrategy::Results trainingStrategyResults = trainingStrategy.perform_training();
    }
    catch ( std::exception& e )
    {
        std::cout << e.what() << std::endl;
    }

    // save current neural network state to a file
    neuralNetwork.save( "../data/neuralNetwork" + getSideString() + ".xml" );
    neuralNetwork.save_expression( "../data/neuralNetworkExpression" + getSideString() + ".txt" );

    // clear old data from playfieldData vector
    playfieldData.clear();
}

void NNAI::reflected( Side side )
{
    playfieldData.clear();
    std::cout << "Reflected from  " << ( side == Side::RIGHT ? "Right" : "Left" ) << std::endl;
}

std::string NNAI::getSideString()
{
    return side == Side::LEFT ? "Left" : "Right";
}
