// Copyright Camden Andersson 2024
#include "RandWriter.hpp"
#include <iostream>
#include <random>
#include <exception>
#include <algorithm>

RandWriter::RandWriter(const std::string& text, size_t k) : k(k) {
    alphabet = activeAlphabet(text);
    if (text.length() < k) {
       throw std::invalid_argument("Constructor Error: text < k");
    }
    // Testing out circular text
    std::string circText = circularText(text, k);
    // std::cout << circText << std::endl;

    buildSymbolTable(circularText(text, k));
}

size_t RandWriter::orderK() const {
    return k;
}

std::map<char, int> findEntry(const std::map<std::string,
std::map<char, int>>& symbolTable, const std::string& key) {
    auto it = symbolTable.find(key);
    if (it != symbolTable.end()) {
        return it->second;
    } else {
        // Return an empty map if the key is not found
        return {};
    }
}

std::string RandWriter::circularText(const std::string& text, size_t k) {
    return text + text.substr(0, k);
}

void RandWriter::buildSymbolTable(const std::string& text) {
    for (size_t i = 0; i < text.length() - k; ++i) {
        std::string kgram = text.substr(i, k);
        char nextChar = text[i + k];
        symbolTable[kgram][nextChar]++;
    }
}

std::string RandWriter::activeAlphabet(const std::string& text) {
    std::vector<bool> found(128, false);
    std::string result;
    for (char c : text) {
        if (!found[c]) {
            found[c] = true;
            result += c;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.orderK() << std::endl;
    os << "Alphabet: " << rw.alphabet << std::endl;
    for (const auto& entry : rw.symbolTable) {
        os << "K-gram: " << entry.first << std::endl;
        for (const auto& freqPair : entry.second) {
            os << "  Next char: " << freqPair.first <<
            " Frequency: " << freqPair.second << std::endl;
        }
    }
    return os;
}

char RandWriter::kRand(const std::string& kgram) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Rewrite
    std::vector<int> f;
    std::vector<char> possibleChars;
    int total = 0;
    int n = 0;

    if (kgram.size() != k) {
       throw std::length_error("kRand Length Error");
    }
    // Find the possible letters that follow kgram
    for (char c : alphabet) {
        n = freq(kgram, c);
        if (n > 0) {
            f.push_back(n);
            total += n;
            possibleChars.push_back(c);
        }
    }

    // TO DO: Throw an exception here
    if (possibleChars.size() == 0) {
       // std::cout << "EXCEPTION, will crash!" << std::endl;
       throw std::length_error("possibleChars.size() == 0");
    }

    // Build the percentages
    std::vector<double> percentages;
    for (size_t i = 0; i < f.size(); i++) {
        f[i] = static_cast<int>((static_cast<double>(f[i]) / static_cast<double>(total)) * 100.0);
    }
    std::discrete_distribution<> d(f.begin(), f.end());

    // Use the random generator
    int randomNum = d(gen);
    // char cReturn = possibleChars[randomNum];
    return possibleChars[randomNum];
}

int RandWriter::freq(const std::string& kgram) const {
    // Note that for this function you can't use the map's
    // count() function as that just returns 1 or 0.
    if (kgram.size() != k) {
       throw std::length_error("freq Length Error");
    }
    std::map<char, int> entry = findEntry(symbolTable, kgram);

    int nNumOccurences = 0;
    for (const auto& pair : entry) {
        // Sum up all the frequencies in the last part of the map
        nNumOccurences += pair.second;
    }

    return nNumOccurences;
}
/*
int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.size() != k) {
       throw std::length_error("freq Length Error (2)");
    }
    if (symbolTable.count(kgram) && symbolTable.at(kgram).count(c)) {
        return symbolTable.at(kgram).at(c);
    }
    return 0;
}
*/
int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.size() != k) {
        throw std::length_error("freq Length Error (2)");
    }
    if (symbolTable.count(kgram)) {
        const auto& charMap = symbolTable.at(kgram);

        auto it = std::find_if(charMap.begin(), charMap.end(), [c](const std::pair<char, int>& p) {
            return p.first == c;
        });

        return (it != charMap.end()) ? it->second : 0;
    }
    return 0;
}



std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (kgram.size() != k) {
       throw std::length_error("generate Length Error");
    }
    std::string result = kgram;

    for (size_t i = k; i < L; ++i) {
        std::string sz = result.substr(result.length() - k);
        char nextChar = kRand(sz);
        result += nextChar;
    }
    return result;
}



std::string read_file_to_string(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string file_contents;
    file.seekg(0, std::ios::end);
    file_contents.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    file_contents.assign((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    return file_contents;
}

std::string replace_newlines_with_spaces(const std::string& inText) {
    std::string result = inText;
    size_t startPos = 0;
    while ((startPos = result.find('\n', startPos)) != std::string::npos) {
        result.replace(startPos, 1, " ");
        startPos += 1;  // Move past the replaced character
    }
    return result;
}

void TextWriter::TextWriter_main(int k, int L, const std::string& filename) {
    // Open the file that contains the text & display it
    // std::string rawText = read_file_to_string(filename);
    //  if (!rawText.empty()) {
    //    std::cout << "File contents:\n" << rawText << std::endl;
    //  }
    std::string text = replace_newlines_with_spaces(filename);

    // Build the Markov model and display the frequencies
    RandWriter rw(text, k);
    // std::cout << rw << std::endl;

    // Set the seed kgram and generate the text
    std::string kgram = text.substr(0, k);
    std::cout << rw.generate(kgram, L) << std::endl;
}
