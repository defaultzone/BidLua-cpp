cmake_minimum_required(VERSION 3.24)
project(BidLua_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(BidLua_cpp src/main.cpp src/replace.hpp src/names/names.hpp src/userMap.hpp src/compiler.hpp src/info.h)
