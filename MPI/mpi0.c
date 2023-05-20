#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){
   int my_id, nproc, tag = 99, source;
  
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   MPI_Comm_size(MPI_COMM_WORLD, &nproc);

   printf("I am processor %d from a total of %d\n",my_id,nproc);

   MPI_Finalize();
}
