#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{ char nombre_maquina[MPI_MAX_PROCESSOR_NAME];
  int MyId, N, valor, largonombre;

  MPI_Init (&argc, &argv);
  
  MPI_Comm_rank (MPI_COMM_WORLD, &MyId); 
  MPI_Comm_size (MPI_COMM_WORLD, &N);
  srand(MyId);
  MPI_Get_processor_name(nombre_maquina,&largonombre); 
  valor= (rand() % 100);
  printf("Hola, soy el proceso %d, de un total de %d. Calcule %d. Estoy en %s\n",MyId,N,valor,nombre_maquina); 
  
  
  MPI_Finalize();
  
return 0;
}
 
