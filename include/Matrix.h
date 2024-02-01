#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <string>

class Matrix
{
public:
	int rows{1};
	int columns{1};

	double** layout;
	
	void Initialize();

	Matrix(int rows, int columns);
	Matrix& operator-=(const Matrix& other);
	Matrix& operator+=(const Matrix& other);
	Matrix(std::string matrix, char row_del='\\', char col_del='&');

	double* operator[](int index) const
	{
		return layout[index];
	}

};

Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);