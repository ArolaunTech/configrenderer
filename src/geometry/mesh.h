#include <vector>

#include "../types/vector.h"

#ifndef MESH_H
#define MESH_H

struct MeshArrays {
	std::vector<Vector3> points;
	std::vector<Vector3> normals;
};

MeshArrays join(const MeshArrays& a, const MeshArrays& b);
MeshArrays operator+(const MeshArrays& lhs, const MeshArrays& rhs);

#endif