#include <stdio.h>
#include <process_cmd_args.h>
#include <setup_compute.h>
#include <benchmark.h>


int main(int argc, char **argv)
{
    // read command line arguments
    Command cmd = process_cmd_args(argc, argv);

    // print commands the program will run with
    cmd.print();

    // select either to run benchmark or normal computation
    if (cmd.benchmarkFile.length())
    {
        benchmark(cmd);
    }
    else
    {
        setup_compute(cmd);
    }
    
    return 0;
}