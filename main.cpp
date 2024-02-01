#include <iostream>
#include <Matrix.h>
#include <Utils.h>

int main()
{
	Matrix matA("1&2&3.0\\1.3&2\\1&3&2\\1&2&4&2&1&0&30");
	Matrix matB("5.23\\2.3\\3\\4\\5\\6\\7");
	
	std::cout << matA;
	std::cout << matB << std::endl;
	std::cout << matA * matB;
	return 0;
}
