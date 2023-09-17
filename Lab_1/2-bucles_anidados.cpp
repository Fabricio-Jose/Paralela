#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

void init_matrix(double **&A, int MAX){
    A = new double*[MAX];
    for( int i=0; i<MAX; i++ )
        A[i] = new double[MAX];
}

void fill_matrix(double **A,int MAX){
    srand(time(NULL));
    for (int i=0;i<MAX;i++)
        for (int j=0;j<MAX;j++)
            *(*(A+i)+j)=1+rand()%(11-1);
}

void fill_vector(double *x, int MAX){
    for (int i=0;i<MAX;i++)
        *(x+i)=1+rand()%(11-1);
}

void fill_vector_with_ceros(double *y, int MAX){
    for (int i=0;i<MAX;i++)
        *(y+i)=0;
}

int main(){
    int MAX = 10000;
    double **A;
    double *x = new double[MAX]; 
    double *y = new double[MAX];
    // inicializamos la matriz
    init_matrix(A,MAX);
    // llenado de datos de matriz y vector a multiplicar
    fill_matrix(A,MAX);
    fill_vector(x,MAX);

    // VS de tiempos
    // primer par de bucles anidados
    fill_vector_with_ceros(y,MAX);
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j]*x[j];
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float,std::milli> duration1 = end1 - start1;
    cout<<"Tiempo bucle 1: "<<duration1.count()<<endl<<endl;

    // segundo par de bucles anidados
    fill_vector_with_ceros(y,MAX);
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i][j]*x[j];
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float,std::milli> duration2 = end2 - start2;
    cout<<"Tiempo bucle 2: "<<duration2.count()<<endl<<endl;
    
    return 0;
}
