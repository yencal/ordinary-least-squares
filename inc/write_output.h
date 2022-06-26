#pragma once

#include <utilities.h>
#include <iostream>


template <typename T>
void write_data_as_csv(std::ostream &output_stream, int numRows, int numCols, T *ptr);

template <typename T>
void write_data_as_csv(std::ostream &output_stream, int numRows, int numCols, T *ptr)
{

    int count = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            output_stream << ptr[count];

            // avoid comma at end of line 
            if(j != numCols - 1)
            {
                output_stream << ",";
            } 

            count++;
        } // end for j

        output_stream << "\n";

    } // end for i

}