// Copyright 2023 Camden Andersson
#include <string>
#include "PTree.hpp"

int main(int argc, char* argv[]) {
    int sideLength = std::atoi(argv[1]);
    int recursionAmt = std::atoi(argv[2]);

    sf::RenderWindow window(sf::VideoMode((sideLength * 6),
    (sideLength * 4)), "SFML Pythagoras Tree");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        PTree pTree;

        window.clear();
        pTree.pTree(window, (sideLength * 2.5), (sideLength * 3), sideLength, 0, recursionAmt);

        window.display();
    }



    return 0;
}
