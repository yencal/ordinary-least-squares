set(Executable_Name estOLS)

set(Sources
    main.cpp
    estimate_OLS.cpp
    read_input_files.cpp
    write_output.cpp
    setup_compute.cpp
    command.cpp
    process_cmd_args.cpp
    benchmark.cpp
)

include_directories(${${Project_Name}_SOURCE_DIR}/include)
add_executable(${Executable_Name} ${Sources})

set(BLA_VENDOR Generic) # set BLAS/LAPACK Vendors
find_package(LAPACK REQUIRED)
#message(STATUS "LAPACK_LIBRARIES: ${LAPACK_LIBRARIES}")

target_link_libraries(${Executable_Name} -llapacke ${LAPACK_LIBRARIES})