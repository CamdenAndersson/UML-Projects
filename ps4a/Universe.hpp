// Copyright 2024 Camden Andersson
#pragma once

#include "CelestialBody.hpp"
namespace NB {
class Universe : public sf::Drawable {
 private:
    std::vector<std::shared_ptr<CelestialBody>> bodies;
    int numParticles;
    double _radius;
    sf::Texture backgroundTexture;
    int screenWidth;
    int screenHeight;
 protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;  // override;
 public:
    Universe();
    explicit Universe(const std::string filename);
    void loadTextures();
    void setScreenDimensions(int width, int height);
    void setMaxDimension();
    void step(double deltaT);
    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
    CelestialBody& operator[](size_t index);
    double radius() const;
    int numPlanets() const;
};
}  // namespace NB
