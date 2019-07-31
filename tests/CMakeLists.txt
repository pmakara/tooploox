cmake_minimum_required (VERSION 3.9)

file(GLOB TEST_FILES *.cpp)
add_executable(median_calc_test ${TEST_FILES})
target_link_libraries(median_calc_test median_calc_lib gtest gmock pthread)

