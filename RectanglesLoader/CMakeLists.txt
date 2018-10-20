cmake_minimum_required(VERSION 3.12)
project(RectanglesLoader)

add_library(rectanglesLoader_lib
            src/RectLoader.cpp
            src/RectLoader.h
            src/Rect.h
            src/Rect.cpp
            src/RectanglesList.cpp
            src/RectanglesList.h
            src/BinPackHelper.h
            src/BinPackHelper.cpp
        src/print/TerminalPrint.cpp
        src/print/TerminalPrint.h
        src/print/IPrint.h
            src/RectangleBinPack/MaxRectsBinPack.h
            src/RectangleBinPack/MaxRectsBinPack.cpp
            )
