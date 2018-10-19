//
// Created by Joao Henriques David Dos Reis on 19/10/2018.
//

#include <iostream>
#include "BinPackHelper.h"
#include "RectanglesList.h"


BinPackHelper::~BinPackHelper() {
    _binPackList.clear();
}

void BinPackHelper::add(const std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method,
                        bool allow_flip) {
    rbp::MaxRectsBinPack bin;
    int maxWidth = sum_width(rectList);
    int maxHeight = sum_height(rectList);

    if(maxHeight > maxWidth)
        maxWidth = maxHeight;
    else
        maxHeight = maxWidth;
    bin.Init(maxWidth, maxHeight, allow_flip);

    for(auto rect : rectList) {
        bin.Insert(rect.width(), rect.height(), method);
    }
    _binPackList.push_back(std::move(bin));
}

std::vector<Rect> BinPackHelper::get_bestBin(std::vector<Rect> &rectList,
                                             rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method,
                                             bool allow_flip) {
    rbp::MaxRectsBinPack bin;
    std::vector<Rect> dst;
    int maxWidth = sum_width(rectList);
    int maxHeight = sum_height(rectList);

    if(maxHeight > maxWidth)
        maxWidth = maxHeight;
    else
        maxHeight = maxWidth;
    bin.Init(maxWidth, maxHeight, allow_flip);
    bin.Insert(rectList, dst, method);
    _binPackList.push_back(std::move(bin));
    return std::move(dst);
}

std::vector<rbp::MaxRectsBinPack> BinPackHelper::get_smallest_squares() {
    auto min_bin = get_minArea(_binPackList);
    auto min_side = square_side(min_bin.GetUsedRectangles());
    return get_bins_minSide(_binPackList, min_side);
}




//Get all the packs with the minimum side in a vector
std::vector<rbp::MaxRectsBinPack> get_bins_minSide(std::vector<rbp::MaxRectsBinPack> &binPackList, int min_side) {
    std::vector<rbp::MaxRectsBinPack> matches;
    copy_if(binPackList.begin(), binPackList.end(), back_inserter(matches), [&](rbp::MaxRectsBinPack v) {
        return square_side(v.GetUsedRectangles()) == min_side;
    });
    return matches;
}

rbp::MaxRectsBinPack get_minArea(std::vector<rbp::MaxRectsBinPack> &binPackList) {
    auto minimumBinPack = min_element(binPackList.begin(), binPackList.end(),
                                      [](const rbp::MaxRectsBinPack &a, const rbp::MaxRectsBinPack &b)
                                      {
                                          return square_side(a.GetUsedRectangles()) < square_side(b.GetUsedRectangles());
                                      });
    return *minimumBinPack;
}

rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method, bool allow_flip) {
    rbp::MaxRectsBinPack bin;
    int maxWidth = sum_width(rectList);
    int maxHeight = sum_height(rectList);

    if(maxHeight > maxWidth)
        maxWidth = maxHeight;
    else
        maxHeight = maxWidth;

    bin.Init(maxWidth, maxHeight, allow_flip);

    for(auto rect : rectList) {
        bin.Insert(rect.width(), rect.height(), method);
        auto free_space = 100.f - bin.Occupancy()*100.f;
        //std::cout << "free space:" << free_space << std::endl;
    }
    return bin;
}

std::string heuristic_to_string(rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method) {

    std::string heuristic;
    switch (method) {
        case rbp::MaxRectsBinPack::Uncertain:
            heuristic = "RectBestShortSideFit";
            break;
        case rbp::MaxRectsBinPack::RectBestShortSideFit:
            heuristic = "RectBestShortSideFit";
            break;
        case rbp::MaxRectsBinPack::RectBestLongSideFit:
            heuristic = "RectBestLongSideFit";
            break;
        case rbp::MaxRectsBinPack::RectBestAreaFit:
            heuristic = "RectBestAreaFit";
            break;
        case rbp::MaxRectsBinPack::RectBottomLeftRule:
            heuristic = "RectBottomLeftRule";
            break;
        case rbp::MaxRectsBinPack::RectContactPointRule:
            heuristic = "RectContactPointRule";
            break;
    }
    return heuristic;
}
