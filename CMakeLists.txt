cmake_minimum_required(VERSION 3.10)
project(Periscope_Project C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

enable_testing()

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
