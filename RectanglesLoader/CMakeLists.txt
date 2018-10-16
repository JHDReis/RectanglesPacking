cmake_minimum_required(VERSION 3.12)
project(RectanglesLoader)

add_library(rectanglesLoader
        src/RectLoader.cpp
        src/RectLoader.h
        src/Rect.h
        src/Rect.cpp
        src/RectanglesList.cpp
        src/RectanglesList.h
        src/TerminalPrint.cpp
        src/TerminalPrint.h
        src/IPrint.h
        src/MaxRectsBinPack.h
        src/MaxRectsBinPack.cpp)
