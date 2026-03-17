#include <cpp11.hpp>
#include <functional>
#include <R_ext/Random.h>
#include "opensimplex2_types.hpp"
#include "OpenSimplex2F.h"
#include "OpenSimplex2S.h"

using namespace cpp11;

SimplexSpace::SimplexSpace (char type, int dimensions) {
  char my_type = 'F';
  if (dimensions < 2 || dimensions > 4) cpp11::stop("Dimensions out of range!");
  this->dimensions = dimensions;
  if (type == 'S') my_type = 'S';
  this->type = my_type;
  GetRNGstate();
  uint32_t seed = (uint32_t)(unif_rand() * 4294967296.0);
  PutRNGstate();
  if (this->type == 'F') {
    ose = initOpenSimplex();
    osg = newOpenSimplexGradients(ose, seed);
  } else {
    ose = initOpenSimplexS();
    osg = newOpenSimplexSGradients(ose, seed);
  }
}

SimplexSpace::~SimplexSpace () {
  freeOpenSimplexGradients(osg);
  if (type == 'F') {
    freeOpenSimplex(ose);
  } else {
    freeOpenSimplexS(ose);
  }
}

char SimplexSpace::get_type() {
  return this->type;
}

int SimplexSpace::get_dimensions() {
  return this->dimensions;
}

OpenSimplexEnv * SimplexSpace::getOSE() {
  return this->ose;
}

OpenSimplexGradients * SimplexSpace::getOSG() {
  return this->osg;
}

[[cpp11::register]]
doubles_matrix<> noise2d_(int width, int height, double frequency) {
  SimplexSpace ss('F', 2L);
  writable::doubles_matrix<> mat(width, height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      mat(i, j) = noise2(
        ss.getOSE(), ss.getOSG(),
        frequency * (i - width/2)/width,
        frequency * (j - height/2)/height);
    }
  }
  return mat;
}

[[cpp11::register]]
sexp noise3d_(int width, int height, int depth, double frequency) {
  SimplexSpace ss('F', 3L);
  writable::doubles d(width*height*depth);
  d.attr("dim") = writable::integers({width, height, depth});
  d.attr("class") = "array";
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < depth; k++) {
        d[i + j*width + k*width*height] = noise3_Classic(ss.getOSE(), ss.getOSG(),
                                                         frequency * (i - width/2)/width,
                                                         frequency * (j - height/2)/height,
                                                         frequency * (k - depth/2)/depth);
      }
    }
  }
  return d;
}

[[cpp11::register]]
sexp noise4d_(int width, int height, int depth, int slice, double frequency) {
  SimplexSpace ss('F', 4L);
  writable::doubles d(width*height*depth*slice);
  d.attr("dim") = writable::integers({width, height, depth, slice});
  d.attr("class") = "array";
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < depth; k++) {
        for (int l = 0; l < slice; l++) {
          d[i + j*width + k*width*height + l*width*height*depth] =
            noise4_Classic(ss.getOSE(), ss.getOSG(),
                           frequency * (i - width/2)/width,
                           frequency * (j - height/2)/height,
                           frequency * (k - depth/2)/depth,
                           frequency * (l - slice/2)/slice);
        }
      }
    }
  }
  return d;
}

[[cpp11::register]]
doubles_matrix<> noise2dS_(int width, int height, double frequency) {
  SimplexSpace ss('S', 2L);
  writable::doubles_matrix<> mat(width, height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      mat(i, j) = noiseS2(
        ss.getOSE(), ss.getOSG(),
        frequency * (i - width/2)/width,
        frequency * (j - height/2)/height);
    }
  }
  return mat;
}

[[cpp11::register]]
sexp noise3dS_(int width, int height, int depth, double frequency) {
  SimplexSpace ss('S', 3L);
  writable::doubles d(width*height*depth);
  d.attr("dim") = writable::integers({width, height, depth});
  d.attr("class") = "array";
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < depth; k++) {
        d[i + j*width + k*width*height] = noiseS3_Classic(
          ss.getOSE(), ss.getOSG(),
          frequency * (i - width/2)/width,
          frequency * (j - height/2)/height,
          frequency * (k - depth/2)/depth);
      }
    }
  }
  return d;
}

[[cpp11::register]]
sexp noise4dS_(int width, int height, int depth, int slice, double frequency) {
  SimplexSpace ss('S', 4L);
  writable::doubles d(width*height*depth*slice);
  d.attr("dim") = writable::integers({width, height, depth, slice});
  d.attr("class") = "array";
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < depth; k++) {
        for (int l = 0; l < slice; l++) {
          d[i + j*width + k*width*height + l*width*height*depth] =
            noiseS4_Classic(ss.getOSE(), ss.getOSG(),
                           frequency * (i - width/2)/width,
                           frequency * (j - height/2)/height,
                           frequency * (k - depth/2)/depth,
                           frequency * (l - slice/2)/slice);
        }
      }
    }
  }
  return d;
}

[[cpp11::register]]
external_pointer<SimplexSpace> simplex_space_(std::string type, int dimensions) {
  char my_type = 'F';
  if (type == "S") my_type = 'S';
  return external_pointer<SimplexSpace>(new SimplexSpace(my_type, dimensions));
}

void check_ss_pointer(external_pointer<SimplexSpace> ss) {
  if (ss.get() == nullptr) cpp11::stop("External pointer is no longer valid");
}

[[cpp11::register]]
sexp simplex_sample_space_2d(external_pointer<SimplexSpace> ss,
                             doubles i, doubles j) {
  check_ss_pointer(ss);
  if (i.size() != j.size()) cpp11::stop("All dimension args should have same length");
  writable::doubles result(i.size());
  std::function<double(OpenSimplexEnv *,OpenSimplexGradients *,double,double)> f;
  if (ss->get_type() == 'F') f = noise2; else f = noiseS2;
  for (R_xlen_t idx = 0; idx < i.size(); idx++) {
    result[idx] = f(ss->getOSE(), ss->getOSG(), i[idx], j[idx]);
  }
  return result;
}

[[cpp11::register]]
sexp simplex_sample_space_3d(external_pointer<SimplexSpace> ss,
                             doubles i, doubles j, doubles k) {
  check_ss_pointer(ss);
  if (i.size() != j.size() || i.size() != k.size())
    cpp11::stop("All dimension args should have same length");
  writable::doubles result(i.size());
  std::function<double(OpenSimplexEnv *,OpenSimplexGradients *,double,double,double)> f;
  if (ss->get_type() == 'F') f = noise3_Classic; else f = noiseS3_Classic;
  for (R_xlen_t idx = 0; idx < i.size(); idx++) {
    result[idx] = f(ss->getOSE(), ss->getOSG(), i[idx], j[idx], k[idx]);
  }
  return result;
}

[[cpp11::register]]
sexp simplex_sample_space_4d(external_pointer<SimplexSpace> ss,
                             doubles i, doubles j, doubles k, doubles l) {
  check_ss_pointer(ss);
  if (i.size() != j.size() || i.size() != k.size() ||
      i.size() != l.size())
    cpp11::stop("All dimension args should have same length");
  writable::doubles result(i.size());
  std::function<double(OpenSimplexEnv *,OpenSimplexGradients *,double,double,double,double)> f;
  if (ss->get_type() == 'F') f = noise4_Classic; else f = noiseS4_Classic;
  for (R_xlen_t idx = 0; idx < i.size(); idx++) {
    result[idx] = f(ss->getOSE(), ss->getOSG(), i[idx], j[idx], k[idx], l[idx]);
  }
  return result;
}

[[cpp11::register]]
sexp simplex_sample_close(external_pointer<SimplexSpace> ss) {
  check_ss_pointer(ss);
  delete ss.get();
  R_ClearExternalPtr(ss);
  return R_NilValue;
}