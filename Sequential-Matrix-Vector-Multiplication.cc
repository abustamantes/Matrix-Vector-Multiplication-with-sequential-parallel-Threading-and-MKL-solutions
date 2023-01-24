 #include <cstdlib>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int MAX=10;
 
double matA[MAX][MAX];
double matB[MAX];
double matC[MAX];
double matD[MAX];

double random(double i, double j) {
   return ((double(3.5)*j)/double(2.14253) * i);
}

double sequencial_multiplication(double matA[MAX][MAX],double matB[MAX]){
    for (int i = 0; i < MAX; i++)
      for (int j = 0; j < MAX; j++)
        matC[i] += matA[i][j] * matB[j];

    printf("Result of the multiplication: \n");
    for(int i=0;i<MAX;i++){
        cout<<matC[i]<<endl;
    }
    printf("\n");
    return 0;
}

auto get_time() {
	return std::chrono::high_resolution_clock::now();
}

int main()
{   
    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = random(i+0.12,j+0.23);
            }}
    for (int i = 0; i < MAX; i++) {
        matB[i] = random(i+0.61,0.213);
    }

/*
    printf("Matrix A: \n");
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matA[i][j]<<" ";
        cout<<endl;
    }
   
    printf("\nMatrix B: \n");
    for (int i = 0; i < MAX; i++) {
        cout << matB[i]<<endl;
    }
    printf("\n");*/ 

 
    if (true){

        auto mkl_t1 = get_time();
        sequencial_multiplication(matA,matB);
        auto mkl_t2 = get_time();

        //printf("Execution time\n");
        //printf("**************\n");
	    auto mkl_time_span = duration_cast<duration<double>>(mkl_t2 - mkl_t1);
	    cout << "Elapsed time for sequential code: " << mkl_time_span.count() << " s" << endl;
        //cout <<MAX<<","<<mkl_time_span.count()<< endl;
        double FLOPS=(MAX*MAX)/mkl_time_span.count();
        cout<<"Execution rate (operations per second): "<<FLOPS<<endl;

        }       
}