#include <stdio.h>

#include "read_input_files.h"


int main(int argc, char **argv)
{

    int n;
    int m;
    std::string XMAT_file;
    std::string yVEC_file;
    XMAT_file = "../test/XMAT.csv";
    yVEC_file = "../test/yVEC.csv";
    int numHeaderLines_XMAT_file = 1;
    int numHeaderLines_yVEC_file = 1;
    get_XMAT_dim(&n, &m, XMAT_file, numHeaderLines_XMAT_file);

    gsl_matrix * XMAT = gsl_matrix_alloc (n, m);
    gsl_vector * yVEC = gsl_vector_alloc (n);

    read_XMAT(n, m, XMAT_file, numHeaderLines_XMAT_file, XMAT);
    read_yVEC(n, yVEC_file, numHeaderLines_yVEC_file, yVEC);

    gsl_matrix_free (XMAT);
    gsl_vector_free (yVEC);
    
    return 0;
}