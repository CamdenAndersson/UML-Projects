// Copyright 2024 Camden Andersson
// pixels.cpp:
// using SFML to load a file, manipulate its pixels, write it to disk



// g++ -o pixels pixels.cpp -lsfml-graphics -lsfml-window
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "PhotoMagic.hpp"
int main(int argc, char* argv[]) {
    sf::Image image;
    if (!image.loadFromFile(argv[1]))
        return -1;

    std::cout << "loaded image" << std::endl;

    sf::Vector2u size = image.getSize();
    sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "awooga");
    sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "awooga 2");

    std::cout << "windows made" << std::endl;

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    // transform image
    std::string seedSTR = argv[3];
    PhotoMagic::FibLFSR seed(seedSTR);
    PhotoMagic::FibLFSR* ptr = &seed;
    PhotoMagic::transform(image, ptr);
    std::cout << "seed loaded into transform" << std::endl;

    sf::Texture texture2;
    texture2.loadFromImage(image);

    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    std::cout << "texture loaded and sprites created, drawing window:" << std::endl;

    while (window1.isOpen() && window2.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window1.close();
        }
            while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window2.close();
        }

        window1.clear();
        window1.draw(sprite);
        window1.display();

        window2.clear();
        window2.draw(sprite2);
        window2.display();
    }


    // fredm: saving a PNG segfaults for me, though it does properly
    // write the file
    if (!image.saveToFile(argv[2]))
        return -1;

    return 0;
}
