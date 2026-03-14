#ifndef SIMPLEX_SPACE_H
#define SIMPLEX_SPACE_H
#pragma once

#include <cpp11.hpp>
#include "R_ext/Random.h"
#include "opensimplex2_ctypes.h"
using namespace cpp11;

class SimplexSpace {
public:
  SimplexSpace(char type, int dimensions);
  ~SimplexSpace();
  char get_type();
  int get_dimensions();
  OpenSimplexEnv * getOSE();
  OpenSimplexGradients * getOSG();
private:
  char type;
  int dimensions;
  OpenSimplexEnv * ose;
  OpenSimplexGradients * osg;
};

#endif //SIMPLEX_SPACE_H