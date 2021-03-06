#include "stdafx.h"


constexpr int MaxVertexNum = 100;


std::vector<std::vector<int>> GetMatrix(std::string& inputFileName, int& VertexNum)
{
	std::ifstream inFile;
	inFile.open(inputFileName);

	if (!inFile)
	{
		std::cout << "File don't open\n";
		return std::vector<std::vector<int>>();
	}

	if (!(inFile >> VertexNum))
	{
		VertexNum = 0;
		return std::vector<std::vector<int>>();
	}

	if (VertexNum > MaxVertexNum)
	{
		std::cout << "Invalid argument count!\n" << "Must be less then 100\n";
		return std::vector<std::vector<int>>();
	}

	std::vector<std::vector<int>> matrix(VertexNum, std::vector<int>(VertexNum, 0));
	for (int i = 0; i < VertexNum; i++)
	{
		for (int j = 0; j < VertexNum; j++)
		{
			inFile >> matrix[i][j];
		}
	}
	return matrix;
}


void InitPreFlow(std::vector<std::vector<int>>& capacity, std::vector<std::vector<int>>& flow)
{
	for (size_t i = 0; i < capacity.size(); i++)
	{
		flow[0][i] = capacity[0][i];
		flow[i][0] = -capacity[0][i];
	}
}

void InitHeight(std::vector<int>& height)
{
	*height.begin() = height.size();
}

void InitExcessFlow(std::vector<std::vector<int>>& capacity, std::vector<int>& exessFlow)
{
	for (size_t i = 0; i < capacity.size(); i++)
	{
		exessFlow[i] = capacity[0][i];
		exessFlow[0] -= capacity[0][i];
	}
}


void Push(int first, int second, std::vector<std::vector<int>>& capacity, std::vector<std::vector<int>>& flow, std::vector<int>& exessFlow)
{
	int d = std::min(exessFlow[first], capacity[first][second] - flow[first][second]);
	flow[first][second] += d;
	flow[second][first] = -d;
	exessFlow[first] -= d;
	exessFlow[second] += d;
}

void Relabel(int vertex, std::vector<std::vector<int>>& capacity, std::vector<std::vector<int>>& flow, std::vector<int>& height)
{
	int h = 2 * capacity.size();

	for (size_t i = 0; i < capacity.size(); i++)
	{
		if ((capacity[vertex][i] - flow[vertex][i]) > 0)
		{
			h = std::min(h, height[i]);
		}
	}

	height[vertex] = h + 1;
}

bool Discharge(int i, std::vector<std::vector<int>>& capacity, std::vector<std::vector<int>>& flow, std::vector<int>& height, std::vector<int>& excessFlow)
{
	int j = 0;
	bool isRelabeled = false;
	while (excessFlow[i] > 0)
	{
		if (j == capacity.size())
		{
			Relabel(i, capacity, flow, height);
			j = 0;
			isRelabeled = true;
		}
		if (((capacity[i][j] > 0) || (capacity[j][i] > 0)) && ((capacity[i][j] - flow[i][j]) > 0) && (height[i] == (height[j] + 1)))
		{
			Push(i, j, capacity, flow, excessFlow);
		}
		else
		{
			j++;
		}
	}
	return isRelabeled;
}


int GetFlow(std::vector<std::vector<int>>& capacity, std::vector<std::vector<int>>& flow, std::vector<int>& height, std::vector<int>& excessFlow)
{
	InitPreFlow(capacity, flow);
	InitHeight(height);
	InitExcessFlow(capacity, excessFlow);
	std::list <int> vertexList;
	for (size_t i = 1; i < capacity.size() - 1; i++)
	{
		vertexList.push_back(i);
	}
	auto cur = vertexList.begin();
	while (cur != vertexList.end())
	{
		if (Discharge(*cur, capacity, flow, height, excessFlow))
		{
			vertexList.erase(cur); 
			int j = *cur;
			cur = vertexList.insert(vertexList.begin(), j);
		}
		cur++;
	}

	return excessFlow[capacity.size() - 1];
} 



int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument";
		return 1;
	}

	std::string inputFileName = argv[1];
	int VertexNum = 0;

	std::vector<std::vector<int>> capacity = GetMatrix(inputFileName, VertexNum);
	std::vector<std::vector<int>> flow(VertexNum, std::vector<int>(VertexNum, 0));
	std::vector<int> excessFlow(VertexNum, 0);
	std::vector<int> height(VertexNum, 0);

	std::cout << "flow = " << GetFlow(capacity, flow, height, excessFlow) << "\n";
	return 0;
}

