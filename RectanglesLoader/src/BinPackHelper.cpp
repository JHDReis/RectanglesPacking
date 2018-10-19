//
// Created by Joao Henriques David Dos Reis on 19/10/2018.
//

#include "BinPackHelper.h"
#include "RectanglesList.h"



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

    //std::cout << "-> will initialized with: "<<std::to_string(maxWidth)<<"x"<< std::to_string(maxHeight)<< std::endl;
    for(auto rect : rectList) {
        //std::cout << "-> before " << rect.width() << "x" << rect.height() << " (" << rect.x() << "," << rect.y() << ")" << std::endl;
        Rect result = bin.Insert(rect.width(), rect.height(), method);
        //std::cout << "-> after " << result.width() << "x" << result.height() << " (" << result.x() << "," << result.y() << ")" << std::endl;
        auto free_space = 100.f - bin.Occupancy()*100.f;
        //std::cout << "free space:" << free_space << std::endl;
    }
    return bin;
}


