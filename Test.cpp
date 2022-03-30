#include <iostream>
#include "doctest.h"
#include <unordered_map>
#include "sources/Direction.hpp"
#include <algorithm>
#include <string>
#include <stdexcept>
#include "sources/Notebook.hpp"
#define ROW_MAX_LENGTH 100

using namespace ariel;

TEST_CASE("good easy cases"){
    Notebook note;
    note.write(0,0,0,Direction::Horizontal,"firstcheck");
    note.write(0,1,0,Direction::Vertical,"orever");
    CHECK(note.read(0,0,0,Direction::Vertical,5)=="forev");
    CHECK(note.read(0,0,5,Direction::Horizontal,5)=="check");
    note.erase(0,0,2,Direction::Horizontal,3);
    CHECK(note.read(0,0,0,Direction::Horizontal,10)=="fi~~~check");
    note.erase(0,0,0,Direction::Vertical,5);
    CHECK(note.read(0,0,0,Direction::Vertical,7)=="~~~~~er");
}

TEST_CASE("good difficult cases"){
    Notebook note;
    note.write(1,0,0,Direction::Horizontal,"1111");
    note.write(1,0,5,Direction::Horizontal,"2222");
    CHECK(note.read(1,0,0,Direction::Horizontal,9)=="1111_2222");
    note.write(1,1,4,Direction::Vertical,"3333");
    CHECK(note.read(1,0,4,Direction::Vertical,5)=="_3333");
    note.erase(1,0,2,Direction::Horizontal,2);
    note.erase(1,2,4,Direction::Vertical,2);
    CHECK(note.read(1,0,0,Direction::Horizontal,9)=="11~~_2222");
    CHECK(note.read(1,0,4,Direction::Vertical,5)=="_3~~3");


}

TEST_CASE("bad inputs"){
    Notebook note;
    CHECK_THROWS(note.write(-1,0,0,Direction::Horizontal,"page cannot be negative"));
    CHECK_THROWS(note.write(-1,0,0,Direction::Vertical,"page cannot be negative"));
    CHECK_THROWS(note.write(1,-5,0,Direction::Horizontal,"Row cannot be negative"));
    CHECK_THROWS(note.write(1,-100,0,Direction::Vertical,"Row cannot be negative"));
    CHECK_THROWS(note.write(10,0,-3,Direction::Horizontal,"column cannot be_negative"));
    CHECK_THROWS(note.write(100,0,-20,Direction::Vertical,"column cannot be_negative"));
    CHECK_THROWS(note.write(0,0,101,Direction::Horizontal,"row length is limited to 100 characters"));

    CHECK_THROWS(note.read(-1,0,0,Direction::Horizontal,3));
    CHECK_THROWS(note.read(-1,0,0,Direction::Vertical,20));
    CHECK_THROWS(note.read(1,-5,0,Direction::Horizontal,10));
    CHECK_THROWS(note.read(1,-100,0,Direction::Vertical,5));
    CHECK_THROWS(note.read(2,6,-3,Direction::Horizontal,1));
    CHECK_THROWS(note.read(14,5,-20,Direction::Vertical,2));
    CHECK_THROWS(note.read(4,5,102,Direction::Horizontal,2));

    CHECK_THROWS(note.erase(-1,0,0,Direction::Horizontal,3));
    CHECK_THROWS(note.erase(-1,0,0,Direction::Vertical,20));
    CHECK_THROWS(note.erase(1,-5,0,Direction::Horizontal,10));
    CHECK_THROWS(note.erase(1,-80,0,Direction::Vertical,5));
    CHECK_THROWS(note.erase(2,6,-3,Direction::Horizontal,1));
    CHECK_THROWS(note.erase(0,1,-1,Direction::Vertical,2));
    CHECK_THROWS(note.erase(0,1,103,Direction::Vertical,2));
    note.write(0,0,0,Direction::Horizontal,"abcd");
    CHECK_THROWS(note.write(0,0,0,Direction::Vertical,"defg"));

}
