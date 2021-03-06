#include "stdafx.h"

void Init(std::vector<int>& pi, std::vector<int>& p, std::vector<int>& d, int n)
{
	pi.push_back(n + 1);
	p.push_back(0);
	d.push_back(0);
	for (int i = 1; i < n + 1; i++)
	{
		pi.push_back(i);
		p.push_back(i);
		d.push_back(-1);
	}
	pi.push_back(n + 1);
}

void PrintPermutation(const std::vector<int>& permutation)
{
	std::copy(++permutation.begin(), --permutation.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << "\n";
}

void NewPermutationGeneration(std::vector<int>& pi, std::vector<int>& p, std::vector<int>& d, int& m)
{
	while (pi[p[m] + d[m]] > m)
	{
		d[m] = -d[m];
		m--;
	}
	std::swap(pi[p[m]], pi[p[m] + d[m]]);
	std::swap(p[pi[p[m]]], p[m]);
}

void PermutationGeneration(std::vector<int>& pi, std::vector<int>& p, std::vector<int>& d, int n)
{
	int m = n;
	d[1] = 0;
	while (m != 1)
	{
		//PrintPermutation(pi);
		m = n;
		NewPermutationGeneration(pi, p, d, m);
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
	std::vector<int> invert;
	std::vector<int> directions;
	Init(permutation, invert, directions, n);
	boost::timer t;
	t.restart();
	PermutationGeneration(permutation, invert, directions, n);
	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}