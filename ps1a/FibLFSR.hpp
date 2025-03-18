// Copyright 2023 Camden Andersson
#include <iostream>
#include <string>
#include <sstream>

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
 private:
        // Any fields that you need
        // stored lfsr as an int
        unsigned int storedLFSR = 0;
};
}  // namespace PhotoMagic
