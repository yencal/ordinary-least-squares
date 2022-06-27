#pragma once

#include <iostream>
#include <string>

// command line options
struct Command
{
    std::string XMAT_file;
    std::string yVEC_file;
    int numHeaderLines_XMAT_file = 0;
    int numHeaderLines_yVEC_file = 0;
    int method = 0;
    bool writeFile = false;
    std::string benchmarkFile;

    void print()
    {
        std::cout 
            << "The program is running with the following commands:\n"
            << "  Xmat: " << XMAT_file << "\n"
            << "  yVec: " << yVEC_file << "\n"
            << "  XmatSkip: " << numHeaderLines_XMAT_file << "\n"
            << "  yVecSkip: " << numHeaderLines_yVEC_file << "\n" 
            << "  method: " << method << "\n"
            << "  writeFile: " << (writeFile ? "true" : "false") << "\n"
            << "  benchmark: " << benchmarkFile << "\n";
    }
};