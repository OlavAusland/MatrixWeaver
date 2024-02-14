#include <Matrix.h>
#include <iostream>
#include <cassert>
#include <string>
#include <Utils.h>
#include <vector>

void Matrix::Initialize()
{
	layout = (double**)calloc(rows, sizeof(double*));
	
	for(int i = 0; i < rows; i++)
	{
		layout[i] = (double*)calloc(columns, sizeof(double));
	}
}

Matrix::Matrix(std::string matrix, char row_del, char col_del)
{
	std::vector<std::string> rows = split(matrix, row_del);
	this->rows = rows.size();	
	
	for(std::string row : rows)
	{
		int columns = count(row, col_del);
		if(columns > this->columns){this->columns = columns+1;}
	}

	Initialize();

	for(int i = 0; i < this->rows; i++)
	{
		std::vector<std::string> values = split(rows[i], col_del);

		for(int j = 0; j < values.size(); j++)
		{
			layout[i][j] = std::stod(values[j]);
		}
	}

}

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns)
{
	Initialize();
}

Matrix Matrix::Transpose()
{
	Matrix result{columns, rows};
	
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			result[j][i] = layout[i][j];
		}
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for(int i = 0; i < matrix.rows; i++)
	{
		std::cout << '[';
		for(int j = 0; j < matrix.columns; j++)
		{
			std::cout << matrix.layout[i][j] << '\t';
		}
			std::cout << ']' << '\n';
	}

	return os;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	assert((lhs.rows == rhs.rows && lhs.columns == rhs.columns));
	
	Matrix result(lhs.rows, lhs.columns);

	for(int i = 0; i < lhs.rows; i++)
	{
		for(int j = 0; j < lhs.columns; j++)
		{
			result[i][j] = lhs[i][j] + rhs[i][j];
		}
	}

	return result;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	assert((lhs.rows == rhs.rows && lhs.columns == rhs.columns));

	Matrix result(lhs.rows, lhs.columns);

	for(int i = 0; i < lhs.rows; i++)
	{
		for(int j = 0; j < lhs.columns; j++)
		{
			result[i][j] = lhs[i][j] - rhs[i][j];
		}
	}

	return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	assert((lhs.columns == rhs.rows));

	Matrix result(lhs.rows, rhs.columns);

	for(int i = 0; i < lhs.rows; i++)
	{
		for(int j = 0; j < rhs.columns; j++)
		{
			for(int k = 0; k < rhs.columns; k++)
			{	
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}

	return result;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	*this = (*this - other);
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	*this = (*this + other);
	return *this;
}

int RowEchelon(Matrix& matrix)
{
	int lead = 0;
	
	while(lead < matrix.rows)
	{
		for(int i = lead+1; i < matrix.rows; i++)
		{
			double coefficient = matrix[i][lead] / matrix[lead][lead];
			
			for(int j = 0; j < matrix.columns; j++) 
			{
				matrix[i][j] += matrix[lead][j] * coefficient * -1;	
			}
		}
		lead++;
	
		for(int i = 0; i < matrix.rows; i++)
		{
			double leading = 1;
			int flag = 0;
			for(int j = 0; j < matrix.columns; j++)
			{	
				if(!flag && matrix[i][j] != 0.0)
				{
					leading = matrix[i][j];
					flag = 1;
				}
				if(flag)
				{
					matrix[i][j] *= (1.0 / leading);
					continue;
				}

			}
		}
	}
}

void ReducedRowEchelon(Matrix& matrix)
{
	RowEchelon(matrix);

	for(int i = matrix.rows - 1; i > 0; i--)
	{
		int leading;
		
		for(int j = 0; j < matrix.columns; j++)
		{
			if(matrix[i][j] != 0.0)
			{
				leading = j;
				break;
			}
		}

		for(int j = i-1; j >= 0; j--)
		{
			if(matrix[j][leading] == 0.0){continue;}

			double coefficient = (matrix[j][leading] / matrix[i][leading]);

			for(int k = 0; k < matrix.columns; k++)
			{	
				matrix[j][k] += coefficient * matrix[i][k] * -1;
			}
		}
	}
}
