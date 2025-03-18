// Copyright 2024 Camden Andersson

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // Create the sokoban object
    SB::Sokoban sokoban;
    sokoban.setLevelName(argv[1]);
    std::ifstream file;
    file.open(argv[1]);
    file >> sokoban;

    file.close();
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("sound.wav");
    sound.setBuffer(buffer);

    // Play the game (draw the level for now)
    sf::RenderWindow window(sf::VideoMode(64 * sokoban.width(),
        64 * sokoban.height()), "Sokoban Game");
    bool soundPlayed = false;  // Variable to track if the sound has been played
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            SB::Direction playerDirection;
            if (event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key key = event.key.code;
                std::cout << "Key released: " << event.key.code << std::endl;
                if (sokoban.isWon()) {
                    if (key == sf::Keyboard::R)
                        sokoban.resetLevel();
                } else {
                    switch (key) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        playerDirection = SB::Up;
                        sokoban.movePlayer(playerDirection);
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                        playerDirection = SB::Left;
                        sokoban.movePlayer(playerDirection);
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        playerDirection = SB::Down;
                        sokoban.movePlayer(playerDirection);
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                        playerDirection = SB::Right;
                        sokoban.movePlayer(playerDirection);
                        break;
                    case sf::Keyboard::R:
                        sokoban.resetLevel();
                        break;
                    case sf::Keyboard::U:
                        sokoban.resetLevelBack();
                    default:
                        break;
                    }
                }
            }
            window.draw(sokoban);

            if (sokoban.isWon()) {
                if (!soundPlayed) {
                    sound.play();
                    soundPlayed = true;  // Mark the sound as played
                }
                // Set up the font
                sf::Font font;
                if (!font.loadFromFile("arial.ttf")) {
                    return 1;  // Exit if the font file is not found
                }
                // Create a text object
                sf::Text text("You Won!", font, 50);
                text.setFillColor(sf::Color::Green);
                // Center the text
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
                text.setPosition(sf::Vector2f(window.getSize().x / 2.0f,
                window.getSize().y / 2.0f));

                // Draw the text
                window.draw(text);
            }
            // display window
            window.display();
        }
    }
}
