cmake_minimum_required(VERSION 3.10)

project(booker)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set the output directories for binaries and libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Include the headers
include_directories("${PROJECT_SOURCE_DIR}/include")

# Collect source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Define the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Define the resource library
add_library(ResourceLib src/resource.cpp)

# Define the test executable
add_executable(TestResource tests/test_resource.cpp)

# Link the test executable with the library
target_link_libraries(TestResource ResourceLib)

# Enable testing
enable_testing()

# Register the test
add_test(NAME TestResource COMMAND $<TARGET_FILE:TestResource>)

# Install rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
