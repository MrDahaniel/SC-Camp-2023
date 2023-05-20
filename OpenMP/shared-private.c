#include <stdio.h>
#include <omp.h>

int main(int arg, char** argsv) {

    int shared = 0;

    #pragma omp parallel
    {
        int private = shared;
        
        shared++;

        printf("In thread %d I got %d and updated to %d\n", omp_get_thread_num(), private, shared); 
    }

    printf("\nEnd result:\n   shared: %d\n", shared);

}

