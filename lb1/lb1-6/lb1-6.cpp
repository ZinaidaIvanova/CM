#include "stdafx.h"

void getInfo(std::string inputFileName, std::vector<int>& w, std::vector<int>& c, int& num, int& capacity)
{
	std::ifstream input(inputFileName);
	if (input)
	{
		input >> num >> capacity;
		w.resize(num);
		c.resize(num);
		for (int i = 0; i < num; i++)
		{
			input >> w[i];
		}
		for (int i = 0; i < num; i++)
		{
			input >> c[i];
		}
	}
}

void GetItemsMaxCost(int N, int C, std::vector<int>& w, std::vector<int>& c, std::vector<std::vector<int>>& a)
{
	a.resize(N + 1);
	for (int i=0; i < N + 1; i++)
	{
		a[i].resize(C + 1);
	}
	for (int k = 1; k < N + 1; k++)
	{
		for (int s = 1; s < C + 1; s++)
		{
			(s >= w[k-1]) ? (a[k][s] = std::max((a[k - 1][s]), (a[k - 1][s - w[k-1]] + c[k-1]))) : (a[k][s] = a[k - 1][s]);
		}
	}
}

std::vector<int> GetResult(int N, int C, std::vector<int>& w, std::vector<std::vector<int>>& a)
{
	std::vector<int> temp;
	int k = N;
	int s = C;
	while (a[k][s] != 0)
	{
		if (a[k][s] == a[k - 1][s])
		{
			k--;
		}
		else
		{
			temp.push_back(k);
			s = s - w[k-1];
			k--;
		}
	}
	return temp;
}

void PrintVector(const std::vector<int>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	std::string inputFileName = argv[1];
	int num = 0, capacity = 0;
	std::vector<int> weight; 
	std::vector<int> cost;
	getInfo(inputFileName, weight, cost, num, capacity);
	std::vector<std::vector<int>> MaxItemsCost;
	GetItemsMaxCost(num, capacity, weight, cost, MaxItemsCost);
	PrintVector(GetResult(num, capacity, weight, MaxItemsCost));
	return 0;
}

