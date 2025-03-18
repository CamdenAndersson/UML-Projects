// Copyright 2024 Camden Andersson
#include "FibLFSR.hpp"



/*
Take the seed as an input of 16 bits
Xor bits 15, 13, 12 and 10 , output to bit 1
*/

namespace PhotoMagic {
FibLFSR::FibLFSR(std::string seed) {
    storedLFSR = std::stoi(seed, 0, 2);

    // for testing
    // std::cout << storedLFSR;
}

int FibLFSR::step() {
    int newBit = ((((((storedLFSR >> 15) & 1) ^ ((storedLFSR >> 13) & 1)))
    ^ ((storedLFSR >> 12) & 1)) ^ ((storedLFSR >> 10) & 1));
    storedLFSR = storedLFSR << 1;
    storedLFSR = storedLFSR | newBit;

    return newBit;
}

int FibLFSR::generate(int k) {
    int result = 0;

    for (int i = 0; i < k; ++i) {
        result = (result << 1) | step();
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const PhotoMagic::FibLFSR& lfsr) {
    for (int i = 15; i >= 0; --i) {
        out << (((lfsr.storedLFSR) >> i) & 1);
    }

    return out;
}
}  // namespace PhotoMagic
