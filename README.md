# ordinary-least-squares

## Description
Calculate ordinary least squares(OLS) estimates using the Normal Equation(NE):

## Project design
The design process of the project is as follows:
* Method 1: computes the OLS directly by using the Normal Equation.
* Method 2: computes the OLS by first rearanging the Normal Equation as follows:
Then solve the system of linear equations(Ax = b) using the LU factorization method.
* The project uses CBLAS and LAPACKE for the linear algebra operations. This enables easy linkage of the project with more optimized and parallel versions of these libraries like the Intel Math Kernal Library. 
* CMake build system was used.

## Dependencies
The project uses CBLAS and LAPACKE for the linear algebra libraries. The liberaries can be installed using the following command:
```
sudo apt install libopenblas-dev
sudo apt-get install liblapacke-dev
```

## Basic build and usage
After cloning the project use the following commands to build it.
```
cd ordinary-least-squares
mkdir build
cmake -S . -B build
cmake --build build
```
This builds the executable `estOLS` in `/build/ordinary-least-squares`

The program accepts command line arguments which can be probed using the following command:
```
estOLS --help
```
The above command shows the following output:
```
  Arguments are:
    long      short  arg        description
  --Xmat        -x    1    X matrix csv file (full path)
  --yVec        -y    1    y Vector csv file (full path)
  --XmatSkip    -s    1    number of header lines to skip in Xmat file (default 0)
  --yVecSkip    -k    1    number of header lines to skip in yVec file (default 0)
  --method      -m    1    select which method to use 0, 1 (default 1, see below for more info)
  --writeFile   -w    0    output result to file (default writes result to screen)
  --benchmark   -b    1    run benchmark for Xmat dimensions in file
  --help        -h    0    print this message
  More info:    method 0: compute OLS estimates using direct evaluation of the normal equation
    method 1: compute OLS estimates using using LU factorization to solve Ax=b
    Note: options with arg=1 require values.
```

If X matrix and y vector are stored in a csv file named XMAT and yVEC with no header lines, the program can be run with the following minimal commands:
```
estOLS -x $path_to_file/XMAT.csv -y $path_to_file/yVEC.csv
```

Example of XMAT.csv and yVEC.csv are included in the test folder. To run the program with those files, you would need to specify the number of header lines in each file using the `-s` and `-k` options for the XMAT.csv and yVEC.csv files, respectively. To specify that the program writes the result to an output file (OLSest.csv) use the -w flag. Below is the full command:
```
estOLS -x $path_to_file/XMAT.csv -y $path_to_file/yVEC.csv -s 1 -k 1 -w
```

## Benchmark
The two methods for calculating the OLS estimates were benchmarked for X matrix of fixed n dimension (40000) and the m dimension in values [500,1000,2000,4000,10000]. The benchmark was ran three times and the results was averaged and ploted in the figure below. From the figure, it can be observed that the AxLU method outperforms the NE method. For a X matrix dimension of 40000x10000, the AxLU method is 3.4 times faster than the NE method. The difference in performance can be attributed to the reduced number of operations in the AxLU method compared to the NE method. The bechmark was run on a laptop powered the intel core i5 8th Gen processor.

![benchmark result plot](https://github.com/yencal/ordinary-least-squares/tree/main/benchmark/benchmark_plot.png)

The benchmark option for the program accepts a csv file that lists all the n and m dimensions of the X matrix that should be benchmarked. An example of the benchmark file is shown in `benchmark/benchmark.csv`. The file can be modified to run different X matrix dimensions. The command to run the benchmark study is shown below:
```
estOLS -b $path_to_file/benchmark.csv
```

## Future work
Future work would look at implementing an iterative method such as the conjugate gradient method to solve linear systems of equations (Ax = b).