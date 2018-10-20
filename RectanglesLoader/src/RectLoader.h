//
// Created by Joao Henriques David Dos Reis on 13/10/2018.
//

#ifndef RECTANGLESPACKING_RECTLOADER_H
#define RECTANGLESPACKING_RECTLOADER_H

#include <random>
#include <string>
#include <vector>
#include <fstream>

class Rect;
class RectLoader {
public:
    explicit RectLoader(const std::string& filePath);
    ~RectLoader() = default;
    
    std::vector<Rect> load();
    static std::vector<Rect> load_rand(int max_rectangles, int max_rand = 100);
    std::string get_file_path();
    bool is_valid_file();

private:
    RectLoader() = default;
    std::string _file_path;
};


inline bool file_exist(const std::string& name);

#endif //RECTANGULESPACKING_RECTLOADER_H
