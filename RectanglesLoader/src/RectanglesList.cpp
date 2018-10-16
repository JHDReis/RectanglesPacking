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
    _rectangles = std::move(rectangles);

    for(auto const& r : _rectangles){
        _max_x += r.width();
        _max_y += r.height();
    }
}

unsigned long RectanglesList::size() {
    return _rectangles.size();
}

unsigned long RectanglesList::max_width() {
    return _max_x;
}

unsigned long RectanglesList::max_height() {
    return _max_y;
}




