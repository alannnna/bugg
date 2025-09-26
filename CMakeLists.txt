cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(bugg VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bugg main.cpp)

# Set output directory
set_target_properties(bugg PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_subdirectory(programs)