#pragma once

#include <utilities.h>
#include <iostream>

template <typename T>
void write_data_to_screen(T *ptr, int size);

void write_estOLS_to_file(int m, real_t *OLSest);


template <typename T>
void write_data_to_screen(T *ptr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << ptr[i] << std::endl;
    }
}