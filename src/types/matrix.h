#include <vector>

#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
	std::vector<std::vector<double> > elements;
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs);

Matrix identityMatrix(int rows);
Matrix translate(Vector3 x);
Matrix rotateX(double amount);
Matrix rotateY(double amount);
Matrix rotateZ(double amount);

Matrix perspective(double fov, double znear, double zfar);

#endif