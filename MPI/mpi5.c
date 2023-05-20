// Ejemplo de Comunicacion Asincrona
//
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#define LIM 10
main (int argc, char *argv[]) {
  double inicio,final;
  int i,error, MyId, p;
  int termino,
  buff[LIM]={10,20,30,40,50,60,70,80,90,100};
  MPI_Status status[LIM];
  MPI_Request reque[LIM];
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyId);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  if (p != 2) {
    fprintf(stderr,"Este programa solo funciona con dos (2) procesadores  ");
    MPI_Finalize();
    exit(1);
  }
  if (MyId == 0)
  { 
    inicio=MPI_Wtime();
    printf("Antes: %lf\n",inicio);
    for (i=0;i<LIM;i++) 
    {
         MPI_Isend(&(buff[i]), 1, MPI_INT, 1, 111,
MPI_COMM_WORLD,&(reque[i]));
         final=MPI_Wtime();
         printf("%d,Despues  del %d, %lf\n",MyId,i,final);
    } 
    printf("Soy el proceso %d, y envie:\n", MyId);
    for (i=0;i<LIM;i++) 
         printf("{%d,%d}",MyId,buff[i]);
    MPI_Waitall(LIM,reque,status);
    final=MPI_Wtime();
    final=MPI_Wtime();
    printf("Soy el proceso %d, voy a finalizar \n", MyId,final);
  } else
    {  
    inicio=MPI_Wtime();
    printf("%lf\n",inicio);
    for (i=0;i<LIM;i++) 
    {
        buff[i]=5555;  
        MPI_Irecv(&(buff[i]),1,MPI_INT, 0, 111,
MPI_COMM_WORLD,&(reque[i]));
        printf("Proceso %d, buff[%d]= %d \n",MyId,i,buff[i]);
   }
//  
// MPI_Test(&(reque[4]),&termino,&(status[4]));
    MPI_Wait(&(reque[3]),&(status[4]));
 
           printf("Proceso %d, recibio 4to. mensaje \n", MyId); 

    for (i=0;i<LIM;i++) 
      printf("{%d,%d}",MyId,buff[i]);
 }
  MPI_Finalize();
  exit(0);
}
