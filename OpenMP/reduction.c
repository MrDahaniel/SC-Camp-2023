#include <stdio.h>

float product(float* a, float* b, int N) {
    float sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    } 

    return sum;
}

int main(int argc, char** argsv) {
    int N = 1000;

    float a[N];
    float b[N];

    //    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    printf("Result %f\n", product(a, b, N)); 
}
