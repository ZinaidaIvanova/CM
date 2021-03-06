// lb3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

//Функция для чтения матрицы смежности из файла
void ReadIncidentMatrix(std::string inputFileName, std::vector<std::vector<float>>& matrix, int& N)
{
	std::ifstream input(inputFileName);
	if (input)
	{
		input >> N;
		if ((N > 9) && (N < 1))
		{
			std::cout << "A graph must contain no more than 8 vertices\n";
		}
		else
		{
			matrix.resize(N);
			for (int i = 0; i < N; i++)
			{
				matrix[i].resize(N);
				for (int j = 0; j < N; j++)
				{
					input >> matrix[i][j];
				}
			}
		}
	}

}


float GetMaxNum(std::vector<std::vector<float>>& matrix)
{
	float sum = 0;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{
			sum += matrix[i][j];
		}
	}
	return sum;
}

//Функция для определения степени вершины графа
int GetDegree(int i, std::vector<std::vector<float>>& incidentMatrix, float MaxNum)
{
	int temp = 0;
	for (size_t j = 0; j < incidentMatrix.size(); j++)
	{
		if((incidentMatrix[i][j] > 0) && (incidentMatrix[i][j] < MaxNum))
		{
			temp++;
		}
	}
	return temp;
}

//Функция для создания матрицы кирхгофа
std::vector<std::vector<float>> GetLaplacianMatrix(std::vector<std::vector<float>>& incidentMatrix, float MaxNum)
{
	std::vector<std::vector<float>> a;

	a.resize(incidentMatrix.size());
	for (size_t i = 0; i < incidentMatrix.size(); i++)
	{
		a[i].resize(incidentMatrix.size());
	}

	for (size_t i = 0; i < incidentMatrix.size(); i++)
	{
		for (size_t j = 0; j < incidentMatrix.size(); j++)
		{
			if (i == j)
			{
				a[i][j] = static_cast<float>(GetDegree(i, incidentMatrix, MaxNum));
			}
			if ((i != j) && (incidentMatrix[i][j] > 0) && (incidentMatrix[i][j] < MaxNum))
			{
				a[i][j] = -1;
			}
		}
	}

	return a;
}

bool IsNullRow(int k, std::vector<std::vector<float>>& matrix)
{
	bool result = true;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		result = (std::abs(matrix[k][i]) < FLT_EPSILON);
		if (!result)
		{
			break;
		}
	}
	return result;
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

//функция для получения определителя матрицы
float GetDet(std::vector<std::vector<float>>& matrix)
{
	for (size_t i = 0; i < matrix.size() - 1; i++)
	{
		if (!(std::abs(matrix[i][i]) < FLT_EPSILON))
		{
			float c = matrix[i][i];
			for (size_t j = i + 1; j < matrix.size(); j++)
			{
				float d = matrix[j][i];
				for (size_t k = 0; k < matrix.size(); k++)
				{
					matrix[j][k] -= (d / c) * matrix[i][k];
				}
			}
		}
		else
		{
			if (IsNullRow(i, matrix))
			{
				break;
			}
			for (size_t k = 0; k < matrix.size(); k++)
			{
				std::swap(matrix[i][k], matrix[i + 1][k]);
			}
		}
	}

	PrintMatrix(matrix, matrix.size());
	float det = 1;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		det *= matrix[i][i];
	}

	return det;
}

//функция для получения дополнительного минора
std::vector<std::vector<float>> GetComplementaryMinor(std::vector<std::vector<float>>& matrix, int i, int j, int N)
{
	std::vector<std::vector<float>> minor(N-1, std::vector<float>(N-1, 0.0f));
	int firstMinorInd;
	int secondMinorInd;
	for (int k = 0; k < N - 1; k++)
	{
		for (int l = 0; l < N - 1; l++)
		{
			(k >= i) ? (firstMinorInd = k + 1) : (firstMinorInd = k);
			(l >= j) ? (secondMinorInd = l + 1) : (secondMinorInd = l);
			minor[k][l] = matrix[firstMinorInd][secondMinorInd];
		}
	}
	return minor;
}


//функция для получения количества остовных деревьев
float GetNumSpanningTrees(std::vector<std::vector<float>>& matrix, int N)
{
	std::vector<std::vector<float>> minor = GetComplementaryMinor(matrix, 0, 0, N);
	PrintMatrix(minor, N - 1);
	float num = GetDet(minor);
	return num;

}


int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	std::string inputFileName = argv[1];
	//std::string inputFileName = "C:/CM/lb3/Debug/example_3-2_2.txt";
	std::vector<std::vector<float>> matrix;
	int Num = 0;
	ReadIncidentMatrix(inputFileName, matrix, Num);
	std::cout << Num << "\n";
	PrintMatrix(matrix, Num);
	std::cout << "\n";
	if (!matrix.empty())
	{
		float maxNum = GetMaxNum(matrix);
		std::vector<std::vector<float>> laplacianMatrix = GetLaplacianMatrix(matrix, maxNum);
		PrintMatrix(laplacianMatrix, Num);
		//GetNumSpanningTrees(laplacianMatrix, Num);
		std::cout << GetNumSpanningTrees(laplacianMatrix, Num) << "\n";
	}
	
	return 0;
}

