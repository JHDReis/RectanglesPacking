#include <utility>

//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#ifndef RECTANGULESPACKING_TERMINALPRINT_H
#define RECTANGULESPACKING_TERMINALPRINT_H

#include <vector>
#include "IPrint.h"

class Rect;
class TerminalPrint : public IPrint {
public:
    TerminalPrint()= default;
    explicit TerminalPrint(const std::vector<Rect> rectangles) : _rectangles(rectangles){}

    void load(const std::vector<Rect>& rectangles) override;
    void print() override;
    int get_left() override;
    int get_bottom() override;
private:
    std::vector<Rect> _rectangles;
};


#endif //RECTANGULESPACKING_TERMINALPRINT_H
