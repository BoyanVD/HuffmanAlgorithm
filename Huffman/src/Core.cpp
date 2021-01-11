#ifndef __CORE_CPP
#define __CORE_CPP

#include "Core.h"
#include "HuffmanTree.h"
#include "AdaptiveHuffmanTree.h"

#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

/**
 * Encoding in the following format :
 * <bool adaptive>
 * <std::string three>
 * <std::string code>
 */
void Core::encodeTxtFileContentStandard(std::ostream& output, std::istream& input)
{
    std::stringstream stream;
    stream << input.rdbuf();
    std::string content = stream.str();

    HuffmanTree tree(content);
    std::string encodedText = tree.encodeText(content);
    std::string encodedTree = tree.encodeTree();

    output << 0 << std::endl;
    output << encodedTree << std::endl;
    output << encodedText;
}

void Core::encodeTxtFileContentAdaptive(std::ostream& output, std::istream& input)
{
    AdaptiveHuffmanTree tree;
    char c;
    std::string content = "";
    while (input.get(c))
    {
        content += c;
        tree.readNextSymbol(c);
    }
    
    std::string encodedText = tree.encodeText(content);
    std::string encodedTree = tree.encodeTree();

    output << 1 << std::endl;
    output << encodedTree << std::endl;
    output << encodedText;

}

void Core::encodeTxtFileContent(const Command& c)
{
    std::ifstream inputFile;
    inputFile.open(c.getInputFile());
    std::ofstream outputFile(c.getOutputFile());

    if(c.isAdaptiveMode())
        encodeTxtFileContentAdaptive(outputFile, inputFile);
    else 
        encodeTxtFileContentStandard(outputFile, inputFile);
}

std::string Core::decodeTxtFileContentStandard(const std::string& encodedText, const std::string& encodedTree)
{
    HuffmanTree decodedTree;
    decodedTree.decodeTree(encodedTree);
    std::string decodedText = decodedTree.decodeText(encodedText);

    return decodedText;
}

std::string Core::decodeTxtFileContentAdaptive(const std::string& encodedText, const std::string& encodedTree)
{
    AdaptiveHuffmanTree decodedTree;
    decodedTree.decodeTree(encodedTree);
    std::string decodedText = decodedTree.decodeText(encodedText);

    return decodedText;
}

void Core::decodeTxtFileContent(const Command& c)
{
    std::ifstream inputFile;
    inputFile.open(c.getInputFile());
    std::ofstream outputFile(c.getOutputFile());

    std::string isAdaptive;
    std::string encodedText;
    std::string encodedTree;

    getline(inputFile, isAdaptive);
    getline(inputFile, encodedTree);
    getline(inputFile, encodedText);

    if (isAdaptive.compare("0") == 0)
        outputFile << decodeTxtFileContentStandard(encodedText, encodedTree);
    else
        outputFile << decodeTxtFileContentAdaptive(encodedText, encodedTree);
}

unsigned Core::binaryStringToNum(const std::string& str)
{
    unsigned res = 0;

    for(int i = str.length() - 1; i >= 0; --i)
    {
        unsigned coeff = str[i] - '0';
        res += (coeff * pow(2, (str.length() - 1 - i)));
    }

    return res;
}

void Core::debugMode(std::istream& input)
{
    std::stringstream stream;
    stream << input.rdbuf();
    std::string content = stream.str();

    HuffmanTree tree(content);
    std::string encodedText = tree.encodeText(content);

    size_t startIndex = 0;
    size_t len = 8;

    while(startIndex < encodedText.length())
    {
        std::string code;

        if (startIndex + len > encodedText.length())
        {
            code = encodedText.substr(startIndex);
            for (int i = 0; i < startIndex + len - encodedText.length(); ++i)
                code += '0';
                
        } else
        {
            code = encodedText.substr(startIndex, len);
        }

        std::cout << code << " " << Core::binaryStringToNum(code) << " ";

        startIndex += len;
    }

    std::cout << std::endl;
}

void Core::compressionLevel(const Command& c)
{
    std::ifstream originalFile(c.getInputFile());
    std::ifstream compressedFile(c.getOutputFile());

    std::stringstream stream;
    stream << originalFile.rdbuf();
    std::string originalText = stream.str();

    std::string isAdaptive;
    std::string encodedText;
    std::string encodedTree;

    getline(compressedFile, isAdaptive);
    getline(compressedFile, encodedTree);
    getline(compressedFile, encodedText);

    unsigned originalSize = originalText.length() * 8;
    unsigned encodedSize = encodedText.length() + (8 - (encodedText.length() % 8));
    unsigned encodedTreeSize = encodedTree.length() * 8;
    std::string encryptionMethod = (isAdaptive.compare("1") == 0) ? "Adaptive Huffman Encoding" : "Standard Huffman Encoding";

    std::cout << std::endl << "--- Compression info ---" << std::endl 
            << "Original file size in bits : " << originalSize << std::endl
            << "Compressed file size in bits : " << encodedSize << std::endl
            << "Encryption method : " << encryptionMethod << std::endl
            << "Encoded Tree Size : " << encodedTreeSize << std::endl
            << "Compression level : " << (double) encodedSize / (double) originalSize << std::endl << std::endl;
}

void Core::run()
{
    std::string input = "";
    getline(std::cin, input);

    while(input.compare("exit") != 0)
    {
        Command c(input);

        if(c.getMode().compare("compress") == 0)
            encodeTxtFileContent(c);
        else if (c.getMode().compare("decompress") == 0)
            decodeTxtFileContent(c);
        else if (c.isInfoMode())
            compressionLevel(c);

        input = "";
        getline(std::cin, input);
    }
}

#endif