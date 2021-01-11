#ifndef __COMMAND_CPP
#define __COMMAND_CPP

#include "Command.h"

Command::Command(const std::string& input)
{
    this->parseInput(input);
}

std::string Command::getPropertyFromInput(const std::string& input, const std::string& propertySignature)
{
    size_t index = input.find(propertySignature) + propertySignature.length();
    
    if(index == std::string::npos)
        return "";

    while(index < input.length() && input[index] == ' ')
    {
        ++index;
    }

    std::string result = "";

    while(index < input.length() && input[index] != ' ')
    {
        result += input[index];
        ++index;
    }
    
    return result;
}

void Command::parseInput(const std::string& input)
{
    if (input.find(COMPRESS_MODE_SIGNATURE) != std::string::npos)
    {
        this->mode = "compress";
    } else if (input.find(DECOMPRESS_MODE_SIGNATURE) != std::string::npos)
    {
        this->mode = "decompress";
    } else
    {
        this->mode = "";
    }

    this->inputFile = getPropertyFromInput(input, INPUT_FILE_SIGNATURE);
    this->outputFile = getPropertyFromInput(input, OUTPUT_FILE_SIGNATURE);
    this->isDebug = (input.find(DEBUG_MODE_SIGNATURE) != std::string::npos);
    this->isAdaptive = (input.find(ADAPTIVE_MODE_ENCODING_SIGNATURE) != std::string::npos);
    this->showInfo = (input.find(COMPRESSION_INFO_MODE_SIGNATURE) != std::string::npos);
}

std::string Command::getMode() const
{
    return this->mode;
}

std::string Command::getInputFile() const
{
    return this->inputFile;
}

std::string Command::getOutputFile() const
{
    return this->outputFile;
}

bool Command::isAdaptiveMode() const
{
    return this->isAdaptive;
}

bool Command::isInfoMode() const
{
    return this->showInfo;
}

void Command::printCommand()
{
    std::cout << "Mode :" << this->mode << std::endl
            << "Input File :" << this->inputFile << std::endl
            << "Output File :" << this->outputFile << std::endl
            << "Is debug mode :" << this->isDebug << std::endl;
            
}

#endif