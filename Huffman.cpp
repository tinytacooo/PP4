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
    prefixCodes.clear();
    decodedPrefixes.clear();
}

std::string HuffmanTree::compress(const std::string inputStr) {
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> pQueue;
    std::map<char, int> charFreq;

    charFreq = determineFrequencies(inputStr);      // determine frequncy of each character
    pQueue = initializePriorityQueue(charFreq);     // add all characters/frequencies to a HeapQueue
    sortedTree = buildTree(pQueue);                 // build tree (using HuffmanNodes) using priority queue
    postOrder(sortedTree, true);                    // traverse tree to get character prefixes (the bool arg is explained below)
    compressText(inputStr);                         // compress input string using prefixes

    return compressed;
}

std::string HuffmanTree::serializeTree() const {
    return serialized;      // tree was already serialized when postOrder() was called
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializeTree){
    std::map<std::string, char>::iterator it;
    std::string ret;
    std::string temp = "";

    decodePrefixes(serializeTree);

    for (auto c : inputCode) {
        temp += c;                                                          // read in characters from compressed code until current "buffer" matches a prefix code
        if((it = decodedPrefixes.find(temp)) != decodedPrefixes.end()) {
            ret += it->second;                                              // when prefix is recognized, add corresponding character to return string
            temp.clear();                                                   // clear buffer
        }
    }

    return ret;     // decompressed string
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
         l = pQueue.min();          // remove the two nodes with the smallest "weight" (frequency) from the queue
         pQueue.removeMin();
         r = pQueue.min();
         pQueue.removeMin();

         size_t f = l->getFrequency() + r->getFrequency();      // combine frequencies of 2 current nodes to get their soon-to-be parent's frequency

         H = new HuffmanNode(g, f); // create an intermediate node
         l->parent = H;             // link the two nodes from before
         r->parent = H;
         H->left  = l;
         H->right = r;

         pQueue.insert(H);          // stick the intermediate node back in the queue
     }

     return H;
 }

 void HuffmanTree::compressText(std::string inputStr) {
     for (auto& c : inputStr) {             // iterate through all characters in the input string.
         compressed  += prefixCodes[c];     // add each char's prefix code to the "compressed" string (private variable in HuffmanTree)
     }
 }

std::map<char, int> HuffmanTree::determineFrequencies(const std::string input) {
    std::map<char, int> freqMap;
    std::map<char, int>::iterator mapIt;

    for (auto& c : input) {                                     // add all characters and their frequencies to a map
        if ((mapIt = freqMap.find(c)) != freqMap.end())
            mapIt->second += 1;
        else
            freqMap[c] = 1;
    }

    return freqMap;
}

HeapQueue<HuffmanNode*, HuffmanNode::Compare> HuffmanTree::initializePriorityQueue(std::map<char, int> freqMap) {
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;

    for (auto& mapIt : freqMap) {                                       // insert all characters and their frequencies into a HeapQueue (min heap)
        HuffmanNode* h = new HuffmanNode(mapIt.first, mapIt.second);
        priorityQueue.insert(h);
    }

    return priorityQueue;
}

bool HuffmanTree::isLeft(HuffmanNode* H) {
    return (H == H->parent->left);      // determine whether the node in question is the left child of its parent
}

// this one's weird, so let me explain:
// I needed 2 functions that could do a post-order traversal of a Huffman tree (one for compression, one for decompression).
// My computer was being a b** and it didn't like when I tried to write code for both functions in my code.
// Polymorphism wasn't really an option, so there's a bool arg to select one chunk of code over another. It's messy, but I'm tired and it's the best I got
void HuffmanTree::postOrder(HuffmanNode* H, bool choice) {
    if(H == NULL)
        return;

    if(choice == true) {                                // when choice == TRUE, use the code for COMPRESSION
        postOrder(H->left, true);                       // recursively visit all nodes in tree in post-order
        postOrder(H->right, true);
        if(H->isLeaf()) {                               // when a leaf is encountered, find its prefix
            std::string pre = getPrefix(H);
            prefixCodes[H->getCharacter()] = pre;

            serialized += "L";                          // also, add an L<char> to the serialized tree string
            serialized += H->getCharacter();
        }
        else {
            serialized += "B";                          // when a branch is encountered, note it in the serialized tree string
        }
    }
    else {                                              // when choice == FALSE, use the code for DECOMPRESSION
        postOrder(H->left, false);                      // recursively visit every node of the (reconstructed) tree
        postOrder(H->right, false);
        if(H->isLeaf()) {                               // if node is a leaf, find its prefix
            std::string pre = getPrefix(H);
            decodedPrefixes[pre] = H->getCharacter();
        }
    }
}

std::string HuffmanTree::getPrefix(HuffmanNode* H) {
    if(H->parent == NULL)
        return "";

    std::string ret = "";
    ret += getPrefix(H->parent);

    if(isLeft(H))       // Recursively trace the node's path in the tree until the root is found.
        ret += "0";     // If the current node it the left child of its parent, add a 0 to the prefix. Add a 1 otherwise.
    else
        ret += "1";

    return ret;
}


/*
 *  Decompression function
 */
void HuffmanTree::decodePrefixes(std::string code) {
     std::map<std::string, char> ret;
     std::vector<HuffmanNode*> nodes;
     char g = '!';                      // dummy char to initialize intermediate nodes

     for (unsigned int i = 0; i < code.length(); i++) {
         if(code[i] == 'L') {
             HuffmanNode* h = new HuffmanNode(code[++i], 0);        // create new nodes when a leaf is encountered
             nodes.push_back(h);
         } else if (code[i] == 'B') {
             HuffmanNode* H = new HuffmanNode(g, 0);                // link the last 2 nodes when a branch is encountered
             HuffmanNode* r = nodes.back();                         // pop the 2 most recent nodes from the vector
             nodes.pop_back();
             HuffmanNode* l = nodes.back();
             nodes.pop_back();

             H->right = r;              // link the nodes with an intermediate node
             H->left = l;
             r->parent = H;
             l->parent = H;
             nodes.push_back(H);        // stick it back in the queue
         }
     }

     HuffmanNode* H = nodes.back();     // do a postorder traversal of the tree to get the prefix code of each character.
     postOrder(H, false);                  // the map of <prefixes, char> is stored as a private variable in the HuffmanTree Class
 }
