#ifndef OPENSIMPLEX2F
#define OPENSIMPLEX2F
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "opensimplex2_ctypes.h"

  double noise2(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y);
  double noise2_XBeforeY(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y);
  double noise3_Classic(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
  double noise3_XYBeforeZ(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
  double noise3_XZBeforeY(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
  double noise4_Classic(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
  double noise4_XYBeforeZW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
  double noise4_XZBeforeYW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
  double noise4_XYZBeforeW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
  
#ifdef __cplusplus
}
#endif
#endif //OPENSIMPLEX2F