/****************************************** 
 *    *** Nilakantha MPI pi code. ***     *
 *                                        *
 * This infinate series calculates pi     *  
 * using MPI. It converges slowely,       *
 * requiring 750 iterations for 9 decimal *
 * place accuracy.                        *
 *                                        *
 * Author: Carlos R. Morrison             *
 *                                        *
 * Date: 1/14/2017                        *
 ******************************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
  int total_iter;
  int n,rank,length,numprocs,i,j,k;
  double sum,sum0,rank_integral,A,B,C;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);                    // initiates MPI
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);  // acquire number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // acquire current process id
  MPI_Get_processor_name(hostname, &length); // acquire hostname

  if (rank == 0)
  {
    printf("\n");
    printf("#######################################################");  
    printf("\n\n");
    printf("Master node name: %s\n", hostname); 
    printf("\n");
    printf("Enter the number of intervals:\n");
    printf("\n");
    scanf("%d",&n);
    printf("\n");
  }

// broadcast the number of iterations "n" to all processes.
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

// this loop increments the maximum number of iterations, thus providing
// additional work for testing computational speed of the processors   
//  for(total_iter = 1; total_iter < n; total_iter++) 
  {
    sum0 = 0.0;
//    for(i = rank + 1; i <= total_iter; i += numprocs)
    for(i = rank + 1; i <= n; i += numprocs)
    { 
      j = i-1;
      k = (2*j+1);
    
      A = (double)pow(-1,j+2);
      B = 4.0/(double)((k+1)*(k+2)*(k+3));
      C = A * B;

      sum0 += C;
    }
 
    rank_integral = sum0;// Partial sum for a given rank

//  collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_integral, &sum, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);

  } // End of for(total_iter = 1; total_iter < n; total_iter++)
    // printf("Process %d on %s has the partial result of %.16f \n",rank,hostname,
    //                                                              rank_integral);

  if(rank == 0)
  {
    printf("\n\n");
    printf("*** Number of processes: %d\n",numprocs);
    printf("\n\n");
    printf("     Calculated pi = %.30f\n", (3+sum));
    printf("              M_PI = %.30f\n", M_PI);    
    printf("    Relative Error = %.30f\n", fabs((3+sum)-M_PI));
    printf("\n");
  }

// clean up, done with MPI
  MPI_Finalize();

  return 0;  
}

