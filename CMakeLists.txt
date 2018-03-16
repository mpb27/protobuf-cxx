cmake_minimum_required(VERSION 3.9)
project(protobuf_cxx)

set(CMAKE_CXX_STANDARD 17)

include_directories(submodules/magic_get/include/)

add_executable(pfr1
        src/test/pfr1.cpp)
