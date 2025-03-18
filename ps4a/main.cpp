// Copyright 2024 Camden Andersson

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "CelestialBody.hpp"
#include "Universe.hpp"


int main(int argc, char* argv[]) {
    // Load the file
    // std::ifstream file("kevin.txt");
    // if (!file.is_open()) {
    //    std::cerr << "Failed to open file" << std::endl;
    //    return 1;
    // }

    // Load an instance of the Universe class
    NB::Universe universe;
    std::cin >> universe;
    //  std::cout << universe;
    sf::Font textCounterFont;
    if (!textCounterFont.loadFromFile("arial.ttf")) {
        std::cout << "No arrial.ttf file found." << std::endl;
    }
    sf::Text textForCounter;
    textForCounter.setFont(textCounterFont);
    textForCounter.setCharacterSize(16);
    sf::Clock clock;



    // Set the screen size and load the Universe->CelestialBody textures
    int screenWidth = 800;
    int screenHeight = 800;
    universe.setScreenDimensions(screenWidth, screenHeight);
    universe.setMaxDimension();
    universe.loadTextures();

    // Setup the times
    double deltaT = std::stod(argv[2]);
    double T = std::stod(argv[1]);
    // double deltaT = 25000.00;
    // double T = 157788000.0;

    // NOTE: 1 day = 86400 sec
    //  1 year = 3153600 sec
    // double deltaT = 86400;
    // double T = 3153600

    // Initialize the current time
    double dCurrT = 0.0 + deltaT;
    std::string seconds = "Seconds: ";

    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("backgroundmusic.wav");
    sound.setBuffer(buffer);
    sound.play();
    sound.setLoop(true);

    // Create the window itself
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Universe");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << universe;
                sound.stop();
                window.close();
            }
        }
        if (dCurrT < T) {
            // Do the physics to compute the forces and positions
            universe.step(deltaT);
            dCurrT = dCurrT + deltaT;
            // Display the results
            // temporary disabling for submission  std::cout << "time: " << dCurrT << std::endl;
        }
        textForCounter.setString(seconds + std::to_string(dCurrT));
        window.clear();
        window.draw(universe);
        window.draw(textForCounter);
        window.display();
    }

    return 0;
}
