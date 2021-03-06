#include "stdafx.h"

std::vector<std::vector<int>> ReadIncidentMatrix(std::string& inputFileName)
{
	std::ifstream input(inputFileName);
	int N;
	input >> N;
	if ((N > 11) && (N < 1))
	{
		std::cout << "A graph must contain no more than 10 vertices\n";
		return std::vector<std::vector<int>>();
	}
	std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 0));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			input >> matrix[i][j];
		}
	}
	return matrix;
}

int GetHamiltonLenght(std::vector<std::vector<int>>& matrix, std::vector<int>& permutation)
{
	int len = 0;
	for (int i = 0; i < static_cast<int>(permutation.size()); i++)
	{
		int j = (i + 1) % permutation.size();
		if (matrix[permutation[i]][permutation[j]] == 0)
		{
			return -1;
		}
		len += matrix[permutation[i]][permutation[j]];
	}
	return len;
}

std::vector<int> InitPermutation(int N)
{
	std::vector <int> vec(N, 0);
	for (int i = 0; i < N; i++)
	{
		vec[i] = i;
	}
	return vec;
}

int GetMaxNum(std::vector<std::vector<int>>& matrix)
{
	int num = 0;
	for (int i = 0; i < static_cast<int>(matrix.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(matrix.size()); j++)
		{
			num += matrix[i][j];
		}
	}
	return num;
}


int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	std::string inputFileName = argv[1];
	std::vector<std::vector<int>> matrix;
	matrix = ReadIncidentMatrix(inputFileName);
	if (!matrix.empty())
	{
		std::vector <int> permutation = InitPermutation(static_cast<int> (matrix.size()));
		std::vector <int> minPermutation(matrix.size(), 0);
		int minLen = GetMaxNum(matrix);
		do
		{
			int len= GetHamiltonLenght(matrix, permutation);
			if ((len != -1) && (len < minLen))
			{
				minLen = len;
				minPermutation = permutation;
			}

		} while (std::next_permutation(permutation.begin(), permutation.end()));
		std::cout << "MinLenght = " << minLen << "\n";
		for(int num: minPermutation)
		{
			std::cout << num + 1 << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}

