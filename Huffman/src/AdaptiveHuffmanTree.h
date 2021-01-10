#ifndef __ADAPTIVE_HUFFMAN_TREE_H
#define __ADAPTIVE_HUFFMAN_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

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

    void clear(Node* current);
    Node* findNodeForSymbol(const std::string& signature, Node* current);
    Node* highestNumberedLeafOfWeight(unsigned weight, Node* current);
    Node* highestNumberedNodeOfWeight(unsigned weight, Node* current);
    static bool isLeaf(Node* node); // Same for both trees.
    void getAllNodesNumbered(unsigned weight, Node* current, std::vector<Node*>& list);
    void swapNodes(Node* node1, Node* node2);
    void printHelper(Node* current);

    void getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const; // Same for both trees .
    void decodeTextHelper(const std::string& text, Node* current, std::string& result) const; // Same for both trees.
    void encodeTreeHelper(Node* node, std::string& result); // Same for both trees.

public:
    AdaptiveHuffmanTree();
    ~AdaptiveHuffmanTree();

    void readNextSymbol(char c);
    void print();
    std::string encodeTree();
    void decodeTree(const std::string encoded);

    std::string encodeText(const std::string& text) const; // Same for both trees.
    std::string decodeText(const std::string& text) const; // Same for both trees.
    std::unordered_map<char, std::string> getEncodingTable() const; // Same for both trees . 
};

#endif