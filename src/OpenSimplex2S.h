#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "OpenSimplex2F.h"

OpenSimplexGradients *newOpenSimplexSGradients(OpenSimplexEnv *ose, int64_t seed);
OpenSimplexEnv *initOpenSimplexS();
double noiseS4_XYZBeforeW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
double noiseS4_XZBeforeYW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
double noiseS4_XYBeforeZW(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
double noiseS4_Classic(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z, double w);
double noiseS3_XZBeforeY(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
double noiseS3_XYBeforeZ(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
double noiseS3_Classic(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y, double z);
double noiseS2_XBeforeY(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y);
double noiseS2(OpenSimplexEnv *ose, OpenSimplexGradients *osg, double x, double y);

#ifdef __cplusplus
}
#endif