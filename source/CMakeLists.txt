cmake_minimum_required (VERSION 3.9)

file(GLOB SRC_FILES *.cpp)
list(REMOVE_ITEM SRC_FILES "main.cpp")
add_library(median_calc_lib STATIC ${SRC_FILES})
add_executable(median_calc main.cpp)
target_link_libraries(median_calc median_calc_lib)
