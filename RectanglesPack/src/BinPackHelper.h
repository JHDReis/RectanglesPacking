//
// Created by Joao Henriques David Dos Reis on 19/10/2018.
//

#ifndef RECTANGULESPACKING_BINPACKCALC_H
#define RECTANGULESPACKING_BINPACKCALC_H

#include <vector>
#include "RectangleBinPack/MaxRectsBinPack.h"

class Rect;
class BinPackHelper {
public:
    BinPackHelper(){};
    ~BinPackHelper();

    //this will add the result to the _binPackList, but at the same time return the best packed bin
    std::vector<Rect> get_bestBin(std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method,
                                  bool allow_flip);
    void add(const std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method, bool allow_flip);

    std::vector<rbp::MaxRectsBinPack> get_smallest_squares();
private:
    std::vector<rbp::MaxRectsBinPack> _binPackList;
};


rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList
        , rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method
        , bool allow_flip = true);
rbp::MaxRectsBinPack get_minArea(std::vector<rbp::MaxRectsBinPack> &binPackList);
std::vector<rbp::MaxRectsBinPack> get_bins_minSide(std::vector<rbp::MaxRectsBinPack> &binPackList, int min_side);

std::string heuristic_to_string(rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method);


#endif //RECTANGULESPACKING_BINPACKCALC_H
