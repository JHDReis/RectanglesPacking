

//
// Created by Joao Henriques David Dos Reis on 15/10/2018.
//

#ifndef RECTANGULESPACKING_TERMINALPRINT_H
#define RECTANGULESPACKING_TERMINALPRINT_H

#include <vector>
#include <string>
#include "IPrint.h"

class Rect;
class TerminalPrint : public IPrint {
public:
    TerminalPrint() = default;
    ~TerminalPrint() = default;
    explicit TerminalPrint(const std::vector<Rect> rectangles) : _rectangles(rectangles){}
    void load(const std::vector<Rect>& rectangles) override;
    void print() override;
private:
    std::vector<Rect> _rectangles;
};


#endif //RECTANGULESPACKING_TERMINALPRINT_H
