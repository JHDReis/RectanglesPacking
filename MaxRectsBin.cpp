//
// Created by Joao Henriques David Dos Reis on 16/10/2018.
//

#include <iostream>
#include "MaxRectsBinPack.h"
#include "RectLoader.h"
#include "RectanglesList.h"

rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method);

int main() {
    std::cout << "Max Rectangles Bin Algorithm!" << std::endl;

    //1st load the test rectangles
    //RectLoader loader("../Files/VerySimpleTest.txt");
    RectLoader loader("../Files/20_rectangles.txt");

    if(!loader.is_valid_file()) {
        std::cout << "File Not Valid!" << std::endl;
        return 1;
    }

    auto rectList = loader.load();
    auto rectList2 = rectList;

    std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin1 = OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit);

    std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin2 = OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit);

    std::cout << " --------- RectBestAreaFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin3 = OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestAreaFit);

    std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
    rbp::MaxRectsBinPack bin4 = OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule);

    std::cout << " --------- RectContactPointRule ---------" << std::endl;
    rbp::MaxRectsBinPack bin5 = OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectContactPointRule);

    //sort by area;
    sort_area_dec(rectList2);
    std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin6 = OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit);

    std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin7 = OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit);

    std::cout << " --------- RectBestAreaFit ---------" << std::endl;
    rbp::MaxRectsBinPack bin8 = OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit);

    std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
    rbp::MaxRectsBinPack bin9 = OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule);

    std::cout << " --------- RectContactPointRule ---------" << std::endl;
    rbp::MaxRectsBinPack bin10 = OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectContactPointRule);



    //std::vector<Rect> destination;
    //bin.Insert(rectList, destination, MaxRectsBinPack::RectBestShortSideFit);

    return 0;
}

rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method) {
    rbp::MaxRectsBinPack bin;
    int maxWidth = max_width(rectList);
    int maxHeight = max_height(rectList);

    if(maxHeight > maxWidth)
        maxWidth = maxHeight;
    else
        maxHeight = maxWidth;

    bin.Init(maxWidth, maxHeight);

    std::cout << "-> will initialized with: "<<std::to_string(maxWidth)<<"x"<< std::to_string(maxHeight)<< std::endl;
    for(auto rect : rectList) {
        std::cout << "-> before " << rect.width() << "x" << rect.height() << " (" << rect.x() << "," << rect.y() << ")" << std::endl;
        Rect result = bin.Insert(rect.width(), rect.height(), method);
        std::cout << "-> after " << result.width() << "x" << result.height() << " (" << result.x() << "," << result.y() << ")" << std::endl;
        auto free_space = 100.f - bin.Occupancy()*100.f;
        std::cout << "free space:" << free_space << std::endl;
    }
    return bin;
}

