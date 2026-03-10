#include <cpp11.hpp>
#include "OpenSimplexCleanup.h"
using namespace cpp11;

#define PERIOD 64
// TODO add license https://github.com/MarcoCiaramella/OpenSimplex2/
// https://github.com/KdotJPG/OpenSimplex2/blob/master/java/OpenSimplex2S.java

[[cpp11::register]]
doubles_matrix<> noise2d_(int width, int height, double frequency, long seed) {
  writable::doubles_matrix<> mat(width, height);
  OpenSimplexEnv *ose = initOpenSimplex();
  OpenSimplexGradients *osg = newOpenSimplexGradients(ose, seed);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      mat(i, j) = noise2(
        ose, osg,
        frequency * ((double)i - width/2)/PERIOD,
        frequency * ((double)j - height/2)/PERIOD);
    }
  }
  // TODO: all nested elements should be freed as well!
  freeOpenSimplexGradients(osg);
  freeOpenSimplex(ose);
  return mat;
}
