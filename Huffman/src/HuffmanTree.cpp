#ifndef __HUFFMAN_TREE_CPP
#define __HUFFMAN_TREE_CPP

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(const std::string& str) : root(nullptr)
{
    this->originalString = str;
    this->buildTree(str);
}

HuffmanTree::~HuffmanTree()
{
    this->clear(this->root);
}

void HuffmanTree::clear(Node* current)
{
    if(current == nullptr)
    {
        return;
    }

    if(isLeaf(current))
    {
        delete current;
        return;
    }
    
    clear(current->left);
    clear(current->right);

    delete current;
}

void HuffmanTree::buildTree(const std::string& str)
{
    this->clear(this->root);
    frequency_queue frequencies = countFrequencies(str);

    while(frequencies.size() > 1)
    {
        Node* first = frequencies.top();
        frequencies.pop();
        Node* second = frequencies.top();
        frequencies.pop();

        std::string signature = first->signature + second->signature;
        unsigned count = first->count + second->count;

        Node* resultNode = new Node(signature, count, first, second);
        frequencies.push(resultNode);
    }

    this->root = frequencies.top();
}

HuffmanTree::frequency_queue HuffmanTree::countFrequencies(const std::string& str) const
{
    std::unordered_map<char, int> frequencies;

    for (int i = 0; i < str.size(); ++i)
    {
        char key = str[i];

        if (frequencies.find(key) == frequencies.end()) 
            frequencies[key] = 1;
        else
            frequencies[key] += 1;
    }

    frequency_queue result;
    for (auto frequency : frequencies)
    {
        std::string signature;
        signature += frequency.first;
        unsigned count = frequency.second;

        Node* next = new Node(signature, count);
        result.push(next);
    }

    return result;
}

void HuffmanTree::getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const
{
    if(HuffmanTree::isLeaf(curr))
        table[curr->signature[0]] = label;
    
    if(curr->left != nullptr)
        getCodes(curr->left, table, label + "0");
    
    if(curr->right != nullptr)
        getCodes(curr->right, table, label + "1");
}

std::unordered_map<char, std::string> HuffmanTree::getEncodingTable() const
{
    std::unordered_map<char, std::string> table;

    if (this->root->signature.size() == 1)
        table[this->root->signature[0]] = "0";
    else
        this->getCodes(this->root, table, "");

    return table;
}

bool HuffmanTree::isLeaf(Node* node)
{
    return (node->left == nullptr && node->right == nullptr);
}

bool HuffmanTree::empty() const
{
    return this->root == nullptr;
}

std::string HuffmanTree::encodeTree() const
{
    std::string res = "";
    encodeTreeHelper(this->root, res);
    return res;
}

void HuffmanTree::encodeTreeHelper(Node* node, std::string& result) const
{
    if(node == nullptr)
        return;
    
    if(isLeaf(node))
        result += (node->signature + std::to_string(node->count));

    encodeTreeHelper(node->left, result);
    encodeTreeHelper(node->right, result);
}

HuffmanTree::frequency_queue HuffmanTree::countFrequenciesFromCode(const std::string& str) const
{
    std::unordered_map<char, int> frequencies;

    for (int i = 0; i < str.size(); ++i)
    {
        char key = str[i];
        unsigned count = 0;
        ++i;

        while(str[i] >= '0' && str[i] <= '9')
        {
            count += (str[i] - '0');
            count *= 10;
            ++i;
        }
        count /= 10;
        --i;

        frequencies[key] = count;
    }

    frequency_queue result;
    for (auto frequency : frequencies)
    {
        std::string signature;
        signature += frequency.first;
        unsigned count = frequency.second;

        Node* next = new Node(signature, count);
        result.push(next);
    }

    return result;
}

void HuffmanTree::decodeTree(const std::string& str)
{
    this->clear(this->root);

    frequency_queue frequencies = countFrequenciesFromCode(str);

    while(frequencies.size() > 1)
    {
        Node* first = frequencies.top();
        frequencies.pop();
        Node* second = frequencies.top();
        frequencies.pop();

        std::string signature = first->signature + second->signature;
        unsigned count = first->count + second->count;

        Node* resultNode = new Node(signature, count, first, second);
        frequencies.push(resultNode);
    }

    this->root = frequencies.top();
}

std::string HuffmanTree::encodeText(const std::string& text) const
{
    std::string result = "";
    std::unordered_map<char, std::string> table = this->getEncodingTable();

    for(size_t i = 0; i < text.size(); ++i)
        result += table[text[i]];

    return result;
}

void HuffmanTree::decodeTextHelper(const std::string& text, Node* current, std::string& result) const
{
    if (HuffmanTree::isLeaf(current) && (text.size() > 0))
    {
        result += current->signature;
        decodeTextHelper(text, this->root, result);
    }

    if (HuffmanTree::isLeaf(current) && (text.size() == 0))
    {
        result += current->signature;
        return;
    }

    if (text[0] == '1' && current->right != nullptr)
        decodeTextHelper(text.substr(1), current->right, result);
    else if (text[0] == '0' && current->left != nullptr)
        decodeTextHelper(text.substr(1), current->left, result);    
}

std::string HuffmanTree::decodeText(const std::string& text) const
{
    std::string result = "";

    this->decodeTextHelper(text, this->root, result);

    return result;
}

#endif