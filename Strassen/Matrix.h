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
	Matrix(size_t _width) : width(_width) {
		this->data = new int[_width * _width];
	}

	Matrix(int *data,size_t _width) : Matrix(_width) {
		for(size_t i=0;i<width * width;++i) {
			this->data[i] = data[i];
		}
	}

	virtual ~Matrix() {
		delete [] this->data;
		this->data = NULL;
	}

	size_t get_width() const{
		return width;
	}
	Matrix & operator=(const Matrix & right);
	Matrix operator+(Matrix & right) const;
	Matrix operator-(Matrix & right) const;
	Matrix operator*(const Matrix & right) const;
	int & operator[](const size_t i);
	const int & operator[](const size_t i) const;


private:
	Matrix basic_operation(Matrix & right, char operation) const;
	Matrix strassen(const Matrix &b) const;
};

std::ostream & operator<<(std::ostream &os, Matrix &matrix);

#endif /* MATRIX_H_ */
