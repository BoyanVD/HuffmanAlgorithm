#ifndef __CORE_H
#define __CORE_H

#include <iostream>
#include "Command.h"

class Core
{
private:
    static void encodeTxtFileContent(const Command& c);
    static void encodeTxtFileContentStandard(std::ostream& output, std::istream& input);
    static void encodeTxtFileContentAdaptive(std::ostream& output, std::istream& input);

    static void decodeTxtFileContent(const Command& c);
    static std::string decodeTxtFileContentStandard(const std::string& encodedText, const std::string& encodedTree);
    static std::string decodeTxtFileContentAdaptive(const std::string& encodedText, const std::string& encodedTree);

    static void compressionLevel(const Command& c);

    static void debugMode(std::istream& input);

    static unsigned binaryStringToNum(const std::string& str);
public:
    static void run();
};

#endif