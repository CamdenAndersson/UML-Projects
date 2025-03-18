// Copyright 2024 Camden Andersson
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
namespace SB {
enum Direction {Up, Down, Left, Right};
class Sokoban : public sf::Drawable {
 public:
      Sokoban();
      void fillTextures();
      int width(void) const;
      int height(void) const;
      sf::Vector2i playerLoc() const;
      void movePlayer(enum Direction);
      bool isWon() const;
      void setPlayerX(int x);
      void setPlayerY(int y);
      void setLevelName(std::string _levelName);
      std::string getLevelName(void);
      char getGridData(int x, int y);
      friend std::ifstream& operator>>(std::ifstream& is, SB::Sokoban& grid);

 protected:
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
      // char levelMatrix[][];
      // std::vector<char> levelData;
      std::vector<std::vector<char>> gridData;  // The 2d grid
      std::string levelName;
      int internalWidth;
      int internalHeight;

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
