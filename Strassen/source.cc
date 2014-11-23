#include <iostream>
#include "Matrix.h"

using std::cout;
using std::endl;

int input1[4][4] = {
	{13, 3, 6, 3},
	{6, 2, 8, 87},
	{37, 42, 57, 69},
	{42, 53, 64, 74}};

int input2[4][4] = {
	{75, 68, 5, 4},
	{64, 58, 47, 3},
	{55, 48, 34, 2},
	{45, 34, 27, 1}};

int main() {
	Matrix inputM1(input1[0], 4);
	Matrix inputM2(input2[0], 4);
	cout << "Input A is:\n" << inputM1 << endl;
	cout << "Input B is:\n" << inputM2 << endl;
	Matrix result(4);
	result = inputM1 * inputM2;
	cout << "Result of A * B is:\n" << result << endl;
	return 0;
}
