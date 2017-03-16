/********************************************* 
 *   *** Fabrice_Bellard MPI pi code. ****   *
 *                                           *
 * This infinite series calculates pi using  *
 * MPI. It converges rapidly, requiring Only *
 * six iterations for 15 decimal place       *
 * accuracy                                  *
 *                                           *
 * Author: Carlos R. Morrison                *
 *                                           *
 * Date: 1/14/2017                           *
 *********************************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
  int total_iter;
  int n,rank,length,numprocs,i;
  double pi,sum,sum0,x,rank_sum,A,B,C,D,E,F,G,H,I;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  unsigned long factorial(unsigned long number);
  unsigned long k;
  double J = pow(2,-6);

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
    printf("Enter the number of iterations:\n");
    printf("\n");
    scanf("%d",&n);
    printf("\n");
  }

  // broadcast to all processes, the number of segments you want
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

  // this loop increments the maximum number of iterations, thus providing
  // additional work for testing computational speed of the processors   
//  for(total_iter = 1; total_iter < n; total_iter++) 
  {
    sum0 = 0.0;
//    for(i = rank + 1; i <= total_iter; i += numprocs)
    for(i = rank + 1; i <= n; i += numprocs)
    { 
      k = i-1;
      A = (double)pow(-1,k)/(double)pow(2,10*k);
      B = -(double)pow(2,5)/(double)(4*k+1);
      C = -1.0/(double)(4*k+3);
      D = (double)pow(2,8)/(double)(10*k+1);
      E = -(double)pow(2,6)/(double)(10*k+3);
      F = -(double)pow(2,2)/(double)(10*k+5);
      G = -(double)pow(2,2)/(double)(10*k+7);
      H = 1.0/(double)(10*k+9);
      I = A*(B+C+D+E+F+G+H);
      sum0 += I;
    }// End of for(i = rank + 1; i <= total_iter; i += numprocs)

    rank_sum = sum0;// Partial sum0 for a given rank

//  collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_sum, &sum, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);

  } // End of for(total_iter = 1; total_iter < n; total_iter++)
    
  if(rank == 0)
  {
    printf("\n\n");
    printf("*** Number of processes: %d\n",numprocs);
    printf("\n\n");
    pi = (J*sum);
    printf("     Calculated pi = %.16f\n", pi);
    printf("              M_PI = %.16f\n", M_PI);    
    printf("    Relative Error = %.16f\n", fabs(pi-M_PI));
    printf("\n");
  }

  // clean up, done with MPI
  MPI_Finalize();

  return 0;  
}// End of int main(int argc, char*argv[])

















