//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//

#ifndef RECTANGLESPACKING_RECT_H
#define RECTANGLESPACKING_RECT_H

struct RectSize
{
    int width;
    int height;
};

class Rect {
public:
    Rect();
    Rect(int width, int height);
    Rect(int width, int height, int x, int y);
    ~Rect() = default;

    //copy assigment
    Rect& operator=(const Rect& other);

    //getters
    int width() const {return _width;}
    int height() const {return _height;}
    int x() const {return _x;}
    int y() const {return _y;}
    int x_right() const;
    int y_bottom() const;

    //setters
    void set_width(int width) {_width = width;}
    void set_height(int height) {_height = height;}
    void set_x(int x) {_x = x;}
    void set_y(int y) {_y = y;}

    void set_dimension(int width, int height);
    void set_position(int x, int y);
    void reset(int width, int height, int x, int y);

    //stats
    bool rotate();
    bool is_rotaded() {return _rotaded;}
    bool overlaps(const Rect& b) const;
    bool is_contained(const Rect& b) const;

private:
    int _x;
    int _y;
    int _height;
    int _width;
    bool _rotaded;
};

bool overlaps(const Rect& a, const Rect& b);
bool is_contained(const Rect& a, const Rect& b);

#endif //RECTANGULESPACKING_RECT_H
