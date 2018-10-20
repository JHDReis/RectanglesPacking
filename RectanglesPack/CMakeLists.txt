cmake_minimum_required(VERSION 3.12)
project(RectanglesPack)


include_directories(src RectanglesBinPack rectpack2D)

add_library(rectanglesPack_lib
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
            src/rectpack2D/best_bin_finder.h
            src/rectpack2D/empty_space_allocators.h
            src/rectpack2D/empty_spaces.h
            src/rectpack2D/finders_interface.h
            src/rectpack2D/insert_and_split.h
            src/rectpack2D/rect_structs.h
            )
