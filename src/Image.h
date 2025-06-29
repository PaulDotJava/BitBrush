#pragma once

#include <string>

struct Image2D {
  int width;
  int height;
  int *color_channels; 
  int *bit_dept;
  char* data;
  std::string name;
  std::string type;
};
