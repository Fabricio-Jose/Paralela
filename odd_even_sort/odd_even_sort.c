#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int RMAX=100000;

void Generate_list(int a[],int n);
void Odd_even_sort(int a[],int n);

int main(int argc,char*argv[]) {
    int n,local_n;
    int *a,*local_a;

    int my_rank, p;

    MPI_Comm comm;
                            
    MPI_Init(&argc,&argv);
    comm = MPI_COMM_WORLD;

    MPI_Comm_size(comm,&p);
    MPI_Comm_rank(comm,&my_rank);

    n = atoi(argv[0]);

    a = (int*) malloc(n*sizeof(int));
    Generate_list(a,n);

    Odd_even_sort(a,n);

    free(a);
    return 0;

}

void Generate_list(int a[], int n){
    int i;
    srandom(0);
    for(i=0;i<n;++i)
        a[i] = random()%RMAX;
}

void Odd_even_sort(int a[],int n){
    int phase, i,temp;
    for(phase=0;phase<n;phase++){
        if(phase%2 == 0){
            for(i=1;i<n;i+=2){
                if(a[i-1] > a[i]){
                    temp = a[i];
                    a[i] = a[i-1];
                    a[i-1]=temp;
                }
            }
        }
        else{
            for(i=1;i<n-1;i+=2){
                if(a[i] > a[i+1]){
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                }
            }
        
        }
    }
}
