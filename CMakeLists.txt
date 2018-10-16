cmake_minimum_required(VERSION 3.12)
project(RectangulesPacking)

set(CMAKE_CXX_STANDARD 17)

set(RECT_LOADER_SRC RectanglesLoader/src)


include_directories(${RECT_LOADER_SRC})

add_subdirectory(RectanglesLoader)
add_subdirectory(RectanglesLoaderTests)

add_executable(rectangules_run main.cpp)

#linking with the library
TARGET_LINK_LIBRARIES(rectangules_run rectanglesLoader)