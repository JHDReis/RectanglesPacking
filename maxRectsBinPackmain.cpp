//
// Created by Joao Henriques David Dos Reis on 16/10/2018.
//

#include <iostream>
#include <limits>
#include <chrono>
#include <future>
#include <thread>
#include "BinPackHelper.h"
#include "RectangleBinPack/MaxRectsBinPack.h"
#include "RectLoader.h"
#include "RectanglesList.h"



int main() {
    std::cout << "Max Rectangles Bin Algorithm!" << std::endl;
    std::cout << "Loading from file (0) or loading from random (1)" <<std::endl;
    int choice;
    std::cin>>choice;

    std::vector<Rect> rectList;
    if(choice == 0) {
        //RectLoader loader("../Files/VerySimpleTest.txt");
        RectLoader loader("../Files/20_rectangles.txt");

        if(!loader.is_valid_file()) {
            std::cout << "File Not Valid!" << std::endl;
            return 1;
        }
        rectList = loader.load();
    }
    else if(choice == 1) {
        std::cout << "insert max rect and max rand number" << std::endl;
        int rectangles, max_rand;
        std::cin>>rectangles>>max_rand;
        rectList = RectLoader::load_rand(rectangles, max_rand);
    } else
        return 1;


    std::cout << "Iterations per Algorithm:" <<std::endl;
    int iterations = 1000;
    std::cin>>iterations;
    int it_ordered = iterations;

    auto rectList2(rectList);
    sort_area_dec(rectList2);

    BinPackHelper bph_shuffled;
    BinPackHelper bph_ordered;



    auto future_shuffled = std::async(std::launch::async, [&](){
        std::chrono::milliseconds total;
        std::chrono::milliseconds loop;
        while(iterations--) {
            auto start = std::chrono::high_resolution_clock::now();
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit, false);
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit, true);

            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit, false);
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit, true);

            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestAreaFit, false);
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBestAreaFit, true);

            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule, false);
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule, true);

            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectContactPointRule, false);
            bph_shuffled.add(rectList, rbp::MaxRectsBinPack::RectContactPointRule, true);

            shuffle_vector(rectList);

            loop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
            total += loop;
            if(iterations%10 == 0)
                std::cout<<"[S] = "<<loop.count()<<std::endl;
        }
        std::cout<<iterations<<"shuffled loop:"<<total.count()<<" ms."<<std::endl;
    });

    auto future_ordered = std::async(std::launch::async, [&](){
        std::chrono::milliseconds total;
        std::chrono::milliseconds loop;
        while(it_ordered--) {
            auto start = std::chrono::high_resolution_clock::now();
            //Ordered vectors (Biggest Area >> Smallest Area
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit, false);
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit, true);

            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit, false);
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit, true);

            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit, false);
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit, true);

            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule, false);
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule, true);

            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectContactPointRule, false);
            bph_ordered.add(rectList2, rbp::MaxRectsBinPack::RectContactPointRule, true);

            loop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
            total += loop;
            if(it_ordered%10 == 0)
                std::cout<<"[O] = "<<loop.count()<<std::endl;
        }
        std::cout<<iterations<<"shuffled loop:"<<total.count()<<" ms."<<std::endl;
    });

    future_shuffled.wait();
    future_ordered.wait();

    std::cout<<std::endl<<"Shuffled Best bin pack results:" <<std::endl;
    for( auto bp : bph_shuffled.get_smallest_squares()) {
        auto result = square_side(bp.GetUsedRectangles());
        std::string flipped = bp.AllowFlip()?"allow":"disabled";
        std::cout<<"------------------------------"<<std::endl;
        std::cout<<"Flipped:"<<flipped<<std::endl;
        std::cout<<"Heuristic:"<<heuristic_to_string(bp.UsedHeuristic())<<std::endl;
        std::cout<<"square "<<result<<"x"<<result<<std::endl;
    }


    std::cout<<std::endl<<"Ordered Best bin pack results:" <<std::endl;
    for( auto bp : bph_ordered.get_smallest_squares()) {
        auto result = square_side(bp.GetUsedRectangles());
        std::string flipped = bp.AllowFlip()?"allow":"disabled";
        std::cout<<"------------------------------"<<std::endl;
        std::cout<<"Flipped:"<<flipped<<std::endl;
        std::cout<<"Heuristic:"<<heuristic_to_string(bp.UsedHeuristic())<<std::endl;
        std::cout<<"square "<<result<<"x"<<result<<std::endl;
    }
    return 0;
}





//    std::vector<rbp::MaxRectsBinPack> binPackList;
//
//    while(iterations--) {
//        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit)));
//
//        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit)));
//
//        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestAreaFit)));
//
//        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule)));
//
//        std::cout << " --------- RectContactPointRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectContactPointRule)));
//
//        // disable flip
//        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestShortSideFit, false)));
//
//        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestLongSideFit, false)));
//
//        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBestAreaFit, false)));
//
//        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectBottomLeftRule, false)));
//
//        std::cout << " --------- RectContactPointRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList, rbp::MaxRectsBinPack::RectContactPointRule, false)));
//
//        shuffle_vector(rectList);
//
//        //sort from biggest to small area;
//
//
//        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit)));
//
//        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit)));
//
//        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit)));
//
//        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule)));
//
//        std::cout << " --------- RectContactPointRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectContactPointRule)));
//
//        // disable flip
//        std::cout << " --------- RectBestShortSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestShortSideFit, false)));
//
//        std::cout << " --------- RectBestLongSideFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestLongSideFit, false)));
//
//        std::cout << " --------- RectBestAreaFit ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBestAreaFit, false)));
//
//        std::cout << " --------- RectBottomLeftRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectBottomLeftRule, false)));
//
//        std::cout << " --------- RectContactPointRule ---------" << std::endl;
//        binPackList.push_back(std::move(OneByOneMaxPack(rectList2, rbp::MaxRectsBinPack::RectContactPointRule, false)));
//
//    }
//
//
//    auto minBinPack = get_minArea(binPackList);
//    auto min_side = square_side(minBinPack.GetUsedRectangles());
//    std::cout<<"Minimum square side results are: " <<min_side<<std::endl;
//
//
//    std::vector<rbp::MaxRectsBinPack> matches = get_bins_minSide(binPackList, min_side);
//
//
//    std::cout<<std::endl<<"Best bin pack results:" <<std::endl;
//    for( auto bp : matches) {
//        auto result = square_side(bp.GetUsedRectangles());
//        std::string flipped = bp.AllowFlip()?"flip":"disabled";
//        std::cout<<"Flipped:"<<flipped<<std::endl;
//        std::cout<<"Heuristic:"<<bp.UsedHeuristic()<<std::endl;
//        std::cout<<"square "<<result<<"x"<<result<<std::endl;
//    }



