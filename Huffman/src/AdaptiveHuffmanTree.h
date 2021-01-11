#ifndef __ADAPTIVE_HUFFMAN_TREE_H
#define __ADAPTIVE_HUFFMAN_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

const std::string ZERO_NODE_SYMBOL = "NULL-Node";

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

    void clear(Node* current);
    Node* findNodeForSymbol(const std::string& signature, Node* current);
    Node* highestNumberedLeafOfWeight(unsigned weight, Node* current);
    Node* highestNumberedNodeOfWeight(unsigned weight, Node* current);
    static bool isLeaf(Node* node);
    void getAllLeafsNumbered(unsigned weight, Node* current, std::vector<Node*>& list);
    void swapNodes(Node* node1, Node* node2);
    void printHelper(Node* current);

    void getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const;
    void decodeTextHelper(const std::string& text, Node* current, std::string& result) const;
    void encodeTreeHelper(Node* node, std::string& result);

public:
    AdaptiveHuffmanTree();
    ~AdaptiveHuffmanTree();

    void readNextSymbol(char c);
    void print();
    std::string encodeTree();
    void decodeTree(const std::string encoded);

    std::string encodeText(const std::string& text) const;
    std::string decodeText(const std::string& text) const;
    std::unordered_map<char, std::string> getEncodingTable() const; 
};

#endif