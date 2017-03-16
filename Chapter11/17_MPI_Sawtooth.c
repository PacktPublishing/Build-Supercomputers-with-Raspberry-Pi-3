/********************************* 
 * *** MPI sawtooth(x) code ***  *
 *                               *
 * Fourier series representation *
 * of the sawtooth(x) function.  * 
 *                               *
 * Author: Carlos R. Morrison    *
 *                               *
 * Date: 2/13/2017               *
 *********************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
  long long int total_iter;
  int rank,length,numprocs,j;
  unsigned long int i;
  double sum,sum0,sum1,rank_integral,A,B,C;
  double D[100]={0},sm[100]={0},d,dd=10.00,x=0.0;
  float Amp,g;
  int m=0,n,p=36;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);                    // initiates MPI
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);  // acquire number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // acquire current process id
  MPI_Get_processor_name(hostname, &length); // acquire hostname
        
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
   
    printf("Enter number of iterations:\n");      
    scanf("%d",&n);
    printf("\n");

    D[0] = 0;
    d  = 0; 
    for(j = 0; j <= p; j += 1)
    {
      d += dd;// deg
      D[j+1] = d;
    }
     
    printf("Enter amplitude:\n");   
    scanf("%f",&Amp);
    printf("\n");

    printf("Enter frequency:\n");   
    scanf("%f",&g);
    printf("\n"); 
  }// End of if(rank == 0)

// broadcast g, n & x values to all processes.
Z:MPI_Bcast(&g, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

// this loop increments the maximum number of iterations, thus providing
// additional work for testing computational speed of the processors   
//for(total_iter = 1; total_iter < n; total_iter++)
  { 
    sum0 = 0.0;       
//  for(i = rank + 1; i <= total_iter; i += numprocs)
    for(i = rank + 1; i <= n; i += numprocs)
    {                             
      A = 1.0/(double)i;
      B = sin(i*g*x);
      C = A*B;     
         
      sum0 += C;// ==> Summation element of the Fourier series
    }// End of for(i = rank + 1; i <= n; i += numprocs)                                 
         
    rank_integral = sum0;// Partial sum for a given rank
           
//  collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_integral, &sum, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
           
  }// End of for(total_iter = 1; total_iter < n; total_iter++)
  
  m += 1;//counter for array angle D[]  
  if(rank == 0)
  {
    sum1 = Amp*(0.5-(1.0/M_PI)*sum);// Sawtooth function
    printf("  x = %.3f rad,  Amp. = %.3f,  Deg. = %.1f\n",x,sum1,D[m-1]);
  }// End of if(rank == 0)

  if(m <= p)
  {
    x += dd*(M_PI/180);// Angle (radians) accumulator
    goto Z;
  }
  
//clean up, done with MPI
  MPI_Finalize();

  return 0;  
}// End of int main(int argc, char*argv[])

























