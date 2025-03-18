// Copyright Camden Andersson 2024
#include "EDistance.hpp"
int main(int argc, char* argv[]) {
    // Load in the text file with the 2 strings
    std::string x, y;
    std::cin >> x >> y;
    // std::ifstream inputFile(fileName);
    // if (inputFile.is_open()) {
    //    inputFile >> x >> y;
    //    inputFile.close();
    // } else {
    //    std::cerr << "Unable to open file";
    //    return 1;
    // }

    // Start the clock, run the alignment code
    // sf::Clock clock;
    // EDistance ed(x, y);
    // std::cout << "opt[][] is initialized and seeded.\n";
    // std::cout << ed.printDynamicArray();

    // Start the clock, run the alignment code
    sf::Clock clock;
    EDistance ed(x, y);
    // std::cout << "opt[][] is initialized and seeded.\n";
    // std::cout << "x is " << x.length() << " chars\n";
    // std::cout << "y is " << y.length() << " chars\n";
    // std::cout << "\n";
    // At this point, the 2d array should be initialized

    // Compute the Edit Distance
    int distance = ed.optDistance();
    // std::cout << "opt[0][0] is the edit distance.\n";
    // std::cout << ed.printDynamicArray();
    std::string alignment = ed.alignment();
    sf::Time elapsed = clock.getElapsedTime();

    // Display the results
    std::cout << "Edit distance = " << distance << std::endl;
    std::cout << alignment;  // << std::endl;
    std::cout << "Execution time is " << elapsed.asSeconds() << " seconds" << std::endl;
    return 0;
}
