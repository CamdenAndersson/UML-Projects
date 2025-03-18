// Copyright Camden Andersson 2024
#pragma once

#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <string>
#include <map>
#include <fstream>

class RandWriter {
 public:
    RandWriter(const std::string& text, size_t k);

    size_t orderK() const;

    int freq(const std::string& kgram) const;

    int freq(const std::string& kgram, char c) const;

    char kRand(const std::string& kgram);

    std::string generate(const std::string& kgram, size_t L);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    size_t k;
    std::string alphabet;
    std::map<std::string, std::map<char, int>> symbolTable;

    std::string circularText(const std::string& text, size_t k);

    void buildSymbolTable(const std::string& text);

    std::string activeAlphabet(const std::string& text);
};

class TextWriter {
 public:
    void TextWriter_main(int k, int L, const std::string& filename);
};

#endif /* RANDWRITER_HPP */
