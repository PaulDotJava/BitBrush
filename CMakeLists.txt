cmake_minimum_required(VERSION 3.12)
project(BitBrush VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(BitBrush 
  src/App.cpp
  src/EditorScene.cpp
  src/StartupScene.cpp
  src/Main.cpp)

add_library(Raygui SHARED
  src/RayguiImpl.cpp)

target_link_libraries(Raygui PRIVATE ${CMAKE_SOURCE_DIR}/deps/raylib/lib/libraylib.a)
target_include_directories(Raygui PRIVATE deps/raylib/include)

target_link_libraries(BitBrush PRIVATE Raygui)

target_include_directories(BitBrush PRIVATE deps/raylib/include)
target_link_libraries(BitBrush PRIVATE ${CMAKE_SOURCE_DIR}/deps/raylib/lib/libraylib.a)
