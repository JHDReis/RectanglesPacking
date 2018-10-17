//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//

#include "RectanglesList.h"
#include "Rect.h"


RectanglesList::RectanglesList() {
    _max_y = 0;
    _max_x = 0;
}

void RectanglesList::load(std::vector<Rect> &rectangles) {
    _rectangles = rectangles;

    for(auto const& r : _rectangles){
        _max_x += r.width();
        _max_y += r.height();
    }
}

int RectanglesList::size() {
    return _rectangles.size();
}

int RectanglesList::max_width() {
    return _max_x;
}

int RectanglesList::max_height() {
    return _max_y;
}

std::vector<Rect> RectanglesList::get_list() {
    return _rectangles;
}




