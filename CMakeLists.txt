cmake_minimum_required (VERSION 3.9)

project(TOOPLOOX_TASK)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(source)
add_subdirectory(tests)