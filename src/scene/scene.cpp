#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "../geometry/mesh.h"

void Scene::compile() {
	points.clear();
	normals.clear();
	startindices.clear();
	sizes.clear();

	std::size_t nummeshes = meshes.size();
	for (std::size_t i = 0; i < nummeshes; i++) {
		startindices.push_back(points.size());

		MeshArrays mesh = meshes[i];

		std::size_t numpoints = mesh.points.size();

		for (std::size_t j = 0; j < numpoints; j++) {
			points.push_back((GLfloat)mesh.points[j].x);
			points.push_back((GLfloat)mesh.points[j].y);
			points.push_back((GLfloat)mesh.points[j].z);

			normals.push_back((GLfloat)mesh.normals[j].x);
			normals.push_back((GLfloat)mesh.normals[j].y);
			normals.push_back((GLfloat)mesh.normals[j].z);
		}

		sizes.push_back(points.size() - startindices[i]);
	}
}