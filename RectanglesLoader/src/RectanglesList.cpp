//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//

#include "RectanglesList.h"
#include "Rect.h"
#include <numeric>
#include <algorithm>

int max_width(const std::vector<Rect> &rectangles) {
    return std::accumulate(rectangles.begin(), rectangles.end(), 0,
                            [](int a, Rect b)
                            {
                                a += b.width();
                                return a;
                            });
}

int max_height(const std::vector<Rect> &rectangles) {
    return std::accumulate(rectangles.begin(), rectangles.end(), 0,
                            [](int a, Rect b)
                            {
                                a += b.height();
                                return a;
                            });
}

int max_right(const std::vector<Rect> &rectangles) {
    auto result =  std::max_element(rectangles.begin(), rectangles.end()
                         , [](const Rect& a, const Rect& b)
                         {
                             return a.x_right() < b.x_right();
                         } );
    return result->x_right();
}

int max_bottom(const std::vector<Rect> &rectangles) {
    auto result =  std::max_element(rectangles.begin(), rectangles.end()
                                    , [](const Rect& a, const Rect& b)
                                    {
                                        return a.y_bottom() < b.y_bottom();
                                    } );
    return result->y_bottom();
}

int area(const std::vector<Rect> &rectangles) {
    return ( max_bottom(rectangles) * max_right(rectangles));
}


void sort_area_dec(std::vector<Rect> &rectangles) {
    std::sort(rectangles.begin(), rectangles.end(),
                            [](Rect const& a, Rect const& b)
                            {
                                return b.area() < a.area();
                            });
}


