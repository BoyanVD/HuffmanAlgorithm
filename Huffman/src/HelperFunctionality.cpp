#ifndef __HELPER_FUNCTIONALITY_CPP
#define __HELPER_FUNCTIONALITY_CPP

#include "HelperFunctionality.h"

unsigned readNextNumber(const std::string& str)
{
    unsigned res = 0;
    unsigned index = 0;

    while(str[index] >= '0' && str[index] <= '9' && index < str.length())
    {
        res += str[index] - '0';
        res *= 10;
        ++index;
    }
    res /= 10;

    return res;
}

unsigned numLength(unsigned num)
{
    unsigned counter = 0;
    while(num > 0)
    {
        ++counter;
        num /= 10;
    }

    return counter;
}

#endif