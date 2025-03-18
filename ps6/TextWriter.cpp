// Copyright Camden Andersson 2024
#include <string>
#include <iostream>
#include <fstream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    int k = std::stoi(argv[1]);  // The size k-gram
    int L = std::stoi(argv[2]);  // Number of char's to generate
    std::string filename;  // Text filename to open
    std::cin >> filename;
    TextWriter tw;
    tw.TextWriter_main(k, L, filename);
    return 0;
}
