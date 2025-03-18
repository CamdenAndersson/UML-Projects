// Copyright 2024 Camden Andersson
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
namespace SB {
enum Direction {Up, Down, Left, Right};
class Sokoban : public sf::Drawable {
 public:
     Sokoban();
     //  void fillTextures();
     void setInitialPlayerLoc();
     int width(void) const;
     int height(void) const;
     sf::Vector2i playerLoc() const;
     void movePlayer(enum Direction _direction);
     bool isWon() const;
     void setPlayerX(int x);
     void setPlayerY(int y);
     void setLevelName(std::string _levelName);
     std::string getLevelName(void);
     char getGridData(int x, int y);
     char getGridOriginalData(int x, int y);
     void setGridData(int x, int y, char c);
     void resetLevel();
     void fillOriginalGrid();
     bool isBoxOrStoredBox(int x, int y);
     bool isWall(int x, int y);
     bool isOrigSpaceStorage(int x, int y);
     void fillPreviousGrid();
     void resetLevelBack();
     friend std::ifstream& operator>>(std::ifstream& is, SB::Sokoban& grid);

 protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
     std::vector<std::vector<char>> gridData;  // The 2d grid
     std::vector<std::vector<char>> gridDataOriginal;  // unmodified grid to allow for a reset
     std::vector<std::vector<char>> gridDataPrevious;  // The 2d grid before we move
     std::string levelName;
     int internalWidth;
     int internalHeight;
     Direction lastDirection;
     int playerX;
     int playerY;
     sf::Texture texturePlayer05;
     sf::Texture texturePlayer08;
     sf::Texture texturePlayer17;
     sf::Texture texturePlayer20;
     sf::Texture textureBlock06;
     sf::Texture textureCrate03;
     sf::Texture textureEnviroment03;
     sf::Texture textureGround01;
     sf::Texture textureGround04;
};
}  // namespace SB
