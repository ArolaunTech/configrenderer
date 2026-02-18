#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "matrix.h"
#include "../consts/consts.h"

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	std::size_t lhsrows = lhs.elements.size();
	std::size_t rhsrows = rhs.elements.size();
	std::size_t lhscols = lhs.elements[0].size();
	std::size_t rhscols = rhs.elements[0].size();

	if (lhscols != rhsrows) {
		throw std::runtime_error("Invalid sizes for matrix multiplication.");
	}

	Matrix out;
	out.elements.clear();

	for (std::size_t i = 0; i < lhsrows; i++) {
		out.elements.push_back(std::vector<double>(rhscols));

		for (std::size_t j = 0; j < rhscols; j++) {
			double elem = 0;

			for (std::size_t k = 0; k < lhscols; k++) {
				elem += lhs.elements[i][k] * rhs.elements[k][j];
			}

			out.elements[i][j] = elem;
		}
	}

	return out;
}

Matrix identityMatrix(int rows) {
	Matrix out;
	for (int i = 0; i < rows; i++) {
		out.elements.push_back(std::vector<double>(rows));
		for (int j = 0; j < rows; j++) {
			out.elements[i][j] = 0;

			if (i == j) out.elements[i][j] = 1;
		}
	}

	return out;
}

Matrix translate(Vector3 x) {
	Matrix out;

	out.elements = {
		{1,   0,   0,   0},
		{0,   1,   0,   0},
		{0,   0,   1,   0},
		{x.x, x.y, x.z, 1}
	};

	return out;
}

Matrix rotateX(double amount) {
	Matrix out;

	out.elements = {
		{1, 0,                 0,                0},
		{0, std::cos(amount),  std::sin(amount), 0},
		{0, -std::sin(amount), std::cos(amount), 0},
		{0, 0,                 0,                1}
	};

	return out;
}

Matrix rotateY(double amount) {
	Matrix out;

	out.elements = {
		{std::cos(amount), 0, -std::sin(amount), 0},
		{0,                1, 0,                 0},
		{std::sin(amount), 0, std::cos(amount),  0},
		{0,                0, 0,                 1}
	};

	return out;
}

Matrix rotateZ(double amount) {
	Matrix out;

	out.elements = {
		{std::cos(amount),  std::sin(amount), 0, 0},
		{-std::sin(amount), std::cos(amount), 0, 0},
		{0,                 0,                1, 0},
		{0,                 0,                0, 1}
	};

	return out;
}

Matrix scaleX(double amount) {
	Matrix out;

	out.elements = {
		{amount, 0, 0, 0},
		{0,      1, 0, 0},
		{0,      0, 1, 0},
		{0,      0, 0, 1}
	};

	return out;
}

Matrix scaleY(double amount) {
	Matrix out;

	out.elements = {
		{1, 0,      0, 0},
		{0, amount, 0, 0},
		{0, 0,      1, 0},
		{0, 0,      0, 1}
	};

	return out;
}

Matrix scaleZ(double amount) {
	Matrix out;

	out.elements = {
		{1, 0, 0,      0},
		{0, 1, 0,      0},
		{0, 0, amount, 0},
		{0, 0, 0,      1}
	};

	return out;
}

Matrix perspective(double fov, double znear, double zfar) {
	Matrix out;

	double fovRadians = fov * pi / 180;
	double cotHalfFov = std::cos(fovRadians / 2) / std::sin(fovRadians / 2);
	double depth = zfar - znear;

	//http://davidlively.com/programming/graphics/opengl-matrices/perspective-projection/
	out.elements = {
		{cotHalfFov, 0,          0,                         0 },
		{0,          cotHalfFov, 0,                         0 },
		{0,          0,          -(zfar + znear) / depth,   -1},
		{0,          0,          -2 * zfar * znear / depth, 0 }
	};

	return out;
}