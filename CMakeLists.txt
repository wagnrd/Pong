cmake_minimum_required(VERSION 3.12)

project(Pong)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Pong
        src/main.cpp
        src/Game.cpp
        src/Game.hpp
        src/views/playfield/Ball.cpp
        src/views/playfield/Ball.hpp
        src/views/playfield/PlayfieldView.cpp
        src/views/playfield/PlayfieldView.hpp
        src/views/playfield/ScoreDisplay.cpp
        src/views/playfield/ScoreDisplay.hpp
        src/views/playfield/Side.hpp
        src/views/playfield/Paddle.cpp
        src/views/playfield/Paddle.hpp
        src/views/startScreen/StartScreenView.cpp
        src/views/startScreen/StartScreenView.hpp
        src/views/menu/MenuView.cpp
        src/views/menu/MenuView.hpp
        src/views/settings/SettingsView.cpp
        src/views/settings/SettingsView.hpp
        src/players/ArrowKeyPlayer.cpp
        src/players/ArrowKeyPlayer.hpp
        src/players/WSPlayer.cpp
        src/players/WSPlayer.hpp
        SFMLMath/SFMLMath.hpp      # add SFMLMath
        src/players/NNAI.cpp
        src/players/NNAI.hpp
        src/views/settings/SettingsView.cpp
        src/views/settings/SettingsView.hpp
        src/players/NNAIPlayer.cpp
        src/players/NNAIPlayer.hpp src/players/Skill.hpp)

# add SFML
find_package(SFML 2.5 COMPONENTS graphics)

# add OpenNN
add_subdirectory(OpenNN)

# add SFMLApp
add_library(SFMLApp STATIC SFMLApp/Application.cpp SFMLApp/Application.hpp SFMLApp/Node.cpp SFMLApp/Node.hpp)
target_include_directories(SFMLApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SFMLApp)

target_link_libraries(Pong PRIVATE sfml-graphics SFMLApp opennn)


