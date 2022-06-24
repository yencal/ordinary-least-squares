#include <stdio.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <limits>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

void get_XMAT_dim(int*, int*, std::string, int);
void read_XMAT(int, int, std::string, int, gsl_matrix*);
void read_yVEC(int, std::string, int, gsl_vector*);