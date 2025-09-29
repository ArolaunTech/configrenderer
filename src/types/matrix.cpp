#include <vector>

#include "matrix.h"

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