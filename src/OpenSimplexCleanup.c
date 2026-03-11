#include <stdlib.h>
#include "OpenSimplexCleanup.h"

void freeLatticePoint2DArray(LatticePoint2D ** lp2d) {
  for (int i = 0; i < 4; i++) {
    free(lp2d[i]);
  }
  free(lp2d);
}

void freeLatticePoint3DArray(LatticePoint3D ** lp3d) {
  for (int i = 0; i < 8; i++) {
    free(lp3d[i]);
  }
  free(lp3d);
}

void freeLatticePoint4DArray(LatticePoint4D ** lp4d) {
  for (int i = 0; i < 16; i++) {
    free(lp4d[i]);
  }
  free(lp4d);
}

void freeOpenSimplex(OpenSimplexEnv *ose) {
  free(ose->GRADIENTS_2D);
  free(ose->GRADIENTS_3D);
  free(ose->GRADIENTS_4D);
  freeLatticePoint2DArray(ose->LOOKUP_2D);
  freeLatticePoint3DArray(ose->LOOKUP_3D);
  freeLatticePoint4DArray(ose->VERTICES_4D);
  free(ose);
  return;
}

void freeOpenSimplexGradients(OpenSimplexGradients *osg) {
  free(osg->perm);
  free(osg->permGrad2);
  free(osg->permGrad3);
  free(osg->permGrad4);
  free(osg);
  return;
}