// Copyright 2024 Camden Andersson

#include <iostream>
#include "Sokoban.hpp"



int main(int argc, char* argv[]) {
    // Create the sokoban object
    SB::Sokoban sokoban;
    sokoban.setLevelName(argv[1]);
    std::ifstream file;
    file.open(sokoban.getLevelName());
    file >> sokoban;

    // Load in all the textures
    sokoban.fillTextures();  // now you can use them in draw()
    // Play the game (draw the level for now)
    sf::RenderWindow window(sf::VideoMode(64 * sokoban.height(),
    64 * sokoban.width()), "Sokoban Game");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(sokoban);

        window.display();
    }
}
