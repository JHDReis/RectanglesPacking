//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//

#include "RectLoader.h"
#include "Rect.h"


bool file_exist(const std::string &name) {
    std::ifstream f(name.c_str(), std::fstream::in);
    return f.good();
}


RectLoader::RectLoader(const std::string& filePath):_file_path(filePath){
    if(!is_valid_file())
        _file_path.clear();
}

std::vector<Rect>RectLoader::load() {
    if(_file_path.empty())
        return {};

    std::vector<Rect> result;
    std::ifstream infile(_file_path);
    int a,b;
    while(infile>>a>>b){
        if(a < 1 || b < 1) continue;
        result.push_back(Rect(a,b));
    }
    infile.close();
    return std::move(result);
}


std::vector<Rect> RectLoader::load_rand(int max_rectangles, int max_rand) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> rand_generator(1, max_rand);
    std::vector<Rect> random_vector;

    for (auto i=0; i<max_rectangles; ++i){
        int rw = rand_generator(generator);
        int rh = rand_generator(generator);

        while(rw == rh)
            rh = rand_generator(generator);
        random_vector.emplace_back(Rect(rw,rh));
    }
    return std::move(random_vector);
}


std::string RectLoader::get_file_path() {
    return _file_path;
}

bool RectLoader::is_valid_file() {
    if(_file_path.empty()) return false;
    return file_exist(_file_path);
}




