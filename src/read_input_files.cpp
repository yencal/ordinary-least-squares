#include "read_input_files.h"
#include "utilities.h"

void read_csv_file_data_dim(int *numRows, int *numCols, std::string fileName, int numHeaderLines)
{
    // initialize to zero
    (*numRows) = 0;
    (*numCols) = 0;

    // create an input filestream and open XMAT_file
    std::ifstream myFile(fileName);

    // string for reading lines in file
    std::string line;

    // make sure file is open
    if (!myFile.is_open())
    {
        throw std::runtime_error("Could not open XMAT.csv. Please specify file full path.");
    }

    // skip header lines
    int count = 0;
    while (count < numHeaderLines)
    {
        myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++count;
    }

    // read first line to get number of columns
    std::getline(myFile, line);
    ++(*numRows); // increament number of rows after line read

    // create a stringstream from line
    std::stringstream ss(line);

    // count number of columns
    while (std::getline(ss, line, ','))
    {
        ++(*numCols);
    }

    // continue counting the number of lines in file
    while (std::getline(myFile, line) && !line.empty())
    {
        // increament number of rows
        ++(*numRows);
    }

    myFile.close();
}