// Copyright 2023 Camden Andersson
#include "PTree.hpp"

const double ANGLE = M_PI / 4.0;  // 45 degrees in radians

void PTree::pTree(sf::RenderTarget& window, int x, int y,
int L, double angle, int depth) {
    if (depth <= 0) {
        return;
    }

    sf::RectangleShape rect(sf::Vector2f(L, L));
    // rect.setFillColor(sf::Color(0,0,0,255));
    rect.setPosition(x, y);
    // rect.setSize(sf::Vector2f(L,L));
    rect.setRotation(angle * (180 / M_PI));
    //  rect.setOutlineColor(sf::Color::White);
    //  rect.setOutlineThickness(1);
    rect.setFillColor(sf::Color
    { 0xff9ff * (static_cast<sf::Uint32>(depth) * 2)});
    window.draw(rect);

    //  Look at the 4 points of the previous rect you drew
    sf::Vector2f vTL = rect.getTransform().transformPoint(rect.getPoint(0));
    sf::Vector2f vTR = rect.getTransform().transformPoint(rect.getPoint(1));
    //  sf::Vector2f vBR = rect.getTransform().transformPoint(rect.getPoint(2));
    //  sf::Vector2f vBL = rect.getTransform().transformPoint(rect.getPoint(3));
    //  int newRightX = vTL.x - (L / sqrt(2)) * cos(angle + (M_PI / 4));
    //  int newRightY = vTL.y - (L / sqrt(2)) * sin(angle + (M_PI / 4));

    //  pTree(window, newRightX, newRightY, L / sqrt(2), (angle - (M_PI / 4)), depth - 1);

    int newLeftX = vTL.x - (L / sqrt(2)) * cos(angle + (M_PI / 4));
    int newLeftY = vTL.y - (L / sqrt(2)) * sin(angle + (M_PI / 4));

    int newRightX = vTR.x + (L) * sin(angle);
    int newRightY = vTR.y - (L) * cos(angle);

    pTree(window, newLeftX, newLeftY, L / sqrt(2),
    (angle - (M_PI / 4)), depth - 1);

    pTree(window, newRightX, newRightY, L / sqrt(2),
    (angle + (M_PI / 4)), depth - 1);
}
