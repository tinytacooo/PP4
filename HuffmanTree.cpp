/**********************
  HuffmanTree.cpp
  COP 4530 Spring '19
  Kelly MJ - PP4
**********************/

#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree() {
    compressed = "";
    serialized = "";
}

HuffmanTree::~HuffmanTree() {
    characterFrequencies.clear();
}

std::string HuffmanTree::compress(const std::string inputStr) {
    determineFrequencies(inputStr);
    return "Done";
}

std::string HuffmanTree::serializeTree() const {
    return "ret";
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializeTree){
    return "ret";
}


/*
 *  Helper functions
 */

void HuffmanTree::determineFrequencies(const std::string input) {
    std::map<char, int>::iterator mapIt;

    for (auto& c : input) {
        if ((mapIt = characterFrequencies.find(c)) != characterFrequencies.end())
            mapIt->second += 1;
        else
            characterFrequencies[c] = 1;
    }
}
