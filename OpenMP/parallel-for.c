#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    int N = 100;
    int i;    

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        printf("Thread %d: i = %d\n", omp_get_thread_num(), i);
    }
    
    return 0;
}
