/******************************************** 
 *          *** MPI pi code. ***            *
 *                                          *
 * This numerical integration calculates    *
 * pi using MPI. It converges very slowely, *
 * requiring 5 million iterations for       *
 * 48 decimal place accuracy.               *
 *                                          *
 * Author: Carlos R. Morrison               *
 *                                          *
 * Date: 1/14/2017                          *
 ********************************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
  int total_iter;
  int n, rank, length, numprocs, i;
  double mypi, pi, width, sum, x, rank_integral;
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
    printf("Enter number of segments:\n");
    printf("\n");
    scanf("%d",&n);
    printf("\n");
  }

// broadcast the number of segments "n" to all processes.
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

// this loop increments the maximum number of iterations, thus providing
// additional work for testing computational speed of the processors   
  for(total_iter = 1; total_iter < n; total_iter++) 
  {
    sum=0.0;
    width = 1.0 / (double)total_iter; // width of a segment
//    width = 1.0 / (double)n; // width of a segment
      
    for(i = rank + 1; i <= total_iter; i += numprocs)
//    for(i = rank + 1; i <= n; i += numprocs)
    {
      x = width * ((double)i - 0.5); // x: distance to center of i(th) segment
      sum += 4.0/(1.0 + x*x); // sum of individual segment height for a given rank
    }

// approximate area of segment (Pi value) for a given rank
    rank_integral = width * sum; 

// collect and add the partial area (Pi) values from all processes
    MPI_Reduce(&rank_integral, &pi, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);

  } // End of for(total_iter = 1; total_iter < n; total_iter++)

// printf("Process %d on %s has the partial result of %.16f \n",rank,hostname,
//                                                              rank_integral);

  if(rank == 0)
  {
    printf("\n\n");
    printf("*** Number of processes: %d\n",numprocs);
    printf("\n\n");
    printf("     Calculated pi = %.50f\n", pi);
    printf("              M_PI = %.50f\n", M_PI);    
    printf("    Relative Error = %.50f\n", fabs(pi-M_PI));
    printf("\n");
  }

  // clean up, done with MPI
  MPI_Finalize();
  return 0;  
}

