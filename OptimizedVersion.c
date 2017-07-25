//
// Created by kasun on 7/24/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
double matrixMultiply(int n);
void transpose(double** arr,int size);
double* out;
double total;
double final_total;
double sdTotal;
double mean;
int n;
int actualSize;
double val;
double sd;
double result;
double a;
int main(int argc,char* argv[]) {
    n=strtol(argv[1],NULL,10);
    out=(double*) malloc(30 * sizeof(double));
    total=0.0;
    printf("Running code for 30 samples............");
    for(int i=0;i<30;i++){
        out[i]=matrixMultiply(n);
        total+=out[i];
    }

    mean=total/30.0;
    sdTotal=0.0;
    for(int i=0;i<30;i++){
        sdTotal+=(out[i]-mean)*(out[i]-mean)/29;
    }
    sd=sqrt(sdTotal);
    val=((100*1.960*sd)/(5*mean))*((100*1.960*sd)/(5*mean));
    actualSize=(int)ceil(val);

    free(out);
    final_total=0.0;

    printf("\nNo. of samples needed: %d",actualSize);
    printf("\nRunning code for %d samples",actualSize);
    for(int i=1;i<=actualSize;i++){
        final_total+=matrixMultiply(n);
    }

    result=final_total/actualSize;
    FILE *f= fopen("OptimizedVersion_results.csv","a+");
    fprintf(f,"%d,%lf\n",n,result);
    fclose(f);
    printf("\nResult=%lf\n",result);
}
double matrixMultiply(int n){
    int i,j;
    /*get the no of the threads from the command line*/

    double **matA = malloc(sizeof *matA *n);
    if (matA)
    {
        for (i = 0; i < n; i++)
        {
            matA[i] = malloc(sizeof *matA[i] * n);
        }
    }
    double **matB = malloc(sizeof *matB *n);
    if (matB)
    {
        for (i = 0; i < n; i++)
        {
            matB[i] = malloc(sizeof *matB[i] * n);
        }
    }
    double **matC = malloc(sizeof *matC *n);
    if (matC)
    {
        for (i = 0; i < n; i++)
        {
            matC[i] = malloc(sizeof *matC[i] * n);
        }
    }
    srand(time(NULL));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a=(double)rand()/1000000;
            matA[i][j]=a;
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a=(double)rand()/1000000;
            matB[i][j]=a;
        }
    }
    clock_t start=clock();
    transpose(matB,n);
    for(int i=0;i<n;i++){

        for(int j=0;j<n;j++){
            double sum=0.0;
            for(int k=0;k<n;k++){
                sum+=matA[i][k]*matB[j][k];
            }
            matC[i][j]=sum;
        }
    }

    clock_t end=clock();
    double seconds = (double)(end-start)/CLOCKS_PER_SEC;
    printf("\n%lf",seconds);
    free(matA);
    free(matB);
    free(matC);
    return seconds;
}

void transpose(double** arr,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            double temp=arr[i][j];
            arr[i][j]=arr[j][i];
            arr[j][i]=temp;
        }
    }
}
