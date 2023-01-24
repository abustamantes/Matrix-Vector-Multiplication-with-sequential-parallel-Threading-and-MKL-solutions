#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mkl.h"
#include <chrono>
#include <cstdlib>
#include <math.h>
#include <thread>

#define MAX 10
double matA[MAX][MAX];

using namespace std;
using namespace std::chrono;

double random(double i, double j) {
	return ((double(3.5) * j) / double(2.14253) * i);
}

template <class T>
void init_matrix(T* a, T value) {

	if (value == 1) {
		for (int i = 0; i < MAX; i++) {
			a[i] = random(i + 0.61, 0.213);
		}

	}
	if (value == 0) {
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				matA[i][j] = random(i + 0.12, j + 0.23);
			}
		}
		int k = 0;
		for (int i = 0;i < MAX;i++) {
			for (int j = 0;j < MAX;j++) {
				a[k] = matA[i][j];
				k++;
			}

		}

	}
}

auto get_time() {
	return std::chrono::high_resolution_clock::now();
}


int main()
{
	int m, n, k;
	m =k= MAX, n = 1;
	int size = m*k;
	
	double* A, * B, * C;
	
	double alpha, beta;	

	alpha = 1.0; beta = 0.0;
	printf(" Allocating memory for matrices aligned on 64-byte boundary for better \n"
		" performance \n\n");

	A = (double*)mkl_malloc(m * k * sizeof(double), 64);
	B = (double*)mkl_malloc(k * n * sizeof(double), 64);
	C = (double*)mkl_malloc(m * n * sizeof(double), 64);


	printf("Initialize the matrix A\n");
	init_matrix<double>(A,0);/*
	for (int i = 0;i < size;i++) {
		cout << A[i] << " ";
	}
	printf("\n");*/

	
	printf("\nInitialize the matrix B\n");
	init_matrix<double>(B,1);/*
	for (int i = 0;i < m;i++) {
		cout << B[i] << " "<<endl;
		}*/


	printf("\nResult of the multiplication\n");
	init_matrix<double>(C,2);

	
	//compute the execution time
	auto mkl_t1 = get_time();
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, k, B, n, beta, C, n);
	auto mkl_t2 = get_time(); 

	
	for (int i = 0;i < m;i++) {
		cout << C[i] << " " << endl;
	}

	printf("\n\n");
	auto mkl_time_span = duration_cast<duration<double>>(mkl_t2 - mkl_t1);
	cout << "Elapsed time MKL: " << mkl_time_span.count() << " s" << endl;

	double FLOPS = (MAX * MAX) / mkl_time_span.count();
	cout << "Execution rate (operations per second): " << FLOPS << endl;

	mkl_free(A);
	mkl_free(B);
	mkl_free(C);

	return 0;
	system("pause");