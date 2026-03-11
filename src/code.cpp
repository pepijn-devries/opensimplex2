#include <cpp11.hpp>
#include "OpenSimplexCleanup.h"
using namespace cpp11;

#define PERIOD 64

[[cpp11::register]]
doubles_matrix<> noise2d_(int width, int height, double frequency, long seed) {
  writable::doubles_matrix<> mat(width, height);
  OpenSimplexEnv *ose = initOpenSimplex();
  OpenSimplexGradients *osg = newOpenSimplexGradients(ose, seed);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      mat(i, j) = noise2(
        ose, osg,
        frequency * (i - width/2)/PERIOD,
        frequency * (j - height/2)/PERIOD);
    }
  }
  freeOpenSimplexGradients(osg);
  freeOpenSimplex(ose);
  return mat;
}

[[cpp11::register]]
sexp noise3d_(int width, int height, int depth, double frequency, long seed) {
  writable::doubles d(width*height*depth);
  d.attr("dim") = writable::integers({width, height, depth});
  d.attr("class") = "array";
  OpenSimplexEnv *ose = initOpenSimplex();
  OpenSimplexGradients *osg = newOpenSimplexGradients(ose, seed);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < depth; k++) {
        int idx = i + j*width + k*width*height; //todo
        d[i + j*width + k*width*height] = noise3_Classic(ose, osg,
                                                         frequency * (i - width/2)/PERIOD,
                                                         frequency * (j - height/2)/PERIOD,
                                                         frequency * (k - depth/2)/PERIOD);
      }
    }
  }
  freeOpenSimplexGradients(osg);
  freeOpenSimplex(ose);
  return d;
}