#include <iostream>
#include <unordered_map>
#include "Direction.hpp"
#include <algorithm>
#include <string>
#include <stdexcept>
#include <vector>
#include "Notebook.hpp"
//#define ROW_MAX_LENGTH 100

constexpr unsigned int row_max_length=100;

using namespace ariel;

namespace ariel{
    Notebook::Notebook() {
    }
    void Notebook:: default_line_fill(std::vector<char> &line){
        for (unsigned int i = 0; i < row_max_length ; ++i) {
            line.at(i)='_';
        }
    }

    void Notebook::write(int page,int row, int column,Direction d,std::string str){
        if(page < 0 || row < 0 || column < 0){
            throw std::invalid_argument("page, row and column have to be non-negative");
        }
        if((unsigned int) column >= row_max_length ){
            throw std::invalid_argument("Out of bounces: row length is limited to 100 chars!");
        }
        unsigned int unsigned_page=(unsigned int)page;
        unsigned int unsigned_row=(unsigned int)row;
        unsigned int unsigned_column=(unsigned int)column;
        if ((unsigned_column >= row_max_length) || ((( unsigned_column +str.length() -1 ) >= row_max_length) && (d==Direction::Horizontal))){
            throw std::invalid_argument("Out of bounces: row length is limited to 100 chars!");
        }
        for (unsigned int i = 0; i < str.length(); ++i) {
            if( std::isprint(str[i])==0 || str[i]=='~'){
                throw std::invalid_argument("Invalid value was entered");
            }
        }

        // This page is not exist yet or the page exist but the row is empty
        if (_notebook.find(unsigned_page) == _notebook.end() || _notebook[unsigned_page][unsigned_row].empty()){
            if (d == Direction::Horizontal){
                _notebook[unsigned_page][unsigned_row].resize(row_max_length);
                Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row]);
                for (unsigned int i = 0; i < str.length() ; ++i) {
                    _notebook[unsigned_page][unsigned_row].at(unsigned_column+i)=str[i];
                }
            }else{ //vertical
                for (unsigned int i = 0; i <str.length() ; ++i) {
                    if (_notebook[unsigned_page][unsigned_row+i].empty()){ // the row is not exist
                        _notebook[unsigned_page][unsigned_row+i].resize(row_max_length);
                        Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row + i]);
                        _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)=str[i];
                    }else{
                        if (_notebook[unsigned_page][unsigned_row+i].at(unsigned_column) == '_'){
                            _notebook[unsigned_page][unsigned_row+i].at(unsigned_column) = str[i];
                        }else{
                            throw std::invalid_argument("cannot write to a place written already");
                        }
                    }
                }
            }
        }
        else{// this page and row is already exist
            if (d==Direction::Horizontal){
                for (unsigned int i = 0; i < str.length() ; ++i) {
                    if (_notebook[unsigned_page][unsigned_row].at(unsigned_column+i)=='_'){
                        _notebook[unsigned_page][unsigned_row].at(unsigned_column+i)=str[i];
                    }else{
                        throw std::invalid_argument("cannot write to a place written already");
                    }
                }
            }else{//vertical
                for (unsigned int i = 0; i <str.length() ; ++i) {
                    if (_notebook[unsigned_page][unsigned_row+i].empty()){ // the row is not exist
                        _notebook[unsigned_page][unsigned_row+i].resize(row_max_length);
                        Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row+i]);
                        _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)=str[i];
                    }else{
                        if (_notebook[unsigned_page][unsigned_row+i].at(unsigned_column)== '_' ){
                            _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)=str[i];
                        }else{
                            throw std::invalid_argument("cannot write to a place written already");
                        }
                    }
                }
            }
        }
    }

    std::string Notebook::read( int page, int row, int column,Direction d, int length) {
        std::string str;
        if(page < 0 || row < 0 || column < 0 || length < 0){
            throw std::invalid_argument("page, row and column,length have to be non-negative");
        }
      if((unsigned int)column>= row_max_length){
          throw std::invalid_argument("Out of bounces: row length is limited to 100 chars!");
      }
        unsigned int unsigned_page=(unsigned int)page;
        unsigned int unsigned_row=(unsigned int)row;
        unsigned int unsigned_column=(unsigned int)column;
        unsigned int unsigned_length=(unsigned int)length;
        if (d == Direction::Horizontal && unsigned_column + unsigned_length -1 >= row_max_length) {
            throw std::invalid_argument("Out of bounces: row length is limited to 100 chars!");
        }
        if (_notebook[unsigned_page][unsigned_row].empty()) {
            _notebook[unsigned_page][unsigned_row].resize(row_max_length);
            Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row]);
            for (int i = 0; i < length; ++i) {
                str += '_';
            }
            return str;
        }
        if (d == Direction::Horizontal) {
            for (unsigned int i = 0; i < length; ++i) {
                str += _notebook[unsigned_page][unsigned_row].at(unsigned_column + i);
            }
        } else {//vertical
            for (unsigned int i = 0; i < length; ++i) {
                if (_notebook[unsigned_page][unsigned_row + i].empty()) {
                    str += '_';
                } else {
                    str += _notebook[unsigned_page][unsigned_row + i].at(unsigned_column);
                }
            }
        }
        return str;

    }

    void Notebook::erase( int page, int row, int column,Direction d, int length){
        if(page < 0 || row < 0 || column < 0 || length < 0){
            throw std::invalid_argument("page, row and column have to be non-negative");
        }
        unsigned int unsigned_page=(unsigned int)page;
        unsigned int unsigned_row=(unsigned int)row;
        unsigned int unsigned_column=(unsigned int)column;
        unsigned int unsigned_length=(unsigned int)length;
        if(d==Direction::Horizontal && unsigned_column+unsigned_length-1 >=row_max_length){
            throw std::invalid_argument("Out of bounces: row length is limited to 100 chars!");
        }
        if (_notebook[unsigned_page][unsigned_row].empty()){ // this row is no exist
            if(d==Direction::Horizontal){
                _notebook[unsigned_page][unsigned_row].resize(row_max_length);
                Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row]);
                for (unsigned int i = 0; i < unsigned_length; ++i) {
                    _notebook[unsigned_page][unsigned_row].at(unsigned_column + i)='~';
                }
            }else{//vertical
                for (unsigned int i = 0; i < unsigned_length ; ++i) {
                    if (_notebook[unsigned_page][unsigned_row+i].empty()){ // the row is not exist
                        _notebook[unsigned_page][unsigned_row+i].resize(row_max_length);
                        Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row+i]);
                        _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)='~';
                    }else{ //the row exist
                            _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)='~';
                    }
                }
            }
        }else{
            if (d==Direction::Horizontal){
                for (unsigned int i = 0; i <unsigned_length ; ++i) {
                    _notebook[unsigned_page][unsigned_row].at(unsigned_column+i)='~';
                }
            }else{//vertical
                for (unsigned int i = 0; i <unsigned_length ; ++i) {
                    if (_notebook[unsigned_page][unsigned_row+i].empty()){ // the row is not exist
                        _notebook[unsigned_page][unsigned_row+i].resize(row_max_length);
                        Notebook::default_line_fill(_notebook[unsigned_page][unsigned_row+i]);
                        _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)='~';
                    }else{ //the row exist
                        _notebook[unsigned_page][unsigned_row+i].at(unsigned_column)='~';
                    }
                }
            }
        }
    }

    std::string Notebook:: show(int page){
        if(page<0){
            throw std::invalid_argument("page has to be non-negative");
        }
        unsigned int unsigned_page= (unsigned int)page;
        std::string str;
        for (unsigned int row = 0; row < row_max_length-1 ; ++row) {
            str+= std::to_string(row);
            str+=":";
            if( !_notebook[unsigned_page][row].empty()){
                for (unsigned int j = 0; j < row_max_length-1 ; ++j) {
                    str+=_notebook[unsigned_page][row].at(j);
                }
            }else{
                for (unsigned int j = 0; j < row_max_length ; ++j) {
                    str+='_';
                }
            }
            str+='\n';
        }
        return str;
    }




}









