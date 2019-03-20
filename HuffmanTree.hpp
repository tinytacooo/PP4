
/**********************
  HuffmanTree.hpp
  COP 4530 Spring '19
  Kelly MJ - PP4
**********************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <map>

#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase {
public:
  HuffmanTree();        // constructor; does nothing
  ~HuffmanTree();       // destructor; recursively destroys all nodes
  std::string compress(const std::string inputStr);
  std::string serializeTree() const;
  std::string decompress(const std::string inputCode, const std::string serializeTree);
  /* Helper functions */
  void determineFrequencies(const std::string input);
private:
  std::map<char, int> characterFrequencies;     // character frequencies
  std::string compressed;
  std::string serialized;
};

#endif /* HUFFMANTREE_H */
