cmake_minimum_required(VERSION 3.10)

# Get all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Create an executable for each source file
foreach(SOURCE ${SOURCES})
    # Get the filename without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    
    # Create executable
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
    
    # Set output directory
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/programs
    )
endforeach()
