#ifndef NOTEBOOK_A_MAIN_NOTEBOOK_H
#define NOTEBOOK_A_MAIN_NOTEBOOK_H
#endif //NOTEBOOK_A_MAIN_NOTEBOOK_H

#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
#include <algorithm>
#include <string>
#include <stdexcept>
#include <vector>

#define ROW_MAX_LENGTH 100

namespace ariel{
    class Notebook{
    private:
        std::unordered_map<unsigned int,std::unordered_map<unsigned int,std::vector<char>>> _notebook;

    public:
        Notebook();
        void write( int page, int row, int column,Direction d,std::string str);
        std::string read( int page, int row, int column,Direction d, int length);
        void erase( int page, int row, int column,Direction d, int length);
        std::string show( int page);
        static void default_line_fill(std::vector<char> &line);
    };

}






