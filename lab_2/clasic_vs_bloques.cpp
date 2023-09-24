#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

void initialize_matrix(double **&A, int MAX){
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

void fill_matrix_with_ceros(double **A, int MAX){
    for (int i=0;i<MAX;i++)
        for(int j=0;j<MAX;j++)
            *(*(A+i)+j)=0;
}

void classical_matrix_multiplication(double **A, double **B, double **C, int MAX){
    fill_matrix_with_ceros(C,MAX);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=0;i<MAX;i++)
        for (int j=0;j<MAX;j++)
            for (int k=0;k<MAX;k++)
                *(*(C+i)+j) += *(*(A+i)+k) * *(*(B+k)+j);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout<<"Costo de la multiplicacion clasica medido en tiempo: "<<duration.count()<<endl; 
}

void block_matrix_multiplication(double **A, double **B, double **C, int b, int MAX){
    fill_matrix_with_ceros(C,MAX);
    auto start = std::chrono::high_resolution_clock::now();
    for (int ii=0;ii<MAX;ii+=b)
        for (int jj=0;jj<MAX;jj+=b)
            for (int kk=0;kk<MAX;kk+=b)
                for (int i = ii; i < ii+b; i++) 
                    for (int j = jj; j < jj+b; j++)
                        for (int k = kk; k < kk+b; k++)
                            *(*(C+i)+j) += *(*(A+i)+k) * *(*(B+k)+j);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout<<"Costo de la multiplicacion por bloques medido en tiempo: "<<duration.count()<<endl; 
}

int main(){
    int MAX = 40;
    double **A, **B, **C;
     // inicializacion de matrices
    initialize_matrix(A,MAX);
    initialize_matrix(B,MAX);
    initialize_matrix(C,MAX);
    // llenado de datos
    fill_matrix(A,MAX);
    fill_matrix(B,MAX);

    //COMPARACION
    classical_matrix_multiplication(A,B,C,MAX);
    block_matrix_multiplication(A,B,C,MAX/2, MAX);
    block_matrix_multiplication(A,B,C,MAX/5, MAX);
    block_matrix_multiplication(A,B,C,MAX/10, MAX);
      
    return 0;
}
