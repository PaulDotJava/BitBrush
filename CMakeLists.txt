cmake_minimum_required(VERSION 3.12)
project(BitBrush VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BitBrush 
  src/Main.cpp)
