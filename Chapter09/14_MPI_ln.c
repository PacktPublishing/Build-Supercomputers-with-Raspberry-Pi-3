/******************************** 
 *   *** MPI ln(x) code. ***    *
 *                              *
 * Taylor series representation *
 * of the trigonometric ln(x).  * 
 *                              *
 * Author: Carlos R. Morrison   *
 *                              *
 * Date: 1/10/2017              *
 ********************************/

#include<mpi.h> 
#include<math.h>
#include<stdio.h>

int main(int argc, char*argv[])
{
/******************************************************/
  long long int total_iter;
  unsigned int n;
  unsigned long int k;
  int rank,length,numprocs,i;
  float x,y;
  double sum,sum0,A,C,B,rank_sum;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);                    // initiates MPI
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);  // acquire number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // acquire current process id
  MPI_Get_processor_name(hostname, &length); // acquire hostname
/******************************************************/

  if(rank == 0)
  {
    printf("\n");
    printf("#######################################################");
    printf("\n\n");
    printf("*** Number of processes: %d\n",numprocs);
    printf("*** processing capacity: %.1f GHz.\n",numprocs*1.2); 
    printf("\n\n");
    printf("Master node name: %s\n", hostname); 
    printf("\n");
    printf("\n");
    printf("Enter the number of iterations:\n");
    printf("\n");
    scanf("%d",&n);
    printf("\n");
  Z:printf("Enter x value:\n");
    printf("\n");
    scanf("%f",&y);

    if(y > 0.0)
    {      
      x = y;
    }
    else
    {
      printf("\n");
      printf("Bad input !! Please try another value\n");
      printf("\n");
      goto Z;
    }
  }// End of if(rank == 0)

// broadcast input items "n" & "x" to all processes.
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

//this loop increments the maximum number of iterations, thus providing
//additional work for testing computational speed of the processors 
//for(total_iter = 1; total_iter < n; total_iter++) 
  {
    sum0 = 0.0;
//  for(i = rank + 1; i <= total_iter; i += numprocs)
    for(i = rank + 1; i <= n; i += numprocs)
    {    
      k = i;
                                                    
      A = 1.0/(double)(2*k-1);
      B = pow(((x-1)/(x+1)),(2*k-1));
      C = A*B;
                                       
      sum0 += C;
    }
                                                                 
    rank_sum = sum0;// Partial sum for a given rank
                                           
//  collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_sum, &sum, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
  }// End of for(total_iter = 1; total_iter < n; total_iter++)
                                                        
  if(rank == 0)
  {                     
    printf("\n");
    printf("ln(%.1f) = %.16f\n", y, 2.0*sum);
    printf("\n");
  }
                                                            
//clean up, done with MPI
  MPI_Finalize();
                          
  return 0;
}// End of int main(int argc, char*argv[])

















