//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//

#ifndef RECTANGULESPACKING_RECTANGLESLIST_H
#define RECTANGULESPACKING_RECTANGLESLIST_H


#include <vector>

class Rect;
class RectanglesList{

public:
    RectanglesList();
    void load(std::vector<Rect>& rectangles);
    unsigned long size();
    unsigned long max_width();
    unsigned long max_height();

private:
    std::vector<Rect> _rectangles;
    unsigned long _max_x;
    unsigned long _max_y;
};


#endif //RECTANGULESPACKING_RECTANGLESLIST_H
