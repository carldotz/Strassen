/*
 * Matrix.h
 *
 *  Created on: Nov 21, 2014
 *      Author: carl
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

class Matrix {
	size_t width;
	int *data;
public:
	Matrix(size_t _width);
	virtual ~Matrix();
	size_t get_width() {
		return width;
	}
	Matrix & operator=(Matrix & right);
	Matrix operator+(Matrix & right);
	Matrix operator-(Matrix & right);
	int & operator[](const size_t i);

private:
	Matrix basic_operation(Matrix & right, char operation);
	void strassen(int *a, int *b, int *c, size_t _width);
};

std::ostream & operator<<(std::ostream &os, Matrix &matrix);

#endif /* MATRIX_H_ */
