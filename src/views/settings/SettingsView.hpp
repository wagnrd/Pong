//
// Created by Denis Wagner on 2/18/19.
//

#ifndef PONG_SETTINGSVIEW_HPP
#define PONG_SETTINGSVIEW_HPP

#include <Node.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../playfield/PlayfieldView.hpp"

class SettingsView : public Node {
    std::shared_ptr<PlayfieldView> playfieldView;

    sf::Font fontTitle;
    sf::Font fontInstruction;
    sf::Text title;
    sf::Text instructions;

    const std::vector<std::string> enumeratingInstructions{ "Player vs. A.I. (Live training)", "Player vs. A.I. (Easy)",
                                                            "Player vs. A.I. (Medium)", "Player vs. A.I. (Hard)",
                                                            "A.I. vs. A.I. (Live training)", "Player vs. Player" };
    int                            currentInstruction        = 1;
    const std::string              instructionStartIndicator = ">> ";
    const std::string              instructionEndIndicator   = " <<";
    bool                           fullscreen                = false;

public:
    explicit SettingsView( std::shared_ptr<PlayfieldView> playfieldView );
    virtual void init() override;
    virtual void eventHandler( const sf::Event& event ) override;
    virtual void draw( sf::RenderWindow& window ) override;

private:
    std::string getInstructionsString();
};

#endif //PONG_SETTINGSVIEW_HPP
