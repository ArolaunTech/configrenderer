#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../types/vector.h"
#include "../types/matrix.h"
#include "../geometry/mesh.h"

#ifndef SCENE_H
#define SCENE_H

struct Scene {
	Vector4 background;

	bool mesheschanged = true;
	bool matriceschanged = true;

	std::vector<MeshArrays> meshes;

	std::vector<Matrix> rotations;
	std::vector<Matrix> translations;
	Matrix view;
	Matrix perspective;

	std::vector<GLfloat> points;
	std::vector<GLfloat> normals;
	std::vector<unsigned int> startindices;
	std::vector<unsigned int> sizes;

	void compile();
};

#endif