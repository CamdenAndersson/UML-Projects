// Copyright 2023 Camden Andersson

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class PTree: public sf::RectangleShape {
 public:
    void pTree(sf::RenderTarget& window, int x, int y,
    int L, double angle, int depth);
};
