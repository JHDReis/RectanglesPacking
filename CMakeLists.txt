cmake_minimum_required(VERSION 3.12)
project(RectangulesPacking)

set(CMAKE_CXX_STANDARD 17)
set(RECT_LOADER_SRC RectanglesPack/src)


include_directories(${RECT_LOADER_SRC})

add_subdirectory(RectanglesPack)
add_subdirectory(RectanglesPackUnitTests)

add_executable(rectangules_run main.cpp)

add_executable(maxrectsbin_run mainMaxBinPack.cpp)

#linking with the library
TARGET_LINK_LIBRARIES(rectangules_run rectanglesPack_lib)
TARGET_LINK_LIBRARIES(maxrectsbin_run rectanglesPack_lib)