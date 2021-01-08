#ifndef __CORE_H
#define __CORE_H

#include <iostream>

class Core
{
private:
    static void encodeTxtFileContent(std::ostream& output, std::istream& input);
    static void encodeTxtFileContentAdaptive(std::ostream& output, std::istream& input);

    static void decodeTxtFileContent(std::ostream& output, std::istream& input);
    static void decodeTxtFileContentAdaptive(std::ostream& output, std::istream& input);

    static void debugMode(std::istream& input);

    static unsigned binaryStringToNum(const std::string& str);
public:
    static void run();
};

#endif