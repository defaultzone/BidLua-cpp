#include <iostream>
#include <string>
#include "compiler.hpp"
//#include "replace.hpp"
//#include "names/names.hpp"

int main(int argc, char** argv) {
    compile("/home/dzone/BidLua-cpp/tests/main.blya", "/home/dzone/BidLua-cpp/tests/main.lua", "/home/dzone/BidLua-cpp/tests/main.map.blya", "false");

    std::cout << "DEBUG | MAIN.CPP: " << replaceKeys("бадяга.обьединяло", names, ".blya");

    return 0;
}
