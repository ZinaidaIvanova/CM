#include "stdafx.h"

constexpr int MaxVertexNum = 400;
constexpr int MaxgeNum = MaxVertexNum * (MaxVertexNum - 1) / 2;

struct edge
{
	int vertex1 = 0;
	int vertex2 = 0;
	float weight = 0;
};


std::vector<std::vector<float>> GetEdgesList(std::string& inputFileName, int& vertexNum, int& edgeNum)
{
	std::ifstream inFile;
	inFile.open(inputFileName);

	if (!inFile)
	{
		std::cout << "File don't open\n";
		return std::vector<std::vector<float>>();
	}

	if (!(inFile >> vertexNum >> edgeNum))
	{
		return std::vector<std::vector<float>>();
	}

	std::vector<std::vector<float>> matrix(vertexNum, std::vector<float>(vertexNum, 0.0));
	for (int i = 0; i < edgeNum; i++)
	{
		int k, l;
		float w;
		if (!(inFile >> k >> l >> w))
		{
			std::cout << "k "<<k<<" l "<<l<<" w "<<w <<"\nInvalid argument count!\n" << "Must be 3 number";
			return std::vector<std::vector<float>>();
		}
		matrix[k - 1][l - 1] = w;
		matrix[l - 1][k - 1] = w;
	}
	return matrix;
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

float GetMaxNum(std::vector<std::vector<float>>& matrix)
{
	float num = 0;
	for (int i = 0; i < static_cast<int>(matrix.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(matrix.size()); j++)
		{
			num += matrix[i][j];
		}
	}
	return num;
}

void PrintMatrix(std::vector<std::vector<float>>& matrix, int Num)
{
	for (int i = 0; i < Num; i++)
	{
		for (int j = 0; j < Num; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n";
}

void AddComponent(std::vector<int>& component, int oldNum, int newNum)
{
	for (int &elem : component)
	{
		if (elem == oldNum)
		{
			elem = newNum;
		}
	}
}

bool GetNextEdge(std::vector<std::vector<float>>& matrix, std::vector<int>& component, int compNum, edge& newEdge, std::vector<bool>& isVertexSelected)
{
	float minNum = GetMaxNum(matrix);
	int newVertex1 = 0;
	int newVertex2 = 0;
	for (int i = 0; i < static_cast<int>(matrix.size()); i++)
	{
		if (component[i] == compNum)
		{
			for (int j = 0; j < static_cast<int>(matrix.size()); j++)
			{
				if ((matrix[i][j] < minNum) && (matrix[i][j] != 0) && (component[j] != compNum))
				{
					minNum = matrix[i][j];
					newVertex1 = i;
					newVertex2 = j;
				}
			}
		}
	}
	
	if (minNum == GetMaxNum(matrix))
	{
		return false;
	}
	else
	{
		if ((!isVertexSelected[newVertex1]) && isVertexSelected[newVertex2])
		{
			component[newVertex1] = component[newVertex2];
		}
		else
		{
			AddComponent(component, component[newVertex2], compNum);
		}
		if (!isVertexSelected[newVertex1]) isVertexSelected[newVertex1] = true;
		if (!isVertexSelected[newVertex2]) isVertexSelected[newVertex2] = true;
		newEdge.vertex1 = newVertex1;
		newEdge.vertex2 = newVertex2;
		newEdge.weight = minNum;
		return true;
	}
}

void BoruvkasAlgorithm(std::vector<std::vector<float>>& matrix, std::vector<int>& component, std::vector<edge>& edgesList)
{
	std::vector<bool> isVertexSelected(matrix.size(), false);
	*isVertexSelected.begin() = true;
	int i = 1;
	while (edgesList.size() < (matrix.size() - 1))
	{
		std::vector<int>uniqueComponent = component;
		std::sort(uniqueComponent.begin(), uniqueComponent.end());
		auto last = std::unique(uniqueComponent.begin(), uniqueComponent.end());
		uniqueComponent.erase(last, uniqueComponent.end());
		int j = 1;
		for (auto comp : uniqueComponent)
		{
			edge newEdge;
			if (GetNextEdge(matrix, component, comp, newEdge, isVertexSelected))
			{
				edgesList.push_back(newEdge);
			}
			j++;
		}
		i++;
	}
}

float GetMinWeight(std::vector<edge>& edgesList)
{
	float len = 0.0;
	for (auto elem: edgesList)
	{
		len += elem.weight;
	}
	return len;
}

void PrintEdgeList(std::vector<edge>& edgesList)
{
	for (auto elem : edgesList)
	{
		std::cout << elem.vertex1 + 1 << "  " << elem.vertex2 + 1 << " "<< elem.weight << "\n";
	}
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	std::string inputFileName = argv[1];
	int vertexNum = 0;
	int edgeNum = 0;
	std::vector<std::vector<float>> matrix = GetEdgesList(inputFileName, vertexNum, edgeNum);
	if (!matrix.empty())
	{
		std::vector<int> component = InitPermutation(vertexNum);
		float weight = 0;
		std::vector<edge> edgesList;
		BoruvkasAlgorithm(matrix, component, edgesList);
		std::cout << GetMinWeight(edgesList) << "\n";
		PrintEdgeList(edgesList);
	}
	return 0;
}

