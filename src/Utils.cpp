#include <vector>
#include <string>

std::vector<std::string> split(std::string str, char delimiter)
{
	std::vector<std::string> result;

	int i = 0, j = 0;
	for(; j < str.length(); j++)
	{
		if(str[j] == delimiter)
		{
			result.push_back(str.substr(i, j - i));
			i = j + 1;
		}
	}

	result.push_back(str.substr(i, j - i));
	
	return result;
}

int count(std::string target, char symbol)
{
	int reocurrences = 0;

	for(int i = 0; i < target.length(); i++)
	{
		if(target[i] == symbol){reocurrences++;}
	}

	return reocurrences;
}
