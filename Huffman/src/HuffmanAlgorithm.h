#ifndef __HUFFMAN_ALGORITHM_H
#define __HUFFMAN_ALGORITHM_H

#include <iostream>
#include "HuffmanTree.h"

class HuffmanAlgorithm
{
private:
    HuffmanTree tree;
public:
    HuffmanAlgorithm() {}
    HuffmanAlgorithm(const std::string& str) { this->tree.buildTree(str); }

    // std::string encodeBinary(const std::string& str) const;
    // std::string encodeDecimal(const std::string& str) const;
    // std::string decode(const std::string& str) const;
};

#endif