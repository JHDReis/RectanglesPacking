//
// Created by Joao Henriques David Dos Reis on 14/10/2018.
//


#include "Rect.h"
Rect::Rect() : _width(0), _height(0), _x(0), _y(0), _rotaded(false){

}

Rect::Rect(int width, int height) :  _width(width), _height(height), _x(0), _y(0), _rotaded(false){}

Rect::Rect(int width, int height, int x, int y) :  _width(width), _height(height), _x(x), _y(y), _rotaded(false) {}

Rect &Rect::operator=(const Rect& other) {
    // check for self-assignment
    if(&other == this) return *this;
    _width = other.width();
    _height = other.height();
    _x = other.x();
    _y = other.y();
    return *this;
}


//getters
int Rect::x_right() const {
    return _x + _width;
}


int Rect::y_bottom() const {
    return _y + _height;
}


int Rect::area() const {
    return _height * _width;
}

//setters
void Rect::set_dimension(int width, int height) {
    _width = width;
    _height = height;
}


void Rect::set_position(int x, int y) {
    _x = x; _y = y;
}


void Rect::reset(int width, int height, int x, int y) {
    _width = width;
    _height = height;
    set_position(x, y);
}


//stats
bool Rect::rotate() {
    _rotaded = !_rotaded;
    return _rotaded;
}


bool Rect::overlaps(const Rect& b) const {

    // If one rectangle is on left side of other
    if( _x >= b.x_right() || b.x() >= x_right())
        return false;
    //If one rectangle is on the above the other
    return !(y_bottom() <= b.y() || b.y_bottom() <= _y);
}


bool Rect::is_contained(const Rect& b) const {
    return _x >= b.x() && _y >= b.y()
            && x_right() <= b.x_right() && y_bottom() <= b.y_bottom();
}


bool overlaps(const Rect& a, const Rect& b){
    return a.overlaps(b);
}


bool is_contained(const Rect& a, const Rect& b) {
    return a.is_contained(b);
}

