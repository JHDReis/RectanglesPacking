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
        std::cout << "insert rectangles number and max rand number" << std::endl;
        int rectangles, max_rand;
        std::cin>>rectangles>>max_rand;
        rectList = RectLoader::load_rand(rectangles, max_rand);
    } else
        return 1;

    std::cout << "Iterations per Algorithm:" <<std::endl;
    int iterations = 1000;
    std::cin>>iterations;
    int it_ordered = iterations;
    int it_shuffled = iterations;

    auto rectList2(rectList);
    sort_area_dec(rectList2);

    BinPackHelper bph_shuffled;
    BinPackHelper bph_ordered;

    std::chrono::milliseconds total_shuffled;
    std::chrono::milliseconds total_ordered;

    auto future_shuffled = std::async(std::launch::async, [&](){
        std::chrono::milliseconds loop;
        while(it_shuffled--) {
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
            total_shuffled += loop;
            if(it_shuffled%10 == 0)
                std::cout<<"[S] = "<<loop.count()<<"ms   ("<<iterations-it_shuffled<<")"<<std::endl;
        }

    });

    auto future_ordered = std::async(std::launch::async, [&](){
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
            total_ordered += loop;
            if(it_ordered%5 == 0)
                std::cout<<"[O] = "<<loop.count()<<"ms   ("<<iterations-it_ordered<<")"<<std::endl;
        }

    });

    future_shuffled.wait();
    future_ordered.wait();

    std::cout<<std::endl<<"-> Shuffled Best bin pack results:" <<std::endl;
    auto shuffled_solution = bph_shuffled.get_smallest_squares();
    int shuffle_side = square_side(shuffled_solution.begin()->GetUsedRectangles());

    for( auto bp : shuffled_solution) {
        std::string flipped = bp.AllowFlip()?"allow":"disabled";
        std::cout<<"-----------shuffled-------------"<<std::endl;
        std::cout<<"Flipped:"<<flipped<<std::endl;
        std::cout<<"Heuristic:"<<heuristic_to_string(bp.UsedHeuristic())<<std::endl;
    }

    std::cout<<std::endl<<"-> Ordered Best bin pack results:" <<std::endl;
    auto ordered_solution = bph_ordered.get_smallest_squares();

    int ordered_side = square_side(shuffled_solution.begin()->GetUsedRectangles());
    for( auto bp : ordered_solution) {
        std::string flipped = bp.AllowFlip()?"allow":"disabled";
        std::cout<<"------------ordered------------"<<std::endl;
        std::cout<<"Flipped:"<<flipped<<std::endl;
        std::cout<<"Heuristic:"<<heuristic_to_string(bp.UsedHeuristic())<<std::endl;
    }

    std::cout<<"shuffled solution square: "<<shuffle_side<<"x"<<shuffle_side<<std::endl;
    std::cout<<"shuffled solutions found: "<<shuffled_solution.size()<<std::endl;
    std::cout<<"shuffled loop: "<<total_shuffled.count()<<" ms."<<std::endl;

    std::cout<<"ordered solution square: "<<ordered_side<<"x"<<ordered_side<<std::endl;
    std::cout<<"ordered solutions found: "<<ordered_solution.size()<<std::endl;
    std::cout<<"ordered loop: "<<total_ordered.count()<<" ms."<<std::endl;

    return 0;
}




