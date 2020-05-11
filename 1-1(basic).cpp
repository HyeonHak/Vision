//나이브 코드 예시

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cuda.h>
#include <vector>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define TILE_WIDTH 8
#define SIZE 150

class Timer {
	struct timespec s_;
public:
	clock_t start, end;
	Timer() { tic(); }
	void tic() {
		start = clock();
	}

	double toc() {
		end = clock();
		return (double)(end - start);
	}
};

// Please optimize this function
void matmult(int m, int n, int k, const float* mat_a, const float* mat_b, float* mat_c)
{
	/*
		== input ==
		mat_a: m x k matrix
		mat_b: k x n matrix

		== output ==
		mat_c: m x n matrix (output)
	*/
	
	for (int i1 = 0; i1 < m; i1++) {
		for (int i2 = 0; i2 < n; i2++) {
			mat_c[n*i1 + i2] = 0;
			for (int i3 = 0; i3 < k; i3++) {
				mat_c[n*i1 + i2] += mat_a[i1 * k + i3] * mat_b[i3 * n + i2];
			}
		}
	}
}

void genmat(int n, int m, std::vector<float>& mat)
{
	srand(time(0));
	mat.resize(n * m);
	for (int i = 0; i < mat.size(); i++) mat[i] = rand() % 100;
}

void dumpmat(int n, int m, std::vector<float>& mat)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%f ", mat[i * m + j]);
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	std::vector<float> mat_a;
	std::vector<float> mat_b;
	std::vector<float> mat_c;

	genmat(SIZE, SIZE, mat_a);
	genmat(SIZE, SIZE, mat_b);
	genmat(SIZE, SIZE, mat_c);

	Timer t;

	double elapsed = 0;
	const int iteration = 10000;
	for (int i = 0; i < iteration; i++)
	{
		t.tic();
		matmult(SIZE, SIZE, SIZE, &mat_a[0], &mat_b[0], &mat_c[0]);
		elapsed += t.toc();
	}

	dumpmat(SIZE, SIZE, mat_a);
	dumpmat(SIZE, SIZE, mat_c);
	elapsed /= (CLOCKS_PER_SEC);
	printf("%lf s\n", elapsed);
	return 0;
}