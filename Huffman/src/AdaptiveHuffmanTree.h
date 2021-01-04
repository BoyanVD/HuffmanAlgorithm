#ifndef __ADAPTIVE_HUFFMAN_TREE_H
#define __ADAPTIVE_HUFFMAN_TREE_H

#include <iostream>
#include <string>
#include <vector>

const std::string ZERO_NODE_SYMBOL = "NULL-Node";

// USING THE FGK - Faller Gallager Knuth Huffman Coding
// ENCODING TREE IN THE FOLLOWING FORMAT :
//      <symbol1><code1><symbol2><code2>...<symboln><coden>
class AdaptiveHuffmanTree
{
private:
    struct Node
    {
        std::string signature;
        unsigned count;
        Node* left, *right, *parent;
        
        Node(const std::string& _signature, unsigned _count, Node* _left, Node* _right, Node* _parent) :
        signature(_signature), count(_count), left(_left), right(_right), parent(_parent) {}
    };

    Node* root;
    Node* zeroNode;
    // unsigned zeroNodeCounter;
    std::string buildedString;

    Node* findNodeForSymbol(const std::string& signature, Node* current);
    Node* highestNumberedLeafOfWeight(unsigned weight, Node* current);
    Node* highestNumberedNodeOfWeight(unsigned weight, Node* current);
    bool isLeaf(Node* node);
    void getAllNodesNumbered(unsigned weight, Node* current, std::vector<Node*>& list);
    void swapNodes(Node* node1, Node* node2);
    void printHelper(Node* current);

    // void encodeHelper(std::string code, Node* node, std::string& result);
    void encodeHelper(Node* node, std::string& result);

public:
    AdaptiveHuffmanTree();

    void readNextSymbol(char c);
    void print();
    std::string encode();
    void decode(const std::string encoded);
};

#endif