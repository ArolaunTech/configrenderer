#include <vector>

#include "mesh.h"

MeshArrays join(const MeshArrays& a, const MeshArrays& b) {
	MeshArrays out;

	out.points = a.points;
	out.normals = a.normals;

	out.points.insert(out.points.end(), b.points.begin(), b.points.end());
	out.normals.insert(out.normals.end(), b.normals.begin(), b.normals.end());

	return out;
}

MeshArrays operator+(const MeshArrays& lhs, const MeshArrays& rhs) {
	return join(lhs, rhs);
}