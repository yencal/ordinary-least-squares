#pragma once

#include <command.h>
#include <iostream>

void print_help();
Command process_cmd_args(int argc, char** argv);