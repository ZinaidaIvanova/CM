// lb1-2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void PrintPermutation(const std::vector<int>& permutation)
{
	std::copy(++permutation.begin(), permutation.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << "\n";
}

void Init(std::vector<int>& permutation, int n)
{
	for (int i = 0; i <= n; i++)
	{
		permutation.push_back(i);
	}
}

void PermutationGeneration(std::vector<int>& permutation, int n)
{
	int i = 1;
	while (i != 0)
	{
		//PrintPermutation(permutation);
		i = n - 1;
		while (permutation[i] > permutation[i + 1])
		{
			i--;
		}
		int j = n;
		while (permutation[j] < permutation[i])
		{
			j--;
		}
		std::swap(permutation[i], permutation[j]);
		int k = i + 1;
		int m = i + (n - i) / 2;
		while (k <= m)
		{
			std::swap(permutation[k], permutation[n - k + i + 1]);
			k++;
		}
	}
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
	return 1;
	}

	const int n = std::atoi(argv[1]);
	std::vector<int> permutation;
	Init(permutation, n);
	boost::timer t;
	t.restart();
	PermutationGeneration(permutation, n);
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}