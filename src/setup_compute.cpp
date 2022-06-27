#include <setup_compute.h>
#include <utilities.h>
#include <read_input_files.h>
#include <write_output.h>
#include <estimate_OLS.h>

void setup_compute(Command cmd)
{
    // XMAT (nxm), yVec(n), OLS(m)
    int n;
    int m;
    real_t * XMAT;
    real_t * yVEC;
    real_t *OLSest;

    // get dimension of XMAT
    read_csv_file_data_dim(&n, &m, cmd.XMAT_file, cmd.numHeaderLines_XMAT_file);

    // allocate memory for XMAT, yVEC, OLSest
    XMAT = new real_t [n*m];
    yVEC = new real_t[n];
    OLSest = new real_t[m];

    // read XMAT from file
    int numElements_XMAT;
    numElements_XMAT = read_csv_file<real_t> (cmd.XMAT_file, cmd.numHeaderLines_XMAT_file, XMAT);
    if (numElements_XMAT != (n*m))
    {
        throw std::runtime_error("XMAT number of elements read is not equal to number of elements expected");
    }

    // read yVEC from file
    int numElements_yVEC;
    numElements_yVEC = read_csv_file<real_t> (cmd.yVEC_file, cmd.numHeaderLines_yVEC_file, yVEC);
    if (numElements_yVEC != n)
    {
        throw std::runtime_error("yVEC number of elements read is not equal to number of elements expected");
    }

    // estimate OLS using the selected method in cmd.method
    estimate_OLS(n, m, XMAT, yVEC, OLSest, cmd.method);

    // write OLSest to file or screen
    if (cmd.writeFile) {
        std::ofstream file("OLSest.csv");
        write_data_as_csv(file, m, 1, OLSest);
    }
    else
    {
        write_data_as_csv(std::cout, m, 1, OLSest);
    }

    // free allocated memory
    delete [] XMAT;
    delete [] yVEC;
    delete [] OLSest;
}