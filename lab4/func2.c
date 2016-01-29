#include "func.h"
#include "util.h"
#include <string.h>

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{ 
	const double result = 1/((double)(n));
    const double x_r = xr;
    const double y_r = yr;
    //long long start, end;
    //start = get_time();
    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        {
            int i;
	        for(i = 0; i < n; i++)
		        weights[i] = result;
        }
        #pragma omp section
        {
            int i;
            for(i = 0; i < n; i++)
    		    arrayX[i] = x_r;
        }
        #pragma omp section
        {
            int i;
            for(i = 0; i < n; i++)
		        arrayY[i] = y_r;
        }
    }
    //end = get_time();
    //printf("f0: %f\n", elapsed_time(start, end));
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;
    //long long start, end;

    //start = get_time();
    #pragma omp parallel for private(i)
   	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
    }
    //end = get_time();
    //printf("1: %f\n", elapsed_time(start, end));
    
    //start = get_time();
    #pragma omp parallel for private(index_X, index_Y, i, j)
    for(i = 0; i < n; i++){
        for(j = 0; j < Ones; j++){
   			index_X = round(arrayX[i]) + objxy[j*2 + 1];
   			index_Y = round(arrayY[i]) + objxy[j*2];
   			index[i*Ones + j] = fabs(index_X*Y*Z + index_Y*Z + iter);
            if(index[i*Ones + j] >= max_size)
   		        index[i*Ones + j] = 0;
        }
    }
    //end = get_time();
    //printf("2: %f\n", elapsed_time(start, end));

    //start = get_time();
    #pragma omp parallel for private(i)
    for(i = 0; i < n; i++){
   		probability[i] = 0;
        for(j = 0; j < Ones; j++) {
   			probability[i] += (pow((array[index[i*Ones + j]] - 100),2) -
   							  pow((array[index[i*Ones + j]]-228),2))/50.0;
   		}
   		probability[i] = probability[i]/((double) Ones);
   	}
    //end = get_time();
    //printf("3: %f\n", elapsed_time(start, end));
}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
    
    #pragma omp parallel for private(i)
	for(i = 0; i < n; i++)
   		weights[i] = weights[i] * exp(probability[i]);
    
    for(i = 0; i < n; i++)
        sumWeights += weights[i];
    
    #pragma omp parallel for private(i)
	for(i = 0; i < n; i++)
   		weights[i] = weights[i]/sumWeights;
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;
    
	for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   		estimate_y += arrayY[i] * weights[i];
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;
}

void func4(double *u, double u1, int n)
{
	int i;
    for(i = 0; i < n; i++) {
        u[i] = u1 + i/((double)(n));
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
    
    #pragma omp parallel for private(i, j) 
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}
    //long long start, end;
    //start = get_time();
    const double weight = 1/((double)(n));
    #pragma omp parallel for private(i)
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = weight;
	}
    //end = get_time();
    //printf("f5: %f\n", elapsed_time(start, end));
}
