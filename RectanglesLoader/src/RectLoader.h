//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//

#ifndef RECTANGLESPACKING_RECTLOADER_H
#define RECTANGLESPACKING_RECTLOADER_H

#include <string>
#include <vector>
#include <fstream>

class Rect;

class RectLoader {

public:
    explicit RectLoader(const std::string& filePath);
    std::vector<Rect> load();

    std::string get_filepath();
    bool is_valid_file();

private:
    RectLoader() = default;

    std::string _filepath;
};


inline bool file_exist(const std::string& name);

#endif //RECTANGULESPACKING_RECTLOADER_H