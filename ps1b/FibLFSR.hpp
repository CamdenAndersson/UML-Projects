// Copyright 2024 Camden Andersson
#ifndef FibLFSR_HPP
#define FibLFSR_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace PhotoMagic {
class FibLFSR {
 public:
        // Constructor to create LFSR with the given initial seed
        explicit FibLFSR(std::string seed);
        // Simulate one step and return the new bit as 0 or 1
        int step();
        // Simulate k steps and return a k-bit integer
        int generate(int k);
        // friend output operator
        friend std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);
        // Transforms image using FibLFSR
        void transform(sf::Image&, FibLFSR*);
        // Display an encrypted copy of the picture, using the LFSR to do the encryption
 private:
        // Any fields that you need
        // stored lfsr as an int
        unsigned int storedLFSR = 0;
};
}  // namespace PhotoMagic
#endif
