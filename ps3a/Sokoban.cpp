// Copyright 2024 Camden Andersson
#include "Sokoban.hpp"

namespace SB {
//  make it take in an ifstream and output an ifstream
std::ifstream& operator>>(std::ifstream& is, SB::Sokoban& grid) {
    // is.open(grid.levelName);
    if (!is.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return is;
    }

    // Read the width and height
    is >> grid.internalWidth >> grid.internalHeight;

    // Resize the grid
    grid.gridData.resize(grid.internalWidth, std::vector<char>(grid.internalHeight));

    // Read the grid data
    for (int i = 0; i < grid.internalWidth; ++i) {
        for (int j = 0; j < grid.internalHeight; ++j) {
            is >> grid.gridData[i][j];

            if (grid.gridData[i][j] == '@') {
                grid.playerX = j;
                grid.playerY = i;
            }
        }
    }

    is.close();
    return is;
}

Sokoban::Sokoban(void) {
}

void Sokoban::setLevelName(std::string _levelName) {
    levelName = _levelName;
}
// returns height due to how columns are read
int Sokoban::width(void) const {
    return internalHeight;
}
// returns width due to how columns are read
int Sokoban::height(void) const {
    return internalWidth;
}

sf::Vector2i Sokoban::playerLoc() const {
    // returns player position (x,y)
    return sf::Vector2i(playerX, playerY);
}

void Sokoban::movePlayer(enum Direction) {
}

bool Sokoban::isWon() const{
    return 0;
}

std::string Sokoban::getLevelName(void) {
    return levelName;
}

void Sokoban::setPlayerX(int x) {
    playerX = x;
}
void Sokoban::setPlayerY(int y) {
    playerY = y;
}

void Sokoban::fillTextures() {
    //  make sure all textures are valid
    if (!texturePlayer05.loadFromFile("player_05.png")) {
        std::exit(1);
    }
    if (!texturePlayer08.loadFromFile("player_08.png")) {
        std::exit(1);
    }
    if (!texturePlayer17.loadFromFile("player_17.png")) {
        std::exit(1);
    }
    if (!texturePlayer20.loadFromFile("player_20.png")) {
        std::exit(1);
    }
    if (!textureBlock06.loadFromFile("block_06.png")) {
        std::exit(1);
    }
    if (!textureCrate03.loadFromFile("crate_03.png")) {
        std::exit(1);
    }
    if (!textureEnviroment03.loadFromFile("environment_03.png")) {
        std::exit(1);
    }
    if (!textureGround01.loadFromFile("ground_01.png")) {
        std::exit(1);
    }
    if (!textureGround04.loadFromFile("ground_04.png")) {
        std::exit(1);
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // This is example code. Just draws a rectangle.
    // sf::RectangleShape rectangle(sf::Vector2f(20, 20));
    // rectangle.setFillColor(sf::Color::Green);
    // rectangle.setPosition(sf::Vector2f(20, 20));
    // target.draw(rectangle, states);

    // More sample code, this just draws a sprite in the center of the screen
    sf::Sprite tPlayer;
    sf::Sprite tCrate;
    // tPlayer.setTexture(texturePlayer05);

    // Set the origin of the sprite to its center
    // tPlayer.setOrigin(tPlayer.getLocalBounds().width / 2, tPlayer.getLocalBounds().height / 2);

    // Set the position of the sprite to the middle of the screen
    // tPlayer.setPosition(target.getSize().x / 2, target.getSize().y / 2);
    // target.draw(tPlayer, states);

    // Ultimately, draw the full board here
    // TO DO:
    // iterate through the 2d data array, drawing what you see, one object at a time
    // hopefully its light work
    char cCurr;
    for (int i = 0; i < internalWidth; ++i) {
        for (int j = 0; j < internalHeight; ++j) {
            cCurr = gridData[i][j];
            sf::Sprite sprite;
            switch (cCurr) {
            case '#':
                sprite.setTexture(textureBlock06);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);
                break;
            case '.':
                sprite.setTexture(textureGround01);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);
                break;
            case '@':
                sprite.setTexture(textureGround01);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);

                tPlayer.setTexture(texturePlayer05);
                tPlayer.setPosition(j * 64, i*64);
                target.draw(tPlayer, states);
                break;
            case 'A':
                sprite.setTexture(textureGround01);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);

                tCrate.setTexture(textureCrate03);
                tCrate.setPosition(j * 64, i*64);
                target.draw(tCrate, states);
                break;
            case 'a':
                sprite.setTexture(textureGround04);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);
                break;
            }
        }
    }
}
}  // namespace SB
