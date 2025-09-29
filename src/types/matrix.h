#include <vector>

#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
	std::vector<std::vector<double> > elements;
};

Matrix identityMatrix(int rows);

#endif