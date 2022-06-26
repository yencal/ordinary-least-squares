#include <stdio.h>

#include <utilities.h>
#include <read_input_files.h>
#include <write_output.h>
#include <estimate_OLS.h>

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

    // allocate memory
    real_t * XMAT = new real_t [n*m];
    real_t * yVEC = new real_t[n];

    // allocate memory for OLSest (result)
    real_t *OLSest = new real_t[m];

    // read XMAT and yVEC from file
    read_XMAT(n, m, XMAT_file, numHeaderLines_XMAT_file, XMAT);
    read_yVEC(n, yVEC_file, numHeaderLines_yVEC_file, yVEC);

    //write_data_to_screen<real_t> (yVEC, 4);

    estimate_OLS(n, m, XMAT, yVEC, OLSest, 1);

    // free allocated memory
    delete [] XMAT;
    delete [] yVEC;
    delete [] OLSest;
    
    return 0;
}