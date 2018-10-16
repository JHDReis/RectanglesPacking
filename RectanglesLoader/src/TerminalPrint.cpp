//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#include <iostream>
#include "TerminalPrint.h"
#include "Rect.h"

void TerminalPrint::print() {

    std::cout<<"---- rectangles ("<< std::to_string(_rectangles.size()) <<") --------------"<<std::endl;


    while (true) {

    }

}

int TerminalPrint::get_left() {
    return 0;
}

int TerminalPrint::get_bottom() {
    return 0;
}

void TerminalPrint::load(const std::vector<Rect> &rectangles) {
    _rectangles = rectangles;
}
