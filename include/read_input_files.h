#pragma once

#include <iostream>
#include <stdio.h>

#include <fstream>
#include <limits>
#include <sstream>

#include "utilities.h"

void read_csv_file_data_dim(int* numRows, int* numCols, std::string fileName, int numHeaderLines);

template<typename T>
int read_csv_file(std::string fileName, int numHeaderLines, T* ptr);

template<typename T>
int read_csv_file(std::string fileName, int numHeaderLines, T* ptr)
{
    // create an input filestream and open XMAT_file
    std::ifstream myFile(fileName);

    // string for reading lines in file
    std::string line;

    // make sure file is open
    if (!myFile.is_open())
    {
        std::string errorMessage =
            std::string("Could not open ") + fileName + std::string(". Please specify file full path.");
        throw std::runtime_error(errorMessage);
    }

    // skip header lines
    int count = 0;
    while (count < numHeaderLines)
    {
        myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++count;
    }

    // write elements to XMAT using the pointer to its memory location
    T value;
    int i = 0;
    while (std::getline(myFile, line) && !line.empty())
    {
        // create a stringstream of the current line
        std::stringstream ss(line);

        // read columns in line
        while (ss >> value)
        {
            ptr[i] = value;
            i++;

            // if the next token is a comma, ignore it and move on
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }

    // close file
    myFile.close();

    return i;  // Note i == number of elements read
}