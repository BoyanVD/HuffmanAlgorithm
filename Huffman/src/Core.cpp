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
 * МНОГО ВАЖНООООООООООООООО !
 * ОБЕДИНИ ПЪРВИТЕ ДВА МЕТОДИТЕ ЗА КОДИРАНЕ И ДЕКОДИРАНЕ КАТО ОТ ФАЙЛА РАЗБЕРЕШ ДАЛИ Е АДАПТИВНО ИЛИ НЕ !!!!!!!!!!!!!!!!!!!!!!!!!!!
 */


/**
 * Encoding in the following format :
 * <bool adaptive><std::string three><code>
 */
void Core::encodeTxtFileContent(std::ostream& output, std::istream& input) // Think of command parameter
{
    std::stringstream stream;
    stream << input.rdbuf();
    std::string content = stream.str();

    // std::cout << content << "\n";
    HuffmanTree tree(content);
    std::string encodedText = tree.encodeText(content);
    std::string encodedTree = tree.encodeTree();

    output << 0 << std::endl;
    output << encodedTree << std::endl;
    output << encodedText;
}

/**
 * 
 */
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

void Core::decodeTxtFileContent(std::ostream& output, std::istream& input)
{
    std::string isAdaptive;
    std::string encodedText;
    std::string encodedTree;

    getline(input, isAdaptive);
    getline(input, encodedTree);
    getline(input, encodedText);

    HuffmanTree decodedTree;
    decodedTree.decodeTree(encodedTree);
    std::string decodedText = decodedTree.decodeText(encodedText);

    output << decodedText;
}

void Core::decodeTxtFileContentAdaptive(std::ostream& output, std::istream& input)
{
    std::string isAdaptive;
    std::string encodedText;
    std::string encodedTree;

    getline(input, isAdaptive);
    getline(input, encodedTree);
    getline(input, encodedText);

    AdaptiveHuffmanTree decodedTree;
    decodedTree.decodeTree(encodedTree);
    std::string decodedText = decodedTree.decodeText(encodedText);

    output << decodedText;
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

void Core::run()
{
    // std::ifstream inFile;
    // inFile.open("../files/demoInput.txt"); //open the input file
    // std::ofstream outFile("../files/demoOutput.txt");
    // Core::encodeTxtFileContent(outFile, inFile);

    // std::ifstream in;
    // in.open("../files/demoOutput.txt");
    // std::ofstream out("../files/shit.txt");
    // Core::decodeTxtFileContent(out, in);

    // std::ifstream inDebug;
    // inDebug.open("../files/demoInput.txt");
    // Core::debugMode(inDebug);

    // -----------------------------------Adaptive tests---------------------------------
    // std::ifstream inFile;
    // inFile.open("../files/demoInput.txt"); //open the input file
    // std::ofstream outFile("../files/demoOutput.txt");
    // Core::encodeTxtFileContentAdaptive(outFile, inFile);

    // std::ifstream in;
    // in.open("../files/demoOutput.txt");
    // std::ofstream out("../files/shit.txt");
    // Core::decodeTxtFileContentAdaptive(out, in);
}

#endif