// Copyright 2023 Camden Andersson
#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP

#include "FibLFSR.hpp"

using PhotoMagic::FibLFSR;

namespace PhotoMagic {
// Transforms image using FibLFSR
void transform(sf::Image&, FibLFSR*);
// Display an encrypted copy of the picture, using the LFSR to do the encryption
}
#endif
