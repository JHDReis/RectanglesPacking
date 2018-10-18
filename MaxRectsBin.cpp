//
// Created by Joao Henriques David Dos Reis on 16/10/2018.
//

#include <iostream>
#include <limits>
#include "RectangleBinPack/MaxRectsBinPack.h"
#include "RectLoader.h"
#include "RectanglesList.h"

rbp::MaxRectsBinPack OneByOneMaxPack(const std::vector<Rect> &rectList
        , rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method
        , bool allow_flip = true);

int main() {
    std::cout << "Max Rectangles Bin Algorithm!" << std::endl;
    std::cout << "Loading from file (0) or loading from random (1)" <<std::endl;
    int choice;
    std::cin>>choice;

    std::vector<Rect> rectList;
    if(choice == 0) {
        RectLoader loader("../Files/VerySimpleTest.txt");
        //RectLoader loader("../Files/20_rectangles.txt");

        if(!loader.is_valid_file()) {
            std::cout << "File Not Valid!" << std::endl;
            return 1;
        }
        rectList = loader.load();
    }
    else if(choice == 1) {
        rectList = RectLoader::load_rand(100);
    } else
        return 1;


    std::cout << "Iterations per Algorithm:" <<std::endl;
    int iterations = 1000;
    std::cin>>iterations;

    auto rectList2(rectList);
    sort_area_dec(rectList2);
    std::vector<rbp::MaxRectsBinPack> binPackList;

    while(iterations--) {
        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit)));

        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit)));

        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestAreaFit)));

        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule)));

        std::cout << " --------- RectContactPointRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectContactPointRule)));

        // disable flip
        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit, false)));

        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit, false)));

        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestAreaFit, false)));

        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule, false)));

        std::cout << " --------- RectContactPointRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectContactPointRule, false)));

        shuffle_vector(rectList);

        //sort from biggest to small area;


        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit)));

        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit)));

        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit)));

        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule)));

        std::cout << " --------- RectContactPointRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectContactPointRule)));

        // disable flip
        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit, false)));

        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit, false)));

        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit, false)));

        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule, false)));

        std::cout << " --------- RectContactPointRule ---------" << std::endl;
        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectContactPointRule, false)));

    }


    std::cout<<std::endl<<"Bin Pack results square:" <<std::endl;
    int i = 0;
    int best_side = std::numeric_limits<int>::max();
    std::vector<int> best_index;
    for( auto bp : binPackList) {
        int side = square_side(bp.GetUsedRectangles());

        if(side <= best_side){
            best_side = side;
            best_index.push_back(i);
        }
        std::cout<<" binpack["<<(i++)<<"] = "<<square_side(bp.GetUsedRectangles())<<std::endl;
    }


    std::cout<<std::endl<<"Best bin pack results:" <<std::endl;
    for( auto index : best_index) {
        std::cout << " binpack[" << index << "] = " << best_side << std::endl;
        auto result = binPackList[index].GetUsedRectangles();
        std::string flipped = binPackList[index].AllowFlip()?"flip":"disabled";
        std::cout<<"Flipped:"<<flipped<<std::endl;
        std::cout<<"Heuristic:"<<binPackList[index].UsedHeuristic()<<std::endl;
    }

    return 0;
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

