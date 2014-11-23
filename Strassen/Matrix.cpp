/*
 * Matrix.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: carl
 */

#include "Matrix.h"
#include <cstdlib>

Matrix::Matrix(size_t _width) {
	this->width = _width;
	this->data = new int[_width * _width];
}

Matrix::~Matrix() {
	delete [] this->data;
}

Matrix Matrix::basic_operation(Matrix & right, char operation) {
	Matrix result(this->width);
	for(size_t i=0;i<width*width;++i) {
		switch(operation) {
		case '+': result[i] = (*this)[i] + right[i];
		break;
		case '-': result[i] = (*this)[i] - right[i];
		break;
		}
	}
	return result;
}

Matrix Matrix::operator+(Matrix & right) {
	return basic_operation(right, '+');
}

Matrix Matrix::operator-(Matrix & right) {
	return basic_operation(right, '-');
}

int & Matrix::operator[](const size_t i){
	return (this->data)[i];
}

Matrix & Matrix::operator=(Matrix & right) {
	if(this == &right) return *this;
	this->width = right.width;
	delete [] this->data;
	this->data = new int[this->width * this->width];
	for(size_t i=0;i<this->width;++i) {
		(*this)[i] = right[i];
	}
	return *this;
}

void Matrix::strassen(int *a, int *b, int *c, size_t width) {
	int *s[7];
	int *p[7];
	int *sub_a[2][2], *sub_b[2][2], *sub_c[2][2];
	int sub_width = width / 2;

	for(size_t i=0;i<7;++i) {
		s[i] = (int *)malloc(sizeof(int) * sub_width * sub_width);
		p[i] = (int *)malloc(sizeof(int) * sub_width * sub_width);
	}
	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			sub_a[i][j] = (int *)malloc(sizeof(int) * sub_width * sub_width);
			sub_b[i][j] = (int *)malloc(sizeof(int) * sub_width * sub_width);
			sub_c[i][j] = (int *)malloc(sizeof(int) * sub_width * sub_width);
		}
	}

	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			for(size_t y=0;y<sub_width;++y) {
				for(size_t x=0;x<sub_width;++x) {
					*(sub_a[i][j] + y * sub_width + x) = *(a + i*sub_width*width + y*width + x + j*sub_width);
					*(sub_b[i][j] + y * sub_width + x) = *(b + i*sub_width*width + y*width + x + j*sub_width);
				}
			}
		}
	}

//	for(size_t i=0;i<2;++i) {
//		for(size_t j=0;j<2;++j) {
//			for(size_t y=0;y<sub_width;++y) {
//				for(size_t x=0;x<sub_width;++x) {
//					cout << *(sub_a[i][j] + y * sub_width + x) << " ";
//				}
//				cout << endl;
//			}
//		}
//	}

	if(sub_width > 1) {
//		s[0] = *b
	}
}

std::ostream & operator<<(std::ostream &os, Matrix &matrix) {
	for(size_t y=0;y<matrix.get_width();++y) {
		for(size_t x=0;x<matrix.get_width();++x) {
			os << matrix[y * matrix.get_width() + x] << " ";
		}
		os << std::endl;
	}
	return os;
}

