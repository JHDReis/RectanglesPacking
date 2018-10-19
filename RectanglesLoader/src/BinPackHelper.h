//
// Created by Joao Henriques David Dos Reis on 19/10/2018.
//

#ifndef RECTANGULESPACKING_BINPACKCALC_H
#define RECTANGULESPACKING_BINPACKCALC_H

#include <vector>
#include "RectangleBinPack/MaxRectsBinPack.h"
class Rect;

rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList
        , rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method
        , bool allow_flip = true);

rbp::MaxRectsBinPack get_minArea(std::vector<rbp::MaxRectsBinPack> &binPackList);

std::vector<rbp::MaxRectsBinPack> get_bins_minSide(std::vector<rbp::MaxRectsBinPack> &binPackList, int min_side);


class BinPackHelper {

};


#endif //RECTANGULESPACKING_BINPACKCALC_H
