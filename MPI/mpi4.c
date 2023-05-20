#include "mpi.h"
#include <stdio.h>
#include <math.h>
#define lim 20
/*Arreglo que sera dividido en cuatro procesos */
int buf[lim]=
{27,65,3,8,45,10,50,95,10,11,9,48,69,25,19,29,61,42,93,20};
int buf2[5];
int buf3[4];
int max;
int main(int argc, char *argv[])
{
int n, myid, numprocs, i;
int namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&myid);
MPI_Get_processor_name(processor_name,&namelen);
printf("Proceso %d \n",myid);
n=lim/numprocs;
MPI_Scatter(buf,n, MPI_INT,buf2,n,MPI_INT, 0, MPI_COMM_WORLD);
for (i=0; i<n ; i++)
printf("Proceso %d Buf2[%d]= %d \n", myid, i, buf2[i]);
MPI_Reduce(buf2,buf3,n, MPI_INT, MPI_MAX, 0,MPI_COMM_WORLD);
if (myid == 0)
{ max = buf3[0];
for (i=1; i<n ; i++)
if (max < buf3[i]) max = buf3[i]; 
for (i=0; i<n ; i++)
printf("Buf3[%d]= %d \n", i, buf3[i]);
printf("El maximo del arreglo es : %d ", max);
}
MPI_Finalize();
return 0;
}





