#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>


using namespace std::chrono;

#define N 10

const int n=N;

struct v
{
    size_t i;
    size_t j;
};

double A[N][N];
double B[N]; 
double C[N];

double random(double i, double j) {
   return ((double(3.5)*j)/double(2.14253) * i);
}

void regenate_matrices(){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = random(i+0.12,j+0.23);
            }}
    for (int i = 0; i < N; i++) {
        B[i] = random(i+0.61,0.213);
    }
}

auto get_time() {
	return std::chrono::high_resolution_clock::now();
}


static void * multiplication(void *arg){
    struct v *data = (struct v *)arg;

    size_t l;    
    for(l=0; l < N; l++){
        size_t i=(data[l]).i;
        size_t j=(data[l]).j;
        double sum=0;
        size_t d;

        for (d = 0; d < N; d++){
            sum = sum + A[i][d]*B[d];
        }
        C[i] = sum;
        sum = 0;
    }
    return 0;}
    

int main(void)
{
    pthread_t threads[n];
    size_t i, k;

    struct v **data;
    data = (struct v **)malloc(n * sizeof(struct v*));

    regenate_matrices();

    auto mkl_t1 = get_time();

    for(i = 0; i < n; i++){
        data[i] = (struct v *)malloc(n * sizeof(struct v));
        for(k = 0; k < n; k++){
            data[i][k].i = i;
            data[i][k].j = k;}
        pthread_create(&threads[i], NULL, multiplication, data[i]);
    }

    auto mkl_t2 = get_time();
    printf("Execution time in seconds\n");
	auto mkl_time_span1 = duration_cast<duration<double>>(mkl_t2 - mkl_t1);
    printf("%lf\t", mkl_time_span1.count());printf("s");printf("\n");

    double FLOPS=(N*N)/mkl_time_span1.count();
    printf("\nExecution rate (operations per second): \n");
    printf("%lf\t", FLOPS);



    for(i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\n\nThe result of the multiplication is: \n");
    for (i = 0; i < N; i++)
    {
        printf("%lf\t", C[i]);printf("\n");
        }
    
        
}
