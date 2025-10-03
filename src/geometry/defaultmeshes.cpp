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

MeshArrays oneSidedQuad(Vector3 a, Vector3 b, Vector3 c, Vector3 d) {
	return oneSidedTriangle(a, b, c) + oneSidedTriangle(a, c, d);
}

MeshArrays cube() {
	MeshArrays out;

	for (int direction = 0; direction <= 2; direction++) {
		for (int sign = 0; sign <= 1; sign ++) {
			Vector3 normal = {0, 0, 0};

			switch (direction) {
				case 0:
					normal.x = 2 * sign - 1;
					break;
				case 1:
					normal.y = 2 * sign - 1;
					break;
				case 2:
					normal.z = 2 * sign - 1;
			}

			for (int i = 0; i < 6; i++) {
				out.normals.push_back(normal);
			}

			Vector3 blank = {0, 0, 0};
			Vector3 a = {0, 0, 0};
			Vector3 b = {0, 0, 0};
			Vector3 ab = {0, 0, 0};

			switch (direction) {
				case 0:
					blank.x = sign;
					a.x = sign;
					b.x = sign;
					ab.x = sign;

					a.y = 1;
					ab.y = 1;

					b.z = 1;
					ab.z = 1;
					break;
				case 1:
					blank.y = sign;
					a.y = sign;
					b.y = sign;
					ab.y = sign;

					a.z = 1;
					ab.z = 1;

					b.x = 1;
					ab.x = 1;
					break;
				case 2:
					blank.z = sign;
					a.z = sign;
					b.z = sign;
					ab.z = sign;

					a.x = 1;
					ab.x = 1;

					b.y = 1;
					ab.y = 1;
			}

			blank.x -= 0.5;
			blank.y -= 0.5;
			blank.z -= 0.5;
			a.x -= 0.5;
			a.y -= 0.5;
			a.z -= 0.5;
			b.x -= 0.5;
			b.y -= 0.5;
			b.z -= 0.5;
			ab.x -= 0.5;
			ab.y -= 0.5;
			ab.z -= 0.5;

			if (sign == 1) {
				out.points.push_back(blank);
				out.points.push_back(a);
				out.points.push_back(ab);
				out.points.push_back(blank);
				out.points.push_back(ab);
				out.points.push_back(b);
			} else {
				out.points.push_back(b);
				out.points.push_back(ab);
				out.points.push_back(a);
				out.points.push_back(b);
				out.points.push_back(a);
				out.points.push_back(blank);
			}
		}
	}

	return out;
}