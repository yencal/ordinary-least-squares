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

void read_XMAT(int n, int m, std::string XMAT_file, int numHeaderLines, real_t *XMAT_ptr)
{
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

    // write elements to XMAT using the pointer to its memory location
    real_t value;
    int numElements = 0;
    int i = 0;
    while (std::getline(myFile, line))
    {
        // skip empty lines (if any exits)
        if (line.empty())
        {
           continue;
        }

        // create a stringstream of the current line
        std::stringstream ss(line);
        
        // read columns in line
        while(ss >> value)
        {
            XMAT_ptr[i] = value;
            i++;
            numElements++;

            // if the next token is a comma, ignore it and move on
            if(ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }

    // check that numElements == (n*m)
    if (numElements != (n*m))
    {
        throw std::runtime_error("XMAT number of elements read is not equal to number of elements expected");
    }

     myFile.close();
}

void read_yVEC(int n, std::string yVEC_file, int numHeaderLines, real_t *yVEC_ptr)
{
    // create an input filestream and open XMAT_file
    std::ifstream myFile(yVEC_file);

    // string for reading lines in file
    std::string line;

    // make sure file is open
    if (!myFile.is_open())
    {
        throw std::runtime_error("Could not open yVEC.csv. Please specify file full path.");
    }

    // skip header lines
    int count = 0;
    while (count < numHeaderLines)
    {
        myFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++count;
    }

    // write elements to yVEC using the pointer to its memory location
    real_t value;
    int numElements = 0;
    int i = 0;
    while (std::getline(myFile, line))
    {
        // skip empty lines (if any exits)
        if (line.empty())
        {
           continue;
        }

        // create a stringstream of the current line
        std::stringstream ss(line);

        // read columns in line
        while(ss >> value)
        {
            yVEC_ptr[i] = value;
            i++;
            numElements++;
        }
    }

    // check that numElements == n
    if (numElements != n)
    {
        throw std::runtime_error("yVEC number of elements read is not equal to number of elements expected");
    }

     myFile.close();
}