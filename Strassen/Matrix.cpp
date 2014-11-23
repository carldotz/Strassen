/*
 * Matrix.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: carl
 */

#include "Matrix.h"

Matrix Matrix::basic_operation(const Matrix & right, char operation) const{
	Matrix result(this->width);
	for(size_t i=0;i< width*width;++i) {
		switch(operation) {
		case '+': result[i] = (*this)[i] + right[i];
		break;
		case '-': result[i] = (*this)[i] - right[i];
		break;
		}
	}
	return result;
}

Matrix Matrix::operator+(const Matrix & right) const {
	return basic_operation(right, '+');
}

Matrix Matrix::operator-(const Matrix & right) const {
	return basic_operation(right, '-');
}

Matrix Matrix::operator*(const Matrix & right) const {
	return strassen(right);
}

int & Matrix::operator[](const size_t i) {
	return (this->data)[i];
}

const int & Matrix::operator[](const size_t i) const {
	return (this->data)[i];
}

Matrix & Matrix::operator=(const Matrix & right) {
	if(this == &right) return *this;
	this->width = right.width;
	delete [] this->data;
	this->data = NULL;
	this->data = new int[this->width * this->width];
	for(size_t i=0;i<this->width * this->width;++i) {
		(*this)[i] = right[i];
	}
	return *this;
}

Matrix Matrix::strassen(const Matrix &b) const{

	Matrix c(width);

	const Matrix &a = *this;

	//End Condition
	if(width == 1) {
		c[0] = a[0] * b[0];
		return c;
	}

	//Initialization
	Matrix *s[10];
	Matrix *p[7];
	Matrix *sub_a[2][2], *sub_b[2][2], *sub_c[2][2];
	size_t sub_width = width / 2;

	for(size_t i=0;i<10;++i) s[i] = new Matrix(sub_width);

	for(size_t i=0;i<7;++i)	p[i] = new Matrix(sub_width);

	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			sub_a[i][j] = new Matrix(sub_width);
			sub_b[i][j] = new Matrix(sub_width);
			sub_c[i][j] = new Matrix(sub_width);
		}
	}

	//Divide
	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			for(size_t y=0;y<sub_width;++y) {
				for(size_t x=0;x<sub_width;++x) {
					(*sub_a[i][j])[y * sub_width + x] = a[i*sub_width*width + y*width + x + j*sub_width];
					(*sub_b[i][j])[y * sub_width + x] = b[i*sub_width*width + y*width + x + j*sub_width];
				}
			}
		}
	}

	//Conquer
	*s[0] = *sub_b[0][1] - *sub_b[1][1];
	*s[1] = *sub_a[0][0] + *sub_a[0][1];
	*s[2] = *sub_a[1][0] + *sub_a[1][1];
	*s[3] = *sub_b[1][0] - *sub_b[0][0];
	*s[4] = *sub_a[0][0] + *sub_a[1][1];
	*s[5] = *sub_b[0][0] + *sub_b[1][1];
	*s[6] = *sub_a[0][1] - *sub_a[1][1];
	*s[7] = *sub_b[1][0] + *sub_b[1][1];
	*s[8] = *sub_a[0][0] - *sub_a[1][0];
	*s[9] = *sub_b[0][0] + *sub_b[0][1];

	*p[0] = *sub_a[0][0] * (*s[0]);
	*p[1] = *s[1] * (*sub_b[1][1]);
	*p[2] = *s[2] * (*sub_b[0][0]);
	*p[3] = *sub_a[1][1] * (*s[3]);
	*p[4] = *s[4] * (*s[5]);
	*p[5] = *s[6] * (*s[7]);
	*p[6] = *s[8] * (*s[9]);

	*sub_c[0][0] = *p[4] + *p[3] - *p[1] + *p[5];
	*sub_c[0][1] = *p[0] + *p[1];
	*sub_c[1][0] = *p[2] + *p[3];
	*sub_c[1][1] = *p[4] + *p[0] - *p[2] - *p[6];


	//	Merge
	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			for(size_t y=0;y<sub_width;++y) {
				for(size_t x=0;x<sub_width;++x) {
					c[i*sub_width*width + y*width + x + j*sub_width] = (*sub_c[i][j])[y * sub_width + x];
				}
			}
		}
	}

	//	Release Memory
	for(size_t i=0;i<10;++i) {
		delete s[i];
		s[i] = NULL;
	}

	for(size_t i=0;i<7;++i)	{
		delete p[i];
		p[i] = NULL;
	}

	for(size_t i=0;i<2;++i) {
		for(size_t j=0;j<2;++j) {
			delete sub_a[i][j];
			sub_a[i][j] = NULL;
			delete sub_b[i][j];
			sub_b[i][j] = NULL;
			delete sub_c[i][j];
			sub_c[i][j] = NULL;
		}
	}

	return c;
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

