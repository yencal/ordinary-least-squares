#pragma once

#include <stdio.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <limits>

#include "utilities.h"

void get_XMAT_dim(int*, int*, std::string, int);
void read_XMAT(int, int, std::string, int, real_t*);
void read_yVEC(int, std::string, int, real_t*);