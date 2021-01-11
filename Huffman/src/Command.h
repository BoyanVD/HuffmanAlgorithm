#ifndef __COMMAND_H
#define __COMMAND_H

#include <iostream>
#include <string>

const std::string COMPRESS_MODE_SIGNATURE = "-c";
const std::string DECOMPRESS_MODE_SIGNATURE = "-d";
const std::string INPUT_FILE_SIGNATURE = "-i";
const std::string OUTPUT_FILE_SIGNATURE = "-o";
const std::string DEBUG_MODE_SIGNATURE = "-debug";
const std::string ADAPTIVE_MODE_ENCODING_SIGNATURE = "-adaptive";
const std::string COMPRESSION_INFO_MODE_SIGNATURE = "-info";

class Command
{
private:
    std::string mode;
    std::string inputFile;
    std::string outputFile;
    bool isDebug;
    bool isAdaptive;
    bool showInfo;

    std::string getPropertyFromInput(const std::string& input, const std::string& propertySignature);
    void parseInput(const std::string& input);

public:
    Command(const std::string& input);
    std::string getMode() const;
    std::string getInputFile() const;
    std::string getOutputFile() const;
    bool isAdaptiveMode() const;
    bool isInfoMode() const;

    void printCommand();
};

#endif