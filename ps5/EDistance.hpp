// Copyright Camden Andersson 2024
#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EDistance {
 public:
    EDistance(const std::string& x, const std::string& y);
    ~EDistance();
    int optDistance();
    std::string alignment();
    std::string printDynamicArray();
    static int penalty(char a, char b);
    static int min3(int a, int b, int c);
    static int min3std(int a, int b, int c);
    static int min3opt(int a, int b, int c);
 private:
    std::string x;  // the first DNA string
    std::string y;  // the second DNA string
    std::vector<std::vector<int>> opt;  // the n x m array to hold alignments
};
#endif /* EDISTANCE_HPP */
