#ifndef __ADAPTIVE_HUFFMAN_TREE_CPP
#define __ADAPTIVE_HUFFMAN_TREE_CPP

#include "AdaptiveHuffmanTree.h"
#include <exception>
#include "HelperFunctionality.h"

AdaptiveHuffmanTree::AdaptiveHuffmanTree()
{
    Node* node = new Node(ZERO_NODE_SYMBOL + " " + std::to_string(0), 0, nullptr, nullptr, nullptr);

    this->root = node;
    this->zeroNode = node;
}

AdaptiveHuffmanTree::~AdaptiveHuffmanTree()
{
    this->clear(this->root);
}

bool AdaptiveHuffmanTree::isLeaf(Node* node)
{
    return node->left == nullptr && node->right == nullptr;
}

void AdaptiveHuffmanTree::clear(Node* current)
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

AdaptiveHuffmanTree::Node* AdaptiveHuffmanTree::findNodeForSymbol(const std::string& signature, Node* current)
{
    if(current == nullptr)
        return nullptr;
    
    if(signature.compare(current->signature) == 0)
        return current;
    
    Node* resultFromLeft = findNodeForSymbol(signature, current->left);
    if (resultFromLeft != nullptr)
        return resultFromLeft;

    Node* resultFromRight = findNodeForSymbol(signature, current->right);
    if (resultFromRight != nullptr)
        return resultFromRight;

    return nullptr;
}

void AdaptiveHuffmanTree::swapNodes(Node* node1, Node* node2)
{
    if(node1->parent->left == node1)
        node1->parent->left = node2;
    else if(node1->parent->right == node1)
        node1->parent->right = node2;

    if(node2->parent->left == node2)
        node2->parent->left = node1;
    else if(node2->parent->right == node2)
        node2->parent->right = node1;

    Node* tempParent = node1->parent;
    node1->parent = node2->parent;
    node2->parent = tempParent;
}

void AdaptiveHuffmanTree::getAllNodesNumbered(unsigned weight, Node* current, std::vector<Node*>& list)
{
    if(current == nullptr)
    {
        return;
    }
    
    if(this->isLeaf(current) && current->count == weight)
    {
        list.push_back(current);
        return;
    }

    getAllNodesNumbered(weight, current->left, list);
    getAllNodesNumbered(weight, current->right, list);
}

AdaptiveHuffmanTree::Node* AdaptiveHuffmanTree::highestNumberedLeafOfWeight(unsigned weight, Node* current)
{
    // get all leafs of weight in vector where on index 0 stays the left most leaf and we will take the last element
    std::vector<Node*> leafsOfWeight;
    getAllNodesNumbered(weight, current, leafsOfWeight);
    return leafsOfWeight[leafsOfWeight.size() - 1];
}

AdaptiveHuffmanTree::Node* AdaptiveHuffmanTree::highestNumberedNodeOfWeight(unsigned weight, Node* current)
{
    if(current == nullptr || current->count < weight)
        return nullptr;
    
    if(current->count == weight)
        return current;
    
    Node* leftResult = highestNumberedNodeOfWeight(weight, current->left);
    Node* rightResult = highestNumberedNodeOfWeight(weight, current->right);

    if(leftResult != nullptr)
        return leftResult;
    else
        return rightResult;
}

void AdaptiveHuffmanTree::readNextSymbol(char c)
{
    // p = pointer to symbol’s node;
    
    // if ( p == NULL ){  /*  a new symbol!  */
    //     Create two leaf children of the 0-node,
    //       such that the right child is the new
    //         symbol node and the left child is
    //         the new 0-node;
    //     p = parent of the new symbol node;
    // }

    std::string signature = "";
    signature += c;

    Node* nodeForSymbol = this->findNodeForSymbol(signature, this->root);

    if(nodeForSymbol == nullptr)
    {
        Node* newZeroNode = new Node(ZERO_NODE_SYMBOL, 0, nullptr, nullptr, this->zeroNode);
        nodeForSymbol = new Node(signature, 1, nullptr, nullptr, this->zeroNode);

        this->zeroNode->left = newZeroNode;
        this->zeroNode->right = nodeForSymbol;

        nodeForSymbol = this->zeroNode;
        this->zeroNode = newZeroNode;
    }

    // /*  if the two nodes are siblings.  */
    // if ( p’s parent == 0-node’s parent ){
    //     Swap p in the tree with the highest
    //       numbered “leaf” of equal weight;
    //     p’s weight = p’s weight + 1;
    //     p = parent of p;
    // }

    if (nodeForSymbol->parent == this->zeroNode->parent)
    {
        Node* highestNumberedLeaf = this->highestNumberedLeafOfWeight(nodeForSymbol->count, nodeForSymbol);
        this->swapNodes(highestNumberedLeaf, nodeForSymbol);
        nodeForSymbol->count += 1;
        nodeForSymbol = nodeForSymbol->parent;
    }

    // while ( p != root of the tree ){
    //     Swap p in the tree with the highest
    //       numbered “node” of equal weight;
    //     p’s weight = p’s weight + 1;
    //     p = parent of p;
    // }

    while(nodeForSymbol != this->root)
    {
        Node* highestNumberedNode = this->highestNumberedNodeOfWeight(nodeForSymbol->count, nodeForSymbol);
        nodeForSymbol->count += 1;
        nodeForSymbol = nodeForSymbol->parent;
    }

    this->root->count += 1;
}

void AdaptiveHuffmanTree::printHelper(Node* current)
{
    if(current == nullptr)
    {
        return;
    }
    
    printHelper(current->left);
    std::cout << " ( " << current->signature << ", " << current->count << " ) ";
    printHelper(current->right);
}

void AdaptiveHuffmanTree::print()
{
    this->printHelper(this->root);
}

void AdaptiveHuffmanTree::encodeTreeHelper(Node* node, std::string& result)
{
    if(node == nullptr)
        return;
    
    if(isLeaf(node))
        result += (node->signature + std::to_string(node->count));

    encodeTreeHelper(node->left, result);
    encodeTreeHelper(node->right, result);
}

std::string AdaptiveHuffmanTree::encodeTree()  // encode with count property of nodes
{
    std::string res = "";
    encodeTreeHelper(this->root, res);
    return res;
}

// // PUT IN ANOTHER FILE CALLED HELPER FUNCTIONALITY--------START-------------------------
// unsigned readNextNumber(const std::string& str)
// {
//     unsigned res = 0;
//     unsigned index = 0;

//     while(str[index] >= '0' && str[index] <= '9' && index < str.length())
//     {
//         res += str[index] - '0';
//         res *= 10;
//         ++index;
//     }
//     res /= 10;

//     return res;
// }

// unsigned numLength(unsigned num)
// {
//     unsigned counter = 0;
//     while(num > 0)
//     {
//         ++counter;
//         num /= 10;
//     }

//     return counter;
// }
// //--------------------------------------------------------END----------------------------

void AdaptiveHuffmanTree::decodeTree(const std::string encoded)
{
    this->clear(this->root); //-------------------------------------------------------- NEW ----------------------------

    // Check if string starts with "NULL-Node0"
    size_t index = ZERO_NODE_SYMBOL.length() + 1;
    Node* leftNode = new Node(ZERO_NODE_SYMBOL, 0, nullptr, nullptr, nullptr);
    if (index >= encoded.length())
    {
        this->root = leftNode;
        return;
    }

    while(index < encoded.size())
    {
        std::string signature = "";
        signature += encoded[index];
        ++index;
        unsigned count = readNextNumber(encoded.substr(index));
        index += numLength(count);

        Node* rightNode = new Node(signature, count, nullptr, nullptr, nullptr);
        Node* rootNode = new Node(ZERO_NODE_SYMBOL, (leftNode->count + rightNode->count), leftNode, rightNode, nullptr);
        leftNode->parent = rootNode;
        rightNode->parent = rootNode;

        leftNode = rootNode;
        this->root = rootNode;
    }
}



// -------------------------------------------------- SAME FOR BOTH TREES START !!!!!!!!!!!!!!!!!!!!!!!!-----------------------------------------
void AdaptiveHuffmanTree::getCodes(Node* curr, std::unordered_map<char, std::string>& table, std::string label) const
{
    if(isLeaf(curr)) // MAKE FUNCTION TO CHECK THAT CASE (bool isLeaf(Node)) !
        table[curr->signature[0]] = label; // Think of validation
    
    if(curr->left != nullptr)
        getCodes(curr->left, table, label + "0");
    
    if(curr->right != nullptr)
        getCodes(curr->right, table, label + "1");
}

std::unordered_map<char, std::string> AdaptiveHuffmanTree::getEncodingTable() const
{
    std::unordered_map<char, std::string> table;

    if (this->root->signature.size() == 1) // MAKE FUNCTION TO CHECK THAT CASE !
        table[this->root->signature[0]] = "0";
    else
        this->getCodes(this->root, table, "");

    return table;
}

std::string AdaptiveHuffmanTree::encodeText(const std::string& text) const
{
    std::string result = "";
    std::unordered_map<char, std::string> table = this->getEncodingTable();

    for(size_t i = 0; i < text.size(); ++i)
        result += table[text[i]];

    return result;
}

void AdaptiveHuffmanTree::decodeTextHelper(const std::string& text, Node* current, std::string& result) const
{
    if (AdaptiveHuffmanTree::isLeaf(current) && (text.size() > 0)) // FUNCTION TO CHECK CONDITION
    {
        result += current->signature;
        decodeTextHelper(text, this->root, result);
    }

    if (AdaptiveHuffmanTree::isLeaf(current) && (text.size() == 0))
    {
        result += current->signature;
        return;
    }

    if (text[0] == '1' && current->right != nullptr)
        decodeTextHelper(text.substr(1), current->right, result);
    else if (text[0] == '0' && current->left != nullptr)
        decodeTextHelper(text.substr(1), current->left, result);    
}

std::string AdaptiveHuffmanTree::decodeText(const std::string& text) const
{
    std::string result = "";

    this->decodeTextHelper(text, this->root, result);

    return result;
}
// -------------------------------------------------- SAME FOR BOTH TREES END !!!!!!!!!!!!!!!!!!!!!!!!-----------------------------------------

#endif