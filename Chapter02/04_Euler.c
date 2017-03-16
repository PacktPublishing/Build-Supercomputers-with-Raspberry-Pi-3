/***************************************** 
 *      *** Euler MPI pi code. ***       *
 *                                       *
 * This infinate series calculates pi    *
 * using MPI. It converges very slowely, *
 * requiring 7.6 million iterations for  *
 * eight decimal place accuracy.         *
 *                                       *
 * Author: Carlos R. Morrison            *
 *                                       *
 * Date: 1/14/2017                       *
 *****************************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
  int total_iter;
  int n,rank,length,numprocs,i;
  double sum,sum0,rank_integral,A;
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
//    for(i = rank + 1; i < total_iter; i += numprocs)
    for(i = rank + 1; i <= n; i += numprocs)
    {            
      A = 1.0/(double)pow(i,2);
      sum0 += A;
    }

//  Partial sum for a given rank   
	rank_integral = sum0;

//  collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_integral, &sum, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);

  } // End of for(total_iter = 1; total_iter < n; total_iter++)
    
  if(rank == 0)
  {
    printf("\n\n");
    printf("*** Number of processes: %d\n",numprocs);
    printf("\n\n");
    printf("     Calculated pi = %.30f\n", sqrt(6*sum));
    printf("              M_PI = %.30f\n", M_PI);    
    printf("    Relative Error = %.30f\n", fabs(sqrt(6*sum)-M_PI));
    printf("\n");
  }

// clean up, done with MPI
  MPI_Finalize();

  return 0;  
}

