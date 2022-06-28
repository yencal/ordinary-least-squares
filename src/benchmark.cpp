#include <benchmark.h>
#include <chrono>
#include <command.h>
#include <estimate_OLS.h>
#include <read_input_files.h>
#include <utilities.h>

void benchmark(Command cmd)
{
    // print info
    std::cout << "\nRunning benchmark study for different dimensions(nxm) of XMAT. All times in seconds.\n"
              << "n: XMAT dim n\n"
              << "m: XMAT dim m\n"
              << "NE: Normal Equation\n"
              << "AxbLU : Solve Ax=b using LU factorization\n"
              << "\nn,m,NE,AxbLU\n";

    int numRows;
    int numCols;
    int numHeaderLines = 1;

    // get dimension of XMAT
    read_csv_file_data_dim(&numRows, &numCols, cmd.benchmarkFile, numHeaderLines);

    // read XMAT dims form benchmark.csv
    int* benchmark_XMAT_dims = new int[numRows * numCols];
    read_csv_file<int>(cmd.benchmarkFile, numHeaderLines, benchmark_XMAT_dims);

    // seperate out all n and m from benchmark_XMAT_dims
    int* dims_n = new int[numRows];
    int* dims_m = new int[numRows];
    for (int i = 0; i < numRows * numCols; i++)
    {
        if ((i + 1) % 2 == 1)  // if i+1 = odd
        {
            dims_n[i / 2] = benchmark_XMAT_dims[i];
        }
        else
        {
            dims_m[i / 2] = benchmark_XMAT_dims[i];
        }
    }

    // check dims_n and dims_m
    // printf("n,m\n");
    // for (int i = 0; i < numRows; i++)
    // {
    //     printf("%d,%d\n", dims_n[i], dims_m[i]);
    // }
    // exit(1);

    // XMAT (nxm), yVec(n), OLS(m)
    int n;
    int m;
    real_t* XMAT;
    real_t* yVEC;
    real_t* OLSest;

    // for timing
    Timer timer;

    // for storing time for method 0 and 1.
    // NE: Normal equation, AxbLU: solve Ax = b using LU factorization
    double* NE_times = new double[numRows];
    double* AxbLU_times = new double[numRows];

    // run all benchmark dims in benchmark.csv
    for (int i = 0; i < numRows; i++)
    {
        n = dims_n[i];
        m = dims_m[i];

        // allocate memory for XMAT, yVEC, OLSest
        XMAT = new real_t[n * m];
        yVEC = new real_t[n];
        OLSest = new real_t[m];

        // fill XMAT, yVEC with random numbers
        fill_with_rand(XMAT, n * m);
        fill_with_rand(yVEC, n);

        //  estimate OLS by evaluating the normal equation
        timer.reset();
        estimate_OLS(n, m, XMAT, yVEC, OLSest, 0);
        NE_times[i] = timer.stop();

        // estimate OLS using LU factorization to solve Ax=b
        timer.reset();
        estimate_OLS(n, m, XMAT, yVEC, OLSest, 1);
        AxbLU_times[i] = timer.stop();

        // print info
        printf("%d,%d,%8.4E,%8.4E\n", dims_n[i], dims_m[i], NE_times[i], AxbLU_times[i]);

        // free allocated memory
        delete[] XMAT;
        delete[] yVEC;
        delete[] OLSest;
    }

    // deallocate memory
    delete[] benchmark_XMAT_dims;
    delete[] NE_times;
    delete[] AxbLU_times;
}

void fill_with_rand(real_t* ptr, int size)
{
    /*
        fill array with random numbers (0,1]
    */

    real_t inv_rand_max = (real_t)1.0 / (real_t)RAND_MAX;
    for (int i = 0; i < size; i++)
    {
        ptr[i] = rand() * inv_rand_max;
    }
}

// Timer class definations
void Timer::reset()
{
    start_time_ = clock_t::now();
}

double Timer::stop()
{
    elapsed_time_ = clock_t::now() - start_time_;

    // calculate elapsed time in seconds
    elapsed_time_in_seconds_ = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time_).count() * 1.0e-9;

    return elapsed_time_in_seconds_;
}