#include <stdlib.h>
#include "OpenSimplexCleanup.h"

void freeOpenSimplex(OpenSimplexEnv *ose) {
  free(ose->GRADIENTS_2D);
  free(ose->GRADIENTS_3D);
  free(ose->GRADIENTS_4D);
  free(ose->LOOKUP_2D);
  free(ose->LOOKUP_3D);
  free(ose->VERTICES_4D);
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