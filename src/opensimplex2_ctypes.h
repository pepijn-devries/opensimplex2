#ifndef OPENSIMPLEX2_CTYPES
#define OPENSIMPLEX2_CTYPES

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
  unsigned int length;
  void *data;
} vect;

typedef struct {
  int32_t xsv, ysv;
  double dx, dy;
} LatticePoint2D;

typedef struct _LatticePoint3D {
  double dxr, dyr, dzr;
  int32_t xrv, yrv, zrv;
  struct _LatticePoint3D *nextOnFailure;
  struct _LatticePoint3D *nextOnSuccess;
} LatticePoint3D;

typedef struct {
  int32_t xsv, ysv, zsv, wsv;
  double dx, dy, dz, dw;
  double xsi, ysi, zsi, wsi;
  double ssiDelta;
} LatticePoint4D;

typedef struct {
  double dx, dy;
} Grad2;

typedef struct {
  double dx, dy, dz;
} Grad3;

typedef struct {
  double dx, dy, dz, dw;
} Grad4;

typedef struct {
  short *perm;
  Grad2 *permGrad2;
  Grad3 *permGrad3;
  Grad4 *permGrad4;
} OpenSimplexGradients;

typedef struct {
  Grad2 *GRADIENTS_2D;
  Grad3 *GRADIENTS_3D;
  Grad4 *GRADIENTS_4D;
  LatticePoint2D **LOOKUP_2D;
  LatticePoint3D **LOOKUP_3D;
  LatticePoint4D **VERTICES_4D;
  vect *LOOKUP_4D;
} OpenSimplexEnv;

int32_t _fastFloor(double x);
Grad2 *_newGrad2Arr(uint32_t size);
Grad3 *_newGrad3Arr(uint32_t size);
Grad4 *_newGrad4Arr(uint32_t size);
short *_newShortArr(uint32_t size);
Grad2 _newGrad2(double dx, double dy);
Grad3 _newGrad3(double dx, double dy, double dz);
Grad4 _newGrad4(double dx, double dy, double dz, double dw);

OpenSimplexEnv *initOpenSimplex(void);
OpenSimplexGradients *newOpenSimplexGradients(OpenSimplexEnv *ose, int64_t seed);
OpenSimplexGradients *newOpenSimplexSGradients(OpenSimplexEnv *ose, int64_t seed);
OpenSimplexEnv *initOpenSimplexS(void);

void freeOpenSimplex(OpenSimplexEnv *ose);
void freeOpenSimplexS(OpenSimplexEnv *ose);
void freeOpenSimplexGradients(OpenSimplexGradients *osg);

#ifdef __cplusplus
}
#endif
#endif //OPENSIMPLEX2_CTYPES
