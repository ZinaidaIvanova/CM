#include "stdafx.h"


constexpr int MaxFirstNum = 100;
constexpr int MaxSecondNum = 100;

std::vector<std::vector<int>> GetMatrix(std::string& inputFileName, int& firstVertexNum, int& secondVertexNum)
{
	std::ifstream inFile;
	inFile.open(inputFileName);

	if (!inFile)
	{
		std::cout << "File don't open\n";
		return std::vector<std::vector<int>>();
	}

	if (!(inFile >> firstVertexNum >> secondVertexNum))
	{
		firstVertexNum = 0;
		secondVertexNum = 0;
		return std::vector<std::vector<int>>();
	}

	if ((firstVertexNum > MaxFirstNum) || (secondVertexNum > MaxSecondNum))
	{
		std::cout << "Invalid argument count!\n" << "Must be less then 100\n";
		return std::vector<std::vector<int>>();
	}

	std::vector<std::vector<int>> matrix(firstVertexNum, std::vector<int>(secondVertexNum, 0));
	for (int i = 0; i < firstVertexNum; i++)
	{
		for (int j = 0; j < secondVertexNum; j++)
		{
			inFile >> matrix[i][j];
		}
	}
	return matrix;
}

bool IsExistComplementaryChain(int& i, std::vector<std::vector<int>>& matrix, std::vector<int>& first, std::vector<int>& second)
{
	for (int j = 0; j < second.size(); ++j)
		if ((matrix[i][j] == 1) && (first[i] != j))
		{
			if ((second[j] == -1) || (IsExistComplementaryChain(second[j], matrix, first, second)))
			{
				first[i] = j;
				second[j] = i;
				return true;
			}
		}
	return false;
}

void KhunAlgorithm(std::vector<std::vector<int>>& matrix, std::vector<int>& first, std::vector<int>& second)
{
	for (int i = 0; i < first.size(); i++)
	{
		IsExistComplementaryChain(i, matrix, first, second);
	}
}

bool IsFulMatching(std::vector<int>& matching)
{
	for (int& elem : matching)
	{
		if (elem == -1)
		{
			return false;
		}
	}
	return true;
}

void PrintVec(std::vector<int>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << i << "  " << vec[i] << "\n";
	}
}

void PrintResult(std::vector<int>& vec)
{
	if (IsFulMatching(vec))
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
	}
	
	PrintVec(vec);
}


int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument";
		return 1;
	}
	
	std::string inputFileName = argv[1];
	int firstVertexNum = 0;
	int secondVertexNum = 0;

	std::vector<std::vector<int>> matrix = GetMatrix(inputFileName, firstVertexNum, secondVertexNum);
	std::vector<int> first(firstVertexNum, -1);
	std::vector<int> second(secondVertexNum, -1);

	KhunAlgorithm(matrix, first, second);

	if (firstVertexNum <= secondVertexNum)
	{
		PrintResult(first);
	}
	else
	{
		PrintResult(second);
	}
	
	return 0;
}
