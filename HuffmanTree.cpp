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
    // characterFrequencies.clear();       // delete map
}

std::string HuffmanTree::compress(const std::string inputStr) {
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pQueue;
    std::map<char, int> charFreq;

    charFreq = determineFrequencies(inputStr);
    pQueue = initializePriorityQueue(charFreq);
    sortedTree = buildTree(pQueue);

    postTraverseTree(sortedTree);

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

std::map<char, int> HuffmanTree::determineFrequencies(const std::string input) {
    std::map<char, int> freqMap;
    std::map<char, int>::iterator mapIt;

    for (auto& c : input) {
        if ((mapIt = freqMap.find(c)) != freqMap.end())
            mapIt->second += 1;
        else
            freqMap[c] = 1;
    }

    return freqMap;
}

HeapQueue<HuffmanNode*, HuffmanNode::Compare> HuffmanTree::initializePriorityQueue(std::map<char, int> freqMap) {
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;

    for (auto& mapIt : freqMap) {
        HuffmanNode* h = new HuffmanNode(mapIt.first, mapIt.second);
        priorityQueue.insert(h);
    }

/* // test code to check whether priority queue was built correctly
    while (!priorityQueue.empty()) {
        HuffmanNode* h = priorityQueue.min();
        char c = h->getCharacter();
        int i = h->getFrequency();

        std::cout << c << "\t" << i << "\n";
        priorityQueue.removeMin();
    }
*/
    return priorityQueue;
}

HuffmanNode* HuffmanTree::buildTree(HeapQueue<HuffmanNode*, HuffmanNode::Compare>) {
    HuffmanNode* H = new HuffmanNode('c', 2);
    return H;
}

void HuffmanTree::postTraverseTree(HuffmanNode* H) {
    HuffmanNode* t = H;
    //while (t->isRoot()) {
        std::cout << "ISROOT " << t->getCharacter() << std::endl;
    //    t = t->parent;
    //}

    bool leaf = t->isLeaf();
    bool branch = t->isBranch();
    bool root = t->isRoot();
    char c = t->getCharacter();
    size_t f = t->getFrequency();

    std::cout << leaf << " " << branch << " " << root << " " << c << " " << f << std::endl;
}
