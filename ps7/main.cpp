// Copyright Camden Andersson 2024

#include <iostream>
#include <string>
#include <regex>
#include "Kronos.hpp"

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    kronos k(filename);
    k.makeBootupLog();
    // k.printBootupLog();
    k.makeSummaryLog();
    k.printSummaryLog();

    return 0;
}
