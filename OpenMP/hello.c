#include <stdio.h>
#include <omp.h>

int main(int arg, char** argsv) {
	#pragma omp parallel
	{
		printf("Hello from thread %d!\n", omp_get_thread_num());
	}

	return 0;
}
