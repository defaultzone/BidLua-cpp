#include <iostream>
#include <cstring>
#include "compiler.hpp"

int main(int argc, char** argv) {
    compile("/home/dzone/BidLua-cpp/tests/main.blya", "/home/dzone/BidLua-cpp/tests/main.lua", "/home/dzone/BidLua-cpp/tests/main.map.blya", "false");

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            std::cout << "Entered: -h" << std::endl;
        }
    }

    return 0;
}
