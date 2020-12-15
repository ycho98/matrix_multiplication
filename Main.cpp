#include <array>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <ostream>
#include<ratio>
using namespace std;
using namespace std::chrono;

const int n = 256;

int** originMultiply(int** matrix1, int** matrix2, int** answer)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			answer[i][j] = 0;

			for (int k = 0; k < n; k++)
			{
				answer[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << answer[i][j] << " ";
	}

	return answer;
}

int** addMatrix(int** matrix1, int** matrix2, int m)
{
	int** temp = new int*[m];

	for (int i = 0; i < m; i++)
	{
		temp[i] = new int[m];
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}

	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << temp[i][j] << " ";
		}
		cout << endl;
	}*/
	return temp;
}

int** subtract(int** matrix1, int** matrix2, int m)
{
	int** temp = new int*[m];

	for (int i = 0; i < m; i++)
	{
		temp[i] = new int[m];
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}

	/*for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << temp[i][j] << " ";
		}
		cout << endl;
	}*/

	return temp;
}

int** divideAndConquer(int** matrix1, int** matrix2, int** result, int m)
{
	int newSize = m / 2;

	int** A11 = new int*[newSize];
	int** A12 = new int*[newSize];
	int** A21 = new int*[newSize];
	int** A22 = new int*[newSize];
	int** B11 = new int*[newSize];
	int** B12 = new int*[newSize];
	int** B21 = new int*[newSize];
	int** B22 = new int*[newSize];
	int** C11 = new int*[newSize];
	int** C12 = new int*[newSize];
	int** C21 = new int*[newSize];
	int** C22 = new int*[newSize];

	for (int i = 0; i < newSize; i++)
	{
		A11[i] = new int[newSize];
		A12[i] = new int[newSize];
		A21[i] = new int[newSize];
		A22[i] = new int[newSize];
		B11[i] = new int[newSize];
		B12[i] = new int[newSize];
		B21[i] = new int[newSize];
		B22[i] = new int[newSize];
		C11[i] = new int[newSize];
		C12[i] = new int[newSize];
		C21[i] = new int[newSize];
		C22[i] = new int[newSize];
	}

	for (int i = 0; i < newSize; i++)
	{
		for (int j = 0; j < newSize; j++)
		{
			A11[i][j] = matrix1[i][j];
			A12[i][j] = matrix1[i][j + newSize];
			A21[i][j] = matrix1[i + newSize][j];
			A22[i][j] = matrix1[i + newSize][j + newSize];
			B11[i][j] = matrix2[i][j];
			B12[i][j] = matrix2[i][j + newSize];
			B21[i][j] = matrix2[i + newSize][j];
			B22[i][j] = matrix2[i + newSize][j + newSize];
		}
	}

	if (m == 2)
	{
		result[0][0] = matrix1[0][0] * matrix2[0][0];
	}

	else
	{
		C11 = addMatrix(divideAndConquer(A11, B11, result, newSize), divideAndConquer(A12, B21, result, newSize), newSize);
		C12 = addMatrix(divideAndConquer(A11, B12, result, newSize), divideAndConquer(A12, B22, result, newSize), newSize);
		C21 = addMatrix(divideAndConquer(A21, B11, result, newSize), divideAndConquer(A22, B21, result, newSize), newSize);
		C22 = addMatrix(divideAndConquer(A21, B12, result, newSize), divideAndConquer(A22, B22, result, newSize), newSize);
	}

	for (int i = 0; i < newSize; i++)
		for (int j = 0; j < newSize; j++)
		{
			result[i][j] = C11[i][j];
			result[i][j + newSize] = C12[i][j];
			result[i + newSize][j] = C21[i][j];
			result[i + newSize][j + newSize] = C22[i][j];
		}

	return result;
}

int** strassen(int** matrix1, int** matrix2, int** result, int m)
{
	if (m == 2)
	{
		result[0][0] = matrix1[0][0] * matrix2[0][0];
	}
	else
	{
		int newSize = m / 2;


		int** A11 = new int*[newSize];
		int** A12 = new int*[newSize];
		int** A21 = new int*[newSize];
		int** A22 = new int*[newSize];
		int** B11 = new int*[newSize];
		int** B12 = new int*[newSize];
		int** B21 = new int*[newSize];
		int** B22 = new int*[newSize];
		int** C11 = new int*[newSize];
		int** C12 = new int*[newSize];
		int** C21 = new int*[newSize];
		int** C22 = new int*[newSize];


		for (int i = 0; i < newSize; i++)
		{
			A11[i] = new int[newSize];
			A12[i] = new int[newSize];
			A21[i] = new int[newSize];
			A22[i] = new int[newSize];
			B11[i] = new int[newSize];
			B12[i] = new int[newSize];
			B21[i] = new int[newSize];
			B22[i] = new int[newSize];
			C11[i] = new int[newSize];
			C12[i] = new int[newSize];
			C21[i] = new int[newSize];
			C22[i] = new int[newSize];
		}

		for (int i = 0; i < newSize; i++)
		{
			for (int j = 0; j < newSize; j++)
			{
				A11[i][j] = matrix1[i][j];
				A12[i][j] = matrix1[i][j + newSize];
				A21[i][j] = matrix1[i + newSize][j];
				A22[i][j] = matrix1[i + newSize][j + newSize];
				B11[i][j] = matrix2[i][j];
				B12[i][j] = matrix2[i][j + newSize];
				B21[i][j] = matrix2[i + newSize][j];
				B22[i][j] = matrix2[i + newSize][j + newSize];
			}
		}

		int** P = strassen(addMatrix(A11, A22, newSize), addMatrix(B11, B22, newSize), result, newSize);
		int** Q = strassen(addMatrix(A21, A22, newSize), B11, result, newSize);
		int** R = strassen(A11, subtract(B12, B22, newSize), result, newSize);
		int** S = strassen(A22, subtract(B21, B11, newSize), result, newSize);
		int** T = strassen(addMatrix(A11, A12, newSize), B22, result, newSize);
		int** U = strassen(subtract(A21, A11, newSize), addMatrix(B11, B12, newSize), result, newSize);
		int** V = strassen(subtract(A12, A22, newSize), addMatrix(B21, B22, newSize), result, newSize);

		C11 = subtract(addMatrix(P, S, newSize), addMatrix(T, V, newSize), newSize);
		C12 = addMatrix(R, T, newSize);
		C21 = addMatrix(Q, S, newSize);
		C22 = subtract(addMatrix(P, R, newSize), addMatrix(Q, U, newSize), newSize);
	}

	return result;
}

int main()
{
	int** mat1 = new int*[n];
	int** mat2 = new int*[n];
	int** result = new int*[n];

	unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	for (int i = 0; i < n; i++)
	{
		mat1[i] = new int[n];
		mat2[i] = new int[n];
		result[i] = new int[n];
	}

	//for (int i = 0; i < 1000; i++)
	//{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mat1[i][j] = rand() % 10 + 1;
				mat2[i][j] = rand() % 10 + 1;
			}
		}

		/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << mat1[i][j] << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << mat2[i][j] << " ";
			}
			cout << endl;
		}*/

		for (int i = 0; i < 20; i++)
		{
			originMultiply(mat1, mat2, result);
			//divideAndConquer(mat1, mat2, result, n);
			//strassen(mat1, mat2, result, n);
		}
	//}
	unsigned __int64 done = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	cout << done - now;
}