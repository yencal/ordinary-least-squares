#include <stdio.h>

#include <utilities.h>
#include <read_input_files.h>
#include <write_output.h>
#include <estimate_OLS.h>

int main(int argc, char **argv)
{

    std::string XMAT_file;
    std::string yVEC_file;
    XMAT_file = "../test/XMAT.csv";
    yVEC_file = "../test/yVEC.csv";
    int numHeaderLines_XMAT_file = 1;
    int numHeaderLines_yVEC_file = 1;
    int method = 1;
    int benchmark = 0;

    // XMAT dimension (nxm)
    int n;
    int m;

    // get dimension of XMAT
    read_csv_file_data_dim(&n, &m, XMAT_file, numHeaderLines_XMAT_file);

    // allocate memory for XMAT, yVEC, OLSest
    real_t * XMAT = new real_t [n*m];
    real_t * yVEC = new real_t[n];
    real_t *OLSest = new real_t[m];

    // read XMAT from file
    int numElements_XMAT;
    numElements_XMAT = read_csv_file<real_t> (XMAT_file, numHeaderLines_XMAT_file, XMAT);
    if (numElements_XMAT != (n*m))
    {
        throw std::runtime_error("XMAT number of elements read is not equal to number of elements expected");
    }

    // read yVEC from file
    int numElements_yVEC;
    numElements_yVEC = read_csv_file<real_t> (yVEC_file, numHeaderLines_yVEC_file, yVEC);
    if (numElements_yVEC != n)
    {
        throw std::runtime_error("yVEC number of elements read is not equal to number of elements expected");
    }

    estimate_OLS(n, m, XMAT, yVEC, OLSest, method);
    //write_data_to_screen<real_t> (OLSest, m);

    std::ofstream file("output.txt");
    write_data_as_csv(file, m, 1, OLSest);

    // free allocated memory
    delete [] XMAT;
    delete [] yVEC;
    delete [] OLSest;
    
    return 0;
}