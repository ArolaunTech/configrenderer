#include <vector>

#include "../types/vector.h"

#ifndef MESH_H
#define MESH_H

struct MeshArrays {
	std::vector<Vector3> points;
	std::vector<Vector3> normals;
};

#endif