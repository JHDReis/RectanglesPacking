//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//

#include "RectLoader.h"
#include "Rect.h"

bool file_exist(const std::string &name) {
    std::ifstream f(name.c_str(), std::fstream::in);
    return f.good();
}


RectLoader::RectLoader(const std::string& filePath):_filepath(filePath){
    if(!is_valid_file())
        _filepath.clear();
}

std::vector<Rect>RectLoader::load() {
    if(!is_valid_file())
        return {};

    std::vector<Rect> result;
    std::ifstream infile(_filepath);
    int a,b;
    while(infile>>a>>b){
        if(a < 1 || b < 1) continue;
        result.push_back(Rect(a,b));
    }
    infile.close();
    return std::move(result);
}

std::string RectLoader::get_filepath() {
    return _filepath;
}

bool RectLoader::is_valid_file() {
    if(_filepath.empty()) return false;
    return file_exist(_filepath);
}


