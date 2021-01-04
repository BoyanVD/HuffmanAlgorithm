#include <iostream>
#include "HuffmanTree.h"
#include "AdaptiveHuffmanTree.h"

// #include <unordered_map>

int main()
{
// ------------------------------------------------------------------------------------------------------- CASE 1 -------------------------------
    // HuffmanTree tree("Това е новосъздаден форум, в който можете да задавате вашите въпроси относно проектите. Можете да ги задавате и в Дискорд, но препоръчваме да го правите във форума, за да има по-добра структура на дискусията по отделните проекти.");

    // std::string encoded = tree.encodeText("Това е новосъздаден форум, в който можете да задавате вашите въпроси относно проектите. Можете да ги задавате и в Дискорд, но препоръчваме да го правите във форума, за да има по-добра структура на дискусията по отделните проекти.");
    // std::cout << encoded << std::endl;

    // std::string code = tree.encodeTree();
    // std::cout << code << std::endl;

    // HuffmanTree decodedTree;
    // decodedTree.decodeTree(code);
    // std::unordered_map<char, std::string> tableDecoded = decodedTree.getEncodingTable();
    
    // std::string decoded = decodedTree.decodeText(encoded);
    // std::cout << decoded << std::endl;
// ------------------------------------------------------------------------------------------------------- CASE 1 -------------------------------



// ------------------------------------------------------------------------------------------------------- CASE 2 -------------------------------
    // HuffmanTree huffman("ABRACADABRA");
    // huffman.print();
    // std::cout << std::endl;

    // AdaptiveHuffmanTree adaptive;
    // adaptive.readNextSymbol('A');
    // adaptive.readNextSymbol('B');
    // adaptive.readNextSymbol('R');
    // adaptive.readNextSymbol('A');
    // adaptive.readNextSymbol('C');
    // adaptive.readNextSymbol('A');
    // adaptive.readNextSymbol('D');
    // adaptive.readNextSymbol('A');
    // adaptive.readNextSymbol('B');
    // adaptive.readNextSymbol('R');
    // adaptive.readNextSymbol('A');
    // adaptive.print();
    // std::cout << std::endl;
// ------------------------------------------------------------------------------------------------------- CASE 2 -------------------------------

// ------------------------------------------------------------------------------------------------------- CASE 3 -------------------------------

    AdaptiveHuffmanTree adaptive;
    adaptive.readNextSymbol('B');
    adaptive.readNextSymbol('O');
    adaptive.readNextSymbol('O');
    adaptive.readNextSymbol('K');
    adaptive.readNextSymbol('K');
    adaptive.readNextSymbol('E');
    adaptive.readNextSymbol('E');
    adaptive.readNextSymbol('P');
    adaptive.readNextSymbol('E');
    adaptive.readNextSymbol('R');
    adaptive.print();
    std::cout << std::endl;
    std::string encodedTree = adaptive.encode();
    std::cout << encodedTree << std::endl;

    AdaptiveHuffmanTree adaptiveToDecode;
    adaptiveToDecode.decode(encodedTree);
    adaptiveToDecode.print();
// ------------------------------------------------------------------------------------------------------- CASE 3 -------------------------------

// ------------------------------------------------------------------------------------------------------- CASE 4 -------------------------------
    // HuffmanTree tree("ABRACADABRA");

    // std::string encoded = tree.encodeText("ABRACADABRA");
    // std::cout << encoded << std::endl;

    // std::string code = tree.encodeTree();
    // std::cout << code << std::endl;
    // tree.print();

    // HuffmanTree decodedTree;
    // decodedTree.decodeTree(code);
    // std::unordered_map<char, std::string> tableDecoded = decodedTree.getEncodingTable();
    
    // std::string decoded = decodedTree.decodeText(encoded);
    // std::cout << decoded << std::endl;
// ------------------------------------------------------------------------------------------------------- CASE 4 -------------------------------

    return 0;
}