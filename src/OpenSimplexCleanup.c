#include <stdlib.h>
#include "OpenSimplexCleanup.h"

void freeLatticePoint2DArray(LatticePoint2D ** lp2d, int size) {
  for (int i = 0; i < 4; i++) {
    free(lp2d[i]);
  }
  free(lp2d);
}

void freeLatticePointS(LatticePoint3D * lp3d) {
  // Free the entire path:
  //c0->c1->c2->c3->c4->c5->c6->c7->c8->c9->cA->cB->cC->cD
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure);
  free(lp3d);
}

void freeLatticePoint(LatticePoint3D * lp3d) {
  // Free the entire path:
  //c0->c1->c2->c3->c4->c5->c6->c7
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure->nextOnFailure);
  free(lp3d->nextOnFailure);
  free(lp3d);
}

void freeLatticePoint3DArray(LatticePoint3D ** lp3d) {
  for (int i = 0; i < 8; i++) {
    freeLatticePoint(lp3d[i]);
  }
  free(lp3d);
}

void freeLatticePoint4DArray(LatticePoint4D ** lp4d, int size) {
  for (int i = 0; i < size; i++) {
    free(lp4d[i]);
  }
  free(lp4d);
}

void freeOpenSimplex(OpenSimplexEnv *ose) {
  free(ose->GRADIENTS_2D);
  free(ose->GRADIENTS_3D);
  free(ose->GRADIENTS_4D);
  freeLatticePoint2DArray(ose->LOOKUP_2D, 4);
  freeLatticePoint3DArray(ose->LOOKUP_3D);
  freeLatticePoint4DArray(ose->VERTICES_4D, 16);
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

void freeLatticePointS3DArray(LatticePoint3D ** lp3d) {
  for (int i = 0; i < 8; i++) {
    freeLatticePointS(lp3d[i]);
  }
  free(lp3d);
}

void freeLatticePointS4DArray(vect * v) {
  for (int i = 0; i < 256; i++) {
    free(v[i].data);
  }
  free(v);
}

void freeOpenSimplexS(OpenSimplexEnv *ose) {
  free(ose->GRADIENTS_2D);
  free(ose->GRADIENTS_3D);
  free(ose->GRADIENTS_4D);
  freeLatticePoint2DArray(ose->LOOKUP_2D, 16);
  freeLatticePointS3DArray(ose->LOOKUP_3D);
  freeLatticePointS4DArray(ose->LOOKUP_4D);
  freeLatticePoint4DArray(ose->VERTICES_4D, 256);
  free(ose);
}
