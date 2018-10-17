//
// Created by Joao Henriques David Dos Reis on 16/10/2018.
//

#include <iostream>
#include "MaxRectsBinPack.h"
#include "RectLoader.h"
#include "RectanglesList.h"

using namespace rbp;


int main() {
    std::cout << "Max Rectangles Bin Algorithm!" << std::endl;

    //1st load the test rectangles
    RectLoader loader("../Files/VerySimpleTest.txt");

    if(!loader.is_valid_file()) {
        std::cout << "File Not Valid!" << std::endl;
        return 1;
    }

    auto rectList = loader.load();

    RectanglesList rl;
    rl.load(rectList);

    std::cout << "-> will initialized with: "<<std::to_string(rl.max_width())<<"x"<< std::to_string(rl.max_height())<< std::endl;

    MaxRectsBinPack bin;
    bin.Init(rl.max_width(), rl.max_height());

    for(auto rect : rectList) {
        std::cout << "-> before "<<rect.width()<<"x"<< rect.height()<<" ("<<rect.x()<<","<<rect.y()<<")"<< std::endl;
        Rect result = bin.Insert(rect.width(), rect.height(), MaxRectsBinPack::RectBestShortSideFit);
        std::cout << "-> after "<<result.width()<<"x"<< result.height()<<" ("<<result.x()<<","<<result.y()<<")"<< std::endl;
        auto occuppancy = 100.f - bin.Occupancy()*100.f;
        std::cout << "Occuppancy:"<<occuppancy<<std::endl;
    }

    std::vector<Rect> destination;
    bin.Insert(rectList, destination, MaxRectsBinPack::RectBestShortSideFit);

    return 0;
}

