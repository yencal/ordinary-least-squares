#include <getopt.h>
#include <process_cmd_args.h>

void print_help()
{
    std::cout << "  Arguments are:\n"
                 "    long      short  arg        description\n"
                 "  --Xmat        -x    1    X matrix csv file (full path)\n"
                 "  --yVec        -y    1    y Vector csv file (full path)\n"
                 "  --XmatSkip    -s    1    number of header lines to skip in Xmat file (default 0)\n"
                 "  --yVecSkip    -k    1    number of header lines to skip in yVec file (default 0)\n"
                 "  --method      -m    1    select which method to use 0, 1 (default 1, see below for more info)\n"
                 "  --writeFile   -w    0    output result to file (default writes result to screen)\n"
                 "  --benchmark   -b    1    run benchmark for Xmat dimensions in file\n"
                 "  --help        -h    0    print this message\n"
                 "  More info:"
                 "    method 0: compute OLS estimates using direct evaluation of the normal equation\n"
                 "    method 1: compute OLS estimates using using LU factorization to solve Ax=b\n"
                 "    Note: options with arg=1 require values.\n";
    exit(1);
}

Command process_cmd_args(int argc, char** argv)
{
    /*
        This function processes command line arguments.
    */
    // struct that holds all cmd args
    Command cmd;

    const char* const short_opts = "x:y:s:k:m:wb:h";
    const option long_opts[] = {{"Xmat", required_argument, nullptr, 'x'},
                                {"yVec", required_argument, nullptr, 'y'},
                                {"XmatSkip", required_argument, nullptr, 's'},
                                {"yVecSkip", required_argument, nullptr, 'i'},
                                {"method", required_argument, nullptr, 'm'},
                                {"writeFile", no_argument, nullptr, 'w'},
                                {"benchmark", required_argument, nullptr, 'b'},
                                {"help", no_argument, nullptr, 'h'},
                                {nullptr, no_argument, nullptr, 0}};

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 'x': cmd.XMAT_file = std::string(optarg); break;

        case 'y': cmd.yVEC_file = std::string(optarg); break;

        case 's': cmd.numHeaderLines_XMAT_file = std::stoi(optarg); break;

        case 'k': cmd.numHeaderLines_yVEC_file = std::stoi(optarg); break;

        case 'm': cmd.method = std::stoi(optarg); break;

        case 'w': cmd.writeFile = true; break;

        case 'b': cmd.benchmarkFile = std::string(optarg); break;

        case 'h':  // -h or --help
        case '?':  // Unrecognized option
        default: print_help(); break;
        }  // end switch
    }      // end while

    return cmd;
}