#include <stdio.h>
#include <mpi.h>

int main (int argc, char** argv){
   int my_id, nproc, tag = 99, source;
   MPI_Status status;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
   MPI_Comm_size(MPI_COMM_WORLD, &nproc);

   MPI_Send(&my_id, 1, MPI_INT, (my_id+1)%nproc, tag, 	
                   MPI_COMM_WORLD);
   int DoSomeWork();
   MPI_Recv(&source,1,MPI_INT,MPI_ANY_SOURCE,tag,
                  MPI_COMM_WORLD, &status);

   printf("%d recibio mensaje de %d\n",my_id,source);

   MPI_Finalize();
}
