#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
pthread_mutex_t mtx;
#define N 4
#define TERMS 3
double x[N] = {0, M_PI/6., M_PI/3., 0.134};
double res[N];

void *TaskCode(void* argument) {
	int tid;
	tid = *((int*) argument);

	for ( int i = 0 ; i < N ; i++ ) {
		double value = x[i];
		double numer = x[i]*x[i]*x[i];
		double denom = 6.;
		int sign = -1;
		for ( int j = 1 ; j <= TERMS ; j++ ) {
			value += (double)sign * numer / denom;
			numer *= x[i]*x[i];
			denom *= (2.*(double)j+2.)*(2.*(double)j+3.);
			sign *= -1;
		}
		pthread_mutex_lock(&mtx);
		res[i] = value;
		pthread_mutex_unlock(&mtx);
	}	

	return NULL;
}
int main() {
	pthread_t threads[4];
	int args[4];
	int i;
	
	pthread_mutex_init(&mtx, NULL);
	for ( i = 0 ; i < 4 ; ++i) {
		args[i] = i;
		pthread_create(&threads[i], NULL, TaskCode, (void*)&args[i]);
	}
	for ( int i = 0 ; i < 4 ;++i) {
		pthread_join(threads[i], NULL);
	}
	for ( i = 0 ; i < 4 ; i++ ) { 
		printf("sin(%.2f) by Taylor series = %f\n",x[i], res[i]);
		printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
	}
	return 0;
}
