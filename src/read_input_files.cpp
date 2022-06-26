#include "read_input_files.h"
#include "utilities.h"

void get_XMAT_dim(int *n, int *m, std::string XMAT_file, int numHeaderLines)
{
    // initialize to zero
    (*n) = 0;
    (*m) = 0;

    // create an input filestream and open XMAT_file
    std::ifstream myFile(XMAT_file);

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

    // read first line and get number of columns (dim m)
    while (std::getline(myFile, line))
    {
        if (line.empty()) {
            continue;
        } else {
            ++(*n);
            break;
        }
    }

    // create a stringstream from line
    std::stringstream ss(line);

    // count number of columns
    while (std::getline(ss, line, ','))
    {
        ++(*m);
    }

    // count the number of lines in file
    while (std::getline(myFile, line))
    {
        // skip empty lines (if any exits)
        if (line.empty())
        {
           continue;
        }
        ++(*n);
    }
        
    //printf("XMAT dimension: %d x %d\n", (*n), (*m));

    myFile.close();
}