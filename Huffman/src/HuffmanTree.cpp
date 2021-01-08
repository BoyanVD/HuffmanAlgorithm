#ifndef __HUFFMAN_TREE_CPP
#define __HUFFMAN_TREE_CPP

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(const std::string& str) : root(nullptr)
{
    this->originalString = str;
    this->buildTree(str);
}

void HuffmanTree::clear(Node*& startingNode)
{
    if(startingNode == nullptr)
        return;
    
    if(startingNode->left == nullptr && startingNode->right == nullptr)
        delete startingNode;
    
    clear(startingNode->left);
    clear(startingNode->right);
    delete startingNode;
}

void HuffmanTree::buildTree(const std::string& str)
{
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

void HuffmanTree::print()
{
    helper(this->root);
}

void HuffmanTree::helper(Node* curr)
{
    std::queue<Node*> res;
    res.push(curr);

    while(!res.empty())
    {
        Node* c = res.front();
        std::cout << " ( " << c->signature << " " << c->count << " ) ";
        res.pop();

        if(c->left != nullptr)
            res.push(c->left);
        
        if(c->right != nullptr)
            res.push(c->right);
    }
}



void HuffmanTree::getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const
{
    if(HuffmanTree::isLeaf(curr)) // MAKE FUNCTION TO CHECK THAT CASE (bool isLeaf(Node)) !
        table[curr->signature[0]] = label; // Think of validation
    
    if(curr->left != nullptr)
        getCodes(curr->left, table, label + "0");
    
    if(curr->right != nullptr)
        getCodes(curr->right, table, label + "1");
}

std::unordered_map<char, std::string> HuffmanTree::getEncodingTable() const
{
    std::unordered_map<char, std::string> table;

    if (this->root->signature.size() == 1) // MAKE FUNCTION TO CHECK THAT CASE !
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

std::string HuffmanTree::encodeTree() // encode with count property of nodes instead of counting frequencies
{
    std::string res = "";
    encodeHelper(this->root, res);
    return res;
}

void HuffmanTree::encodeHelper(Node* node, std::string& result)
{
    if(node == nullptr)
        return;
    
    if(isLeaf(node))
        result += (node->signature + std::to_string(node->count));

    encodeHelper(node->left, result);
    encodeHelper(node->right, result);
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
    // this->clear()



    // ----------------------------------------------------DUPLICATING CODE-------------------------------------------------
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
    // ----------------------------------------------------DUPLICATING CODE------------------------------------------------
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
    if (HuffmanTree::isLeaf(current) && (text.size() > 0)) // FUNCTION TO CHECK CONDITION
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