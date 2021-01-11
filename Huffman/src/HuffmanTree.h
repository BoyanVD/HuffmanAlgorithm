#ifndef __HUFFMAN_TREE_H
#define __HUFFMAN_TREE_H

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

class HuffmanTree
{
private:
    struct Node
    {
        std::string signature;
        unsigned count;
        Node* left, *right;

        Node() : signature(""), count(0), left(nullptr), right(nullptr) {}
        Node(const std::string _signature) : signature(_signature), count(0), left(nullptr), right(nullptr) {}
        Node(const std::string _signature, unsigned _count) : signature(_signature), count(_count), left(nullptr), right(nullptr) {}
        Node(const std::string _signature, unsigned _count, Node* _left, Node* _right) : signature(_signature), count(_count), left(_left), right(_right) {}
    };

    struct NodeComparator
    { 
        bool operator()(const Node* n1, const Node* n2) 
        {
            if (n1->count != n2->count)
                return (n1->count > n2->count);
            else
                return (n1->signature.compare(n2->signature) > 0);
        } 
    };

    typedef std::priority_queue<Node*, std::vector<Node*>, NodeComparator> frequency_queue; 

    Node* root;
    std::string originalString;

    frequency_queue countFrequencies(const std::string& str) const;
    frequency_queue countFrequenciesFromCode(const std::string& str) const;

    void clear(Node* current);
    static bool isLeaf(Node* node);

    void getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const;
    void decodeTextHelper(const std::string& text, Node* current, std::string& result) const;
    void encodeTreeHelper(Node* node, std::string& result) const;

public:
    HuffmanTree() : root(nullptr) {}
    HuffmanTree(const std::string& str);
    ~HuffmanTree();
    
    void buildTree(const std::string& str);
    bool empty() const;

    std::string encodeTree() const;    
    void decodeTree(const std::string& str);

    std::string encodeText(const std::string& text) const;
    std::string decodeText(const std::string& text) const;
    std::unordered_map<char, std::string> getEncodingTable() const;
};

#endif