//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#ifndef RECTANGULESPACKING_IPRINT_H
#define RECTANGULESPACKING_IPRINT_H

class Rect;
class IPrint {
public:
    ~IPrint() = default;
    virtual void load(const std::vector<Rect>& rectangles)=0;
    virtual void print() = 0;
};

#endif //RECTANGULESPACKING_IPRINT_H
