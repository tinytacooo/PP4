
/**********************
  HuffmanTree.hpp
  COP 4530 Spring '19
  Kelly MJ - PP4
**********************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <map>
#include <vector>

#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase {
public:
  HuffmanTree();
  ~HuffmanTree();
  std::string compress(const std::string inputStr);
  std::string serializeTree() const;
  std::string decompress(const std::string inputCode, const std::string serializeTree);
  /* Compression/serialization functions */
  void compressText(std::string inputStr);
  std::map<char, int> determineFrequencies(const std::string input);
  std::string getPrefix(HuffmanNode* H);
  HeapQueue<HuffmanNode*, HuffmanNode::Compare> initializePriorityQueue(std::map<char, int> freqMap);
  bool isLeft(HuffmanNode* H);
  HuffmanNode* buildTree(HeapQueue<HuffmanNode*, HuffmanNode::Compare>& pQueue);
  void postOrder(HuffmanNode* H, bool choice);
  /* Decompression functions */
  void decodePrefixes(std::string code);
private:
  /* for compression  */
  HuffmanNode* sortedTree;
  std::map<char, std::string> prefixCodes;
  std::string compressed;
  std::string serialized;
  /* for decompression */
  std::map<std::string, char> decodedPrefixes;
};

#endif /* HUFFMANTREE_H */
