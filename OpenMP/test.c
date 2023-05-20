#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

    #pragma omp parallel num_threads(3) 
    {
        printf("Hello from process: %d\n", omp_get_thread_num());
    }

    printf("Bye!\n");


    return 0;
