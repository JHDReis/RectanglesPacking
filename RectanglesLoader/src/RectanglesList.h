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
    int size();
    int max_width();
    int max_height();

    std::vector<Rect> get_list();

private:
    std::vector<Rect> _rectangles;
    int _max_x;
    int _max_y;
};


#endif //RECTANGULESPACKING_RECTANGLESLIST_H
