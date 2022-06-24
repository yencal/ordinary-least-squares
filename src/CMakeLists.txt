set(Executable_Name estOLS)

set(Sources
    read_input_files.cpp
    main.cpp
)

include_directories(${${Project_Name}_SOURCE_DIR}/inc)
add_executable(${Executable_Name} ${Sources})

find_package(GSL REQUIRED)
target_link_libraries(${Executable_Name} GSL::gsl GSL::gslcblas)