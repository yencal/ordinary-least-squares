#include <stdio.h>
#include <process_cmd_args.h>
#include <setup_compute.h>


int main(int argc, char **argv)
{
    // read command line arguments
    Command cmd = process_cmd_args(argc, argv);

    // select either to run benchmark or normal computation
    if (cmd.benchmark)
    {

    }
    else
    {
        setup_compute(cmd);
    }
    
    return 0;
}