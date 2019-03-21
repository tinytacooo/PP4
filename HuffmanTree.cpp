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

    postOrder(sortedTree, "root  parent ");

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

HuffmanNode* HuffmanTree::buildTree(HeapQueue<HuffmanNode*, HuffmanNode::Compare>& pQueue) {
    HuffmanNode* H;
    HuffmanNode* l;
    HuffmanNode* r;

    char g = 0;

    while (pQueue.size() > 1) {
        l = pQueue.min();
        pQueue.removeMin();
        r = pQueue.min();
        pQueue.removeMin();

        size_t f = l->getFrequency() + r->getFrequency();

        H = new HuffmanNode(g, f);
        l->parent = H;
        r->parent = H;
        H->left  = l;
        H->right = r;

        // check if node was built correctly
        // std::cout << "     " << H->getCharacter() << " " << H->getFrequency() << "\n " << l->getCharacter() << " " << l->getFrequency() << "   " << r->getCharacter() << " "<< r->getFrequency() << std::endl;

        pQueue.insert(H);
    }

    return H;
}

void HuffmanTree::postOrder(HuffmanNode* H, std::string s) {
    if(H == NULL)
        return;

    std::map<char, int> prefix;

    postOrder(H->left, "left  parent ");
    postOrder(H->right, "right parent ");

    if(H->isLeaf()) {
        std::string pre = getPrefix(H);
        prefixCodes[H->getCharacter()] = pre;
    }

}

std::string HuffmanTree::getPrefix(HuffmanNode* H) {
    if(H->parent == NULL)
        return "";

    std::string ret = "";
    ret += getPrefix(H->parent);

    if(isLeft(H))
        ret += "0";
    else
        ret += "1";

    return ret;
}

bool HuffmanTree::isLeft(HuffmanNode* H) {
    if (H == H->parent->left)
        std::cout << "ISLEFTCALLED " << H->getCharacter() << " is left\n";
    else std::cout << "ISLEFTCALLED " << H->getCharacter() << " is right\n";
    return (H == H->parent->left);
}
