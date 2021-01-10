#include <iostream>
#include "Core.h"

int main()
{
    /**
     * 1. Encryption and decryption demo :
     * -c -i demo/original.txt -o demo/standard_e.txt
     * -d -i demo/standard_e.txt -o demo/standard_d.txt
     * -c -i demo/original.txt -o demo/adaptive_e.txt -adaptive
     * -d -i demo/adaptive_e.txt -o demo/adaptive_d.txt
     * exit
     */
    
    Core::run();

    return 0;
}