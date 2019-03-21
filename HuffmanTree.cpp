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
    postOrder(sortedTree, true);
    compressText(inputStr);

    return compressed;
}

std::string HuffmanTree::serializeTree() const {
    std::cout << serialized << std::endl;
    return serialized;
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializeTree){
    std::map<std::string, char> decodedPrefixes;
    std::string ret;
    std::string temp;

    decodedPrefixes = decodePrefixes(serializeTree);

    return "done";
}


/*
 *  Compression/serialization functions
 */

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

         pQueue.insert(H);
     }

     return H;
 }

 void HuffmanTree::compressText(std::string inputStr) {
     for (auto& c : inputStr) {
         compressed  += prefixCodes[c];
     }
 }

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

    return priorityQueue;
}

bool HuffmanTree::isLeft(HuffmanNode* H) {
    return (H == H->parent->left);
}

void HuffmanTree::postOrder(HuffmanNode* H, bool choice) {
    if(H == NULL)
        return;
/*
    postOrder(H->left, true);
    postOrder(H->right, true);
*/
    if(choice == true) {
        postOrder(H->left, true);
        postOrder(H->right, true);
        if(H->isLeaf()) {
            std::string pre = getPrefix(H);
            prefixCodes[H->getCharacter()] = pre;

            serialized += "L";
            serialized += H->getCharacter();
        }
        else {
            serialized += "B";
        }
    } else {
        postOrder(H->left, false);
        postOrder(H->right, false);
        if(H->isLeaf()) {
            std::cout << "LEAF: " << H->getCharacter() << std::endl;
        }
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


/*
 *  Decompression functions
 */

 std::map<std::string, char> HuffmanTree::decodePrefixes(std::string code) {
     std::map<std::string, char> ret;
     std::vector<HuffmanNode*> nodes;
     char g = '!';

     for (unsigned int i = 0; i < code.length(); i++) {
         if(code[i] == 'L') {
             HuffmanNode* h = new HuffmanNode(code[++i], 0);        // make a node
             nodes.push_back(h);
         } else if (code[i] == 'B') {
             //link the last 2 nodes
             HuffmanNode* H = new HuffmanNode(g++, 0);
             HuffmanNode* r = nodes.back();
             nodes.pop_back();
             HuffmanNode* l = nodes.back();
             nodes.pop_back();

             H->right = r;
             H->left = l;
             r->parent = H;
             l->parent = H;
             nodes.push_back(H);

             //postOrder(H);    //remove
             //std::cout << std::endl;
             //std::cout << "   " << H->getCharacter() << "\n " << H->left->getCharacter() << "   " << H->right->getCharacter();
         }
     }

     HuffmanNode *H = nodes.back(); //remove
     postOrder(H, false);    //remove
     std::cout << std::endl;

     return ret;
 }
