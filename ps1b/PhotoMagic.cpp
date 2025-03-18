// Copyright 2023 Camden Andersson
#include "PhotoMagic.hpp"

namespace PhotoMagic {
// Transforms image using FibLFSR
// take the iamge as an input, along with the fib lsfr.
// go pixel by pixel stepping once to transform each pixel

void transform(sf::Image& image, FibLFSR* lfsr) {
  int vert, hori;
  sf::Color pixel;

  sf::Vector2u imageSize = image.getSize();

  vert = imageSize.x;
  hori = imageSize.y;
    // look at pdf for explanation on what to do
  for (int i = 0; i < hori; i++) {
      for (int j = 0; j < vert; j++) {
          pixel = image.getPixel(j, i);
          pixel.r = pixel.r ^ lfsr->generate(8);
          pixel.g = pixel.g ^ lfsr->generate(8);
          pixel.b = pixel.b ^ lfsr->generate(8);
          image.setPixel(j, i, pixel);
      }
  }
}
// Display an encrypted copy of the picture, using the LFSR to do the encryption
}  //  namespace PhotoMagic
