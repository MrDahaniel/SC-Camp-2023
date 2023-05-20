#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#define LIM 10
int main (int argc, char *argv[]) {
  int i,error, MyId, N;
  int buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status;
  MPI_Init (&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &N);
  if (N != 2) {
    printf("Este programa solo funciona con dos (2) procesos. Coloque -NP 2");
    MPI_Finalize();
    exit(1);
  }

  if (MyId == 0)
  { 
    MPI_Send(buff, LIM, MPI_INT, 1, 111, MPI_COMM_WORLD);
    printf("Soy el proceso %d, y envie:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    MPI_Recv(buff, LIM, MPI_INT, 1, 222, MPI_COMM_WORLD, &status);
    printf("Soy el proceso %d, y recibi los mensajes:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");

  } else
    {  
    MPI_Recv(buff, LIM, MPI_INT, 0, 111, MPI_COMM_WORLD, &status);
    printf("Soy el proceso %d, y recibi:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
    for (i=0;i<LIM;i++) 
      buff[i]++; 
    MPI_Send(buff, LIM, MPI_INT, 0, 222, MPI_COMM_WORLD);
    printf("Soy el proceso %d, y envie:\n", MyId);
    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
    printf(" \n");
 }

  MPI_Finalize();
  exit(0);
}
