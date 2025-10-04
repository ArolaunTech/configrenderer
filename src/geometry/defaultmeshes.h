#include "mesh.h"
#include "../types/vector.h"

#ifndef DEFAULT_MESHES_H
#define DEFAULT_MESHES_H

MeshArrays oneSidedTriangle(Vector3 a, Vector3 b, Vector3 c);
MeshArrays oneSidedQuad(Vector3 a, Vector3 b, Vector3 c, Vector3 d);

MeshArrays cube();
MeshArrays sphere(double radius, int subdivisions);
MeshArrays cylinder(int n);

#endif