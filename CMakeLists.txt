cmake_minimum_required(VERSION 3.13)

project(Pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics)
add_library(SFMLApp SHARED SFMLApp/Application.cpp SFMLApp/Application.hpp SFMLApp/Node.cpp SFMLApp/Node.hpp)
target_include_directories(SFMLApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFMLApp)

add_executable(Pong src/main.cpp src/Game.cpp src/Game.hpp src/views/playfield/Ball.cpp src/views/playfield/Ball.hpp src/views/playfield/PlayfieldView.cpp src/views/playfield/PlayfieldView.hpp src/views/playfield/ScoreDisplay.cpp src/views/playfield/ScoreDisplay.hpp src/views/playfield/Side.hpp src/views/playfield/Paddle.cpp src/views/playfield/Paddle.hpp src/views/startScreen/StartScreenView.cpp src/views/startScreen/StartScreenView.hpp
        SFMLMath/SFMLMath.hpp src/views/menuView/MenuView.cpp src/views/menuView/MenuView.hpp src/players/ArrowKeyPlayer.cpp src/players/ArrowKeyPlayer.hpp src/players/WSPlayer.cpp src/players/WSPlayer.hpp)
target_link_libraries(Pong PRIVATE sfml-graphics SFMLApp)
