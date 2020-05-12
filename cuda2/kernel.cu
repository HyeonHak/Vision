//나이브 코드 예시

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cuda.h>
#include <vector>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define TILE_WIDTH 8
#define SIZE 512

void MatrixMultiplication(const float* M, const float* N, float* P, int Width);
__global__ void MatrixMulKernel(float* Md, float* Nd, float* Pd, int Width);

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

	MatrixMultiplication(mat_a, mat_b, mat_c, SIZE);
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

void MatrixMultiplication(const float* M, const float* N, float* P, int Width) {
	int size = Width * Width * sizeof(int);
	float *Md, *Nd, *Pd;


	// Transfer M and N to device memory
	cudaMalloc((void**)&Md, size);
	cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&Nd, size);
	cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);

	// Allocate P on the device
	cudaMalloc((void**)&Pd, size);

	// Setup the execution configuration
	dim3 dimGrid(Width, Width);
	dim3 dimBlock(Width, Width);

	// Launch the device computation threads!
	MatrixMulKernel << <dimGrid, dimBlock >> > (Md, Nd, Pd, Width);

	// Transfer P from device to host
	cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);
	// Free device matrices
	cudaFree(Md);
	cudaFree(Nd);
	cudaFree(Pd);

}


__global__ void MatrixMulKernel(float* Md, float* Nd, float* Pd, int Width) {
	// Calculate the row index of the Pd element and M
	int Row = blockIdx.y * blockDim.y + threadIdx.y;
	// Calculate the column index of Pd and N
	int Col = blockIdx.x * blockDim.x + threadIdx.x;

	int Pvalue = 0;
	// each thread computes one element of the bolck sub-matrix
	for (int k = 0; k < Width; ++k)
		Pvalue += Md[Row * Width + k] * Nd[k * Width + Col];

	Pd[Row * Width + Col] = Pvalue;
}