//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//

#ifndef RECTANGULESPACKING_RECTANGLESLIST_H
#define RECTANGULESPACKING_RECTANGLESLIST_H

#include <vector>
class Rect;

int biggest_width(const std::vector<Rect> &rectangles);

int biggest_height(const std::vector<Rect> &rectangles);

int sum_width(const std::vector<Rect> &rectangles);

int sum_height(const std::vector<Rect> &rectangles);

int max_right(const std::vector<Rect> &rectangles);

int max_bottom(const std::vector<Rect> &rectangles);

int area(const std::vector<Rect> &rectangles);

void sort_area_dec(std::vector<Rect> &rectangles);


#endif //RECTANGULESPACKING_RECTANGLESLIST_H
