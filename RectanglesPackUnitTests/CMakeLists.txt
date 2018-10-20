cmake_minimum_required(VERSION 3.12)
project(RectanglesPackUnitTests)

#including the source files from library to be tested
include_directories(${RECT_LOADER_SRC})

#Google Test setting
set(GTEST_SRC lib/googletest)
set(GTEST_INC lib/googletest/include)
set(GTEST_LIB lib)

add_subdirectory(${GTEST_LIB})

include_directories(${GTEST_SRC} ${GTEST_INC})

add_executable(run_tests basic_check.cpp
                        RectTest.cpp
                        RectLoaderTest.cpp
                        TerminalPrintTest.cpp
                        RectanglesListTest.cpp)

target_link_libraries(run_tests gtest gtest_main)
target_link_libraries(run_tests rectanglesPack_lib)
