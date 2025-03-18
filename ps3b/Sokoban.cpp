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

    //  Load in all the textures and set initial player loc
    //  grid.fillTextures();  // now you can use them in draw()
    grid.fillOriginalGrid();
    //  grid.setInitialPlayerLoc();
    return is;
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

bool Sokoban::isWall(int x, int y) {
    if ((getGridData(x, y)) == '#')
        return true;
    else
        return false;
}


bool Sokoban::isBoxOrStoredBox(int x, int y) {
    if ((getGridData(x, y) == 'A') || (getGridData(x, y) == '1'))
        return true;
    else
        return false;
}

bool Sokoban::isOrigSpaceStorage(int x, int y)  {
        if (getGridOriginalData(x, y) == 'a')
            return true;
        else
            return false;
}

void Sokoban::fillPreviousGrid() {
        // Initialize and copy gridData to another vector
        gridDataPrevious.resize(gridData.size());
        for (size_t i = 0; i < gridData.size(); ++i) {
            gridDataPrevious[i].resize(gridData[i].size());
            for (size_t j = 0; j < gridData[i].size(); ++j) {
                gridDataPrevious[i][j] = gridData[i][j];
            }
        }
}


void Sokoban::resetLevelBack() {
        // Put the original grid data back to one previous step
        for (int i = 0; i < internalWidth; ++i) {
            for (int j = 0; j < internalHeight; ++j) {
                gridData[i][j] = gridDataPrevious[i][j];

                if (gridData[i][j] == '@') {
                    playerX = j;
                    playerY = i;
                }
            }
        }
    }


void Sokoban::movePlayer(enum Direction _direction) {
        std::cout << "Player Moved: " << std::endl;

        // This is where the player is currently at
        sf::Vector2i currLoc = playerLoc();

        // See if the move is possible
        bool bMoveOk = true;
        if ((_direction == Right) && (currLoc.x == internalHeight - 1))
            bMoveOk = false;
        else if ((_direction == Left) && (currLoc.x == 0))
            bMoveOk = false;
        else if ((_direction == Up) && (currLoc.y == 0))
            bMoveOk = false;
        else if ((_direction == Down) && (currLoc.y == internalWidth-1))
            bMoveOk = false;
        if (!bMoveOk) {
            std::cout << "Player move not possible." << std::endl;
            return;
        }

        // TO DO: make sure a move is possible ie a player can't go off the board
        int nextX = 0;
        int nextY = 0;
        int nextNextX = 0;
        int nextNextY = 0;

        // Before you move, store the current state so you cand undo one step with the Y key.
        fillPreviousGrid();
        // Make a move
        switch (_direction) {
        case Up:
        case Down:

            if (_direction == Up) {
                nextY = currLoc.y - 1;
                nextNextY = currLoc.y - 2;
            } else {
                nextY = currLoc.y + 1;
                nextNextY = currLoc.y + 2;
            }
            // If the nextY is not a wall or nothing, then move
            if (!isWall(currLoc.x, nextY)) {
                // If the next spot up is a box or stored box
                if (isBoxOrStoredBox(currLoc.x, nextY)) {
                    // See if the next next spot is wall or nothing
                    if (!isWall(currLoc.x, nextNextY)) {
                        //  adding check for if a box is after the box you are pushing
                        if (!isBoxOrStoredBox(currLoc.x, nextNextY)) {
                            // Move the player
                            setPlayerY(nextY);
                            setGridData(currLoc.x, nextY, '@');

                            // See if the box has moved into a storage spot
                            if (getGridData(currLoc.x, nextNextY) == 'a') {
                                // Move the box
                                setGridData(currLoc.x, nextNextY, '1');

                                // Replace the players old location with a '.' or 'a'
                                if (isOrigSpaceStorage(currLoc.x, currLoc.y))
                                setGridData(currLoc.x, currLoc.y, 'a');
                                else
                                    setGridData(currLoc.x, currLoc.y, '.');
                        } else {
                            if (!isWall(currLoc.x, nextNextY)) {
                                setGridData(currLoc.x, nextNextY, 'A');
                                setGridData(currLoc.x, currLoc.y, '.');
                            }
                        }
                        }
                    }
                } else {  // It's not a box, just move
                    // Set the new y location
                    setPlayerY(nextY);
                    setGridData(currLoc.x, nextY, '@');

                    // Replace the players old location with a .
                    if (isOrigSpaceStorage(currLoc.x, currLoc.y))
                        setGridData(currLoc.x, currLoc.y, 'a');
                    else
                        setGridData(currLoc.x, currLoc.y, '.');
                }
            }
            break;

        case Left:
        case Right:

            if (_direction == Left) {
                nextX = currLoc.x - 1;
                nextNextX = currLoc.x - 2;;
            } else {
                nextX = currLoc.x + 1;
                nextNextX = currLoc.x + 2;
            }
            if (!isWall(nextX, currLoc.y)) {
                // If the next spot left is a box or stored box
                if (isBoxOrStoredBox(nextX, currLoc.y)) {
                    // See if the next next spot is wall
                    if (!isWall(nextNextX, currLoc.y)) {
                        if (!isBoxOrStoredBox(nextNextX, currLoc.y)) {
                            // Move the player
                            setPlayerX(nextX);
                            setGridData(nextX, currLoc.y, '@');

                            // See if the box has moved into a storage spot
                            if (getGridData(nextNextX, currLoc.y) == 'a') {
                                // Move the box
                                setGridData(nextNextX, currLoc.y, '1');

                                // Replace the players old location with a '.' or 'a'
                                if (isOrigSpaceStorage(currLoc.x, currLoc.y))
                                    setGridData(currLoc.x, currLoc.y, 'a');
                                else
                                    setGridData(currLoc.x, currLoc.y, '.');
                        } else {
                            if (!isWall(nextNextX, currLoc.y)) {
                                setGridData(nextNextX, currLoc.y, 'A');

                                // Replace the players old location with a '.' or 'a'
                                if (isOrigSpaceStorage(currLoc.x, currLoc.y))
                                    setGridData(currLoc.x, currLoc.y, 'a');
                                else
                                    setGridData(currLoc.x, currLoc.y, '.');
                            }
                        }
                    }
                    }
                } else {  // It's not a box, just move
                    // Set the new y location
                    setPlayerX(nextX);
                    setGridData(nextX, currLoc.y, '@');

                    // Replace the players old location with a '.' or 'a'
                    if (isOrigSpaceStorage(currLoc.x, currLoc.y))
                        setGridData(currLoc.x, currLoc.y, 'a');
                    else
                        setGridData(currLoc.x, currLoc.y, '.');
                }
        }
            break;


        default:
            break;
        }
        lastDirection = _direction;
        std::cout << "Player is at: " << playerX << ", " << playerY << std::endl;
}

// uses algorithm and lambda functions
bool Sokoban::isWon() const {
        // When there are no more unstored boxes 'A', you won
        bool bIsWon = true;
        for (int i = 0; i < internalWidth; ++i) {
            for (int j = 0; j < internalHeight; ++j) {
                if (gridData[i][j] == 'a')
                    bIsWon = false;
            }
        }
        if (bIsWon) {
            return true;
        } else {
        auto it = std::find_if(gridData.begin(), gridData.end(), [](const auto& row) {
            return std::find(row.begin(), row.end(), 'A') != row.end();
            });
        return it == gridData.end();
    }
}


std::string Sokoban::getLevelName(void) {
    return levelName;
}

void Sokoban::setPlayerX(int x) {
    if (x >= 0)
        playerX = x;
}
    void Sokoban::setPlayerY(int y) {
    if (y >= 0)
        playerY = y;
}

void Sokoban::resetLevel() {
        // Put the original grid data back into the grid data
        // that will be drawn
        for (int i = 0; i < internalWidth; ++i) {
            for (int j = 0; j < internalHeight; ++j) {
                gridData[i][j] = gridDataOriginal[i][j];

                if (gridData[i][j] == '@') {
                    playerX = j;
                    playerY = i;
                }
            }
        }
}

void Sokoban::fillOriginalGrid() {
        // Initialize and copy gridData to another vector
        gridDataOriginal.resize(gridData.size());
        for (size_t i = 0; i < gridData.size(); ++i) {
            gridDataOriginal[i].resize(gridData[i].size());
            for (size_t j = 0; j < gridData[i].size(); ++j) {
                gridDataOriginal[i][j] = gridData[i][j];
            }
        }
}

Sokoban::Sokoban() {
    //  make sure all textures are valid
    texturePlayer05.loadFromFile("player_05.png");
    texturePlayer08.loadFromFile("player_08.png");
    texturePlayer17.loadFromFile("player_17.png");
    texturePlayer20.loadFromFile("player_20.png");
    textureBlock06.loadFromFile("block_06.png");
    textureCrate03.loadFromFile("crate_03.png");
    textureEnviroment03.loadFromFile("environment_03.png");
    textureGround01.loadFromFile("ground_01.png");
    textureGround04.loadFromFile("ground_04.png");
}

//  moved to constructor instead
//  void Sokoban::fillTextures() {
//  }

char Sokoban::getGridData(int x, int y) {
    return gridData[y][x];
}

char Sokoban::getGridOriginalData(int x, int y) {
    return gridDataOriginal[y][x];
}

void Sokoban::setGridData(int x, int y, char c) {
    gridData[y][x] = c;
}

void Sokoban::setInitialPlayerLoc() {
    char cCurr;
    for (int i = 0; i < internalWidth; ++i) {
        for (int j = 0; j < internalHeight; ++j) {
            cCurr = gridData[i][j];
            if (cCurr == '@') {
                    playerX = j;
                    playerY = i;
            }
        }
    }
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite tPlayer;
    sf::Sprite tCrate;
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
                sprite.setPosition(j * 64, i * 64);
                target.draw(sprite, states);
                switch (lastDirection) {
                case Up:
                    tPlayer.setTexture(texturePlayer08);
                    break;
                case Right:
                    tPlayer.setTexture(texturePlayer17);
                    break;
                case Left:
                    tPlayer.setTexture(texturePlayer20);
                    break;
                default:  // Down
                    tPlayer.setTexture(texturePlayer05);
                }
                tPlayer.setPosition(j * 64, i * 64);
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
            case '1':
                sprite.setTexture(textureGround01);
                sprite.setPosition(j * 64, i*64);
                target.draw(sprite, states);

                tCrate.setTexture(textureCrate03);
                tCrate.setPosition(j * 64, i*64);
                target.draw(tCrate, states);
            }
        }
    }
}
}  // namespace SB
