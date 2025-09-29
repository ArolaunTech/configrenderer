#include "defaultmeshes.h"
#include "mesh.h"
#include "../types/vector.h"

MeshArrays oneSidedTriangle(Vector3 a, Vector3 b, Vector3 c) {
	MeshArrays out;

	out.points = {a, b, c};

	Vector3 normal = normalize(cross(b - a, c - b)); //Counterclockwise
	//Vector3 normal = cross(c - b, b - a); //Clockwise

	out.normals = {normal, normal, normal};
	
	return out;
}