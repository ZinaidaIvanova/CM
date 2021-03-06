// lb1-3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void PrintCombination(std::vector<int>& combination)
{
	std::copy(++combination.begin(), combination.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

std::vector<int> InitCombination(int k)
{
	std::vector<int> temp = { -1 };
	for (size_t i = 1; i <= k; i++)
	{
		temp.push_back(i);
	}
	return temp;
}

void CombinationGeneration(std::vector<int>& combination, int n, int k)
{
	size_t j = 1;
	while (j != 0)
	{
		PrintCombination(combination);
		j = k;
		while (combination[j] == n - k + j)
		{
			--j;
		}
		++combination[j];
		for (size_t i = j + 1; i <= k; ++i)
		{
			combination[i] = combination[i - 1] + 1;
		}
	}
}



int main(const int argc, const char* argv[])
{
	if (argc != 3)
	{
		return 1;
	}

	const int n = std::atoi(argv[1]);
	const int k = std::atoi(argv[2]);
	if (n < k)
	{
		return 1;
	}
	std::vector<int> combination;
	combination = InitCombination(k);
	boost::timer t;
	t.restart();
	CombinationGeneration(combination, n, k);
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}

