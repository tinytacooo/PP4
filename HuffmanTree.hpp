/**********************
  HuffmanTree.hpp
  COP 4530 Spring '19
  Kelly MJ - PP4
**********************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase {
public:
  HuffmanTree();        // constructor; does nothing
  ~HuffmanTree();       // destructor; recursively destroys all nodes
  std::string compress(const std::string inputStr);
  std::string serializeTree();
  std::string decompress(const std::string inputCode, const std::string serializeTree);
private:
  std::string compressed;
  std::string serialized;
};

/*
 *   compress:
 *     - 
 */

#endif /* HUFFMANTREE_H */