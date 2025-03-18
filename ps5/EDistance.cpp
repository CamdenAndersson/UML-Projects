// Copyright Camden Andersson 2024
#include "EDistance.hpp"
#include <sstream>

EDistance::EDistance(const std::string& x, const std::string& y) : x(x), y(y) {
    opt.resize(x.size() + 1, std::vector<int>(y.size() + 1, 0));

    // Resize the 2d array, and then seed the boundaries with a penalty of 2
    // The 2 increases as you move left and up
    for (size_t i = 0; i <= x.size(); ++i) {
        opt[i][y.size()] = 2 * (x.size() - i);
    }

    for (size_t j = 0; j <= y.size(); ++j) {
        opt[x.size()][j] = 2 * (y.size() - j);
    }
}

EDistance::~EDistance() {
    // Deallocate memory if allocated using new
    // not using new, so we can leave this as-is
}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    // return min3std(a, b, c);
    return min3opt(a, b, c);
}

int EDistance::min3std(int a, int b, int c) {
    // Comparison of three items a, b, c
    return std::min(std::min(a, b), c);
}

int EDistance::min3opt(int a, int b, int c) {
    // An alternative method
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int EDistance::optDistance() {
    // We start at the bottom of the 2d matrix and work our way up
    // Right to left, then bottom to top
    for (int i = x.size() - 1; i >= 0; --i) {
        for (int j = y.size() - 1; j >= 0; --j) {
            opt[i][j] = min3(opt[i + 1][j + 1] + penalty(x[i], y[j]),
                opt[i + 1][j] + 2,
                opt[i][j + 1] + 2);
        }
    }
    // Our Edit Distance is in [0][0]
    return opt[0][0];
}

std::string EDistance::alignment() {
    std::string align;
    size_t i = 0;
    size_t j = 0;
    // Traverse the path and print out the string
    while (i < x.size() || j < y.size()) {
        if (i < x.size() && j < y.size() && opt[i][j] == opt[i + 1][j + 1] + penalty(x[i], y[j])) {
            align += x[i];
            align += ' ';
            align += y[j];
            align += ' ';
            align += std::to_string(penalty(x[i], y[j]));
            align += '\n';
            ++i;
            ++j;
        } else if (i < x.size() && opt[i][j] == opt[i + 1][j] + 2) {
            align += x[i];
            align += ' ';
            align += '-';
            align += ' ';
            align += "2\n";
            ++i;
        } else {
            align += '-';
            align += ' ';
            align += y[j];
            align += ' ';
            align += "2\n";
            ++j;
        }
    }

    return align;
}

// This will print the full array out
std::string EDistance::printDynamicArray() {
    std::string strOut = "";
    // size_t a = x.size();
    // size_t b = y.size();

    std::stringstream ss;
    for (const auto& row : opt) {
        for (int value : row) {
            ss << value << " ";
        }
        ss << "\n";
    }

    std::string optAsString = ss.str();
    return optAsString;
}
