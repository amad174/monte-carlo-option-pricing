cmake_minimum_required(VERSION 3.16)
project(mc_pricer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mc_pricer src/main.cpp)
