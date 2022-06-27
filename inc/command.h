#pragma once

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
    bool benchmark = false;
};