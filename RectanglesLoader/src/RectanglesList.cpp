//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//

#include "RectanglesList.h"
#include "Rect.h"
#include <numeric>
#include <algorithm>
#include <iterator>
#include <random>

int biggest_width(const std::vector<Rect> &rectangles) {
     auto f = std::max_element(rectangles.begin(), rectangles.end(),
                     [](Rect a, Rect b)
                    {
                        return a.width() < b.width();
                    });
    return f->width();
}


int biggest_height(const std::vector<Rect> &rectangles) {
    auto f = std::max_element(rectangles.begin(), rectangles.end(),
                              [](Rect a, Rect b)
                              {
                                  return a.height() < b.height();
                              });
    return f->height();
}

int sum_width(const std::vector<Rect> &rectangles) {
    return std::accumulate(rectangles.begin(), rectangles.end(), 0,
                            [](int a, Rect b)
                            {
                                a += b.width();
                                return a;
                            });
}

int sum_height(const std::vector<Rect> &rectangles) {
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

void shuffle_vector(std::vector<Rect> &rectangles) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(rectangles.begin(), rectangles.end(), g);
}

int square_side(const std::vector<Rect> &rectangles) {
    int right = max_right(rectangles);
    int bottom = max_bottom(rectangles);
    return right > bottom? right : bottom;
}




