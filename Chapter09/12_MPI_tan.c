/******************************** 
 * *** MPI tangent(x) code. *** *
 *                              *
 * Composite Taylor series      *
 * representation of the tan(x) *
 * function.                    * 
 *                              *
 * Author: Carlos R. Morrison   *
 *                              *
 * Date: 1/10/2017              *
 ********************************/

#include <mpi.h>   // (Open)MPI library
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(int argc, char*argv[])
{
/******************************************************************************/
  unsigned int i,j,l;
  unsigned long int k,m,n;
  long long int B,D,G,I; 
  int Q = 17,rank,length,numprocs;
  float x,y;
  double sum,sum1,sum2,sum01=0,sum02=0,rank_sum,rank_sum1,rank_sum2;
  double A,C,E,F,H,J;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  MPI_Init(&argc, &argv);                    // initiates MPI
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);  // acquire number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);      // acquire current process id
  MPI_Get_processor_name(hostname, &length); // acquire hostname
/******************************************************************************/
 
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
 Z: printf("Enter angle(deg.):\n");
    printf("\n");
    scanf("%f",&y);

    if(y >= 0 && y < 90.0) 
    {      
      x = y*(M_PI/180.0);
    }
    else
    if(y > 90.0 && y <= 180.0)
    {
      x = -(180.0-y)*(M_PI/180.0);
    }
    else
    if(y >= 180.0 && y < 270)
    {      
      x = -(180-y)*(M_PI/180.0);
    }
    else
    if(y > 270.0 && y <= 360)
    {      
      x = -(360.0-y)*(M_PI/180.0);
    }
    else
    {
      printf("\n");
      printf("Bad input !! Please try another angel\n");
      printf("\n");
      goto Z;
    }
  }// End of if(rank == 0) 
/******************************************************************************/

// broadcast input items "Q" & "x" to all processes.
  MPI_Bcast(&Q, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

// this loop increments the maximum number of iterations, thus providing
// additional work for testing computational speed of the processors  
//  for(total_iter = 1; total_iter < Q; total_iter++)  
  {
    sum01 = 0;
    sum02 = 0;
//    for(total_iter = 1; i < total_iter; total_iter++)  
    for(i = rank + 1; i <= Q; i += numprocs)
    {
      m = (i-1);   
     /*************************************************
      *             ***** SINE BLOCK *****            *
      *************************************************/
      A = (double)pow(-1,m);
      B = 2*m+1;
      C = (double)pow(x,B);

      D = 1;
      for(j = 1; j <= B; j++)
      {
        D *= j; 
      }
 
      E = (A*C)/(double)D;
    
      sum01 += E;

     /*****************************************************
      *            ***** COSINE BLOCK *****               *
      *****************************************************/ 
      F = (double)pow(-1,m);
      G = 2*m;
      H = (double)pow(x,G);

      I = 1;
      for(l = 1; l <= G; l++)
      {
        I *= l; 
      }
 
      J = (F*H)/(double)I;
    
      sum02 += J;
    }// End of for(i = rank + 1; i <= Q; i += numprocs)

    rank_sum1 = sum01;
    rank_sum2 = sum02;  
          
// collect and add the partial sum0 values from all processes
    MPI_Reduce(&rank_sum1, &sum1, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&rank_sum2, &sum2, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
  }//End of for(total_iter = 1; total_iter < n; total_iter++)
  
  if(rank == 0)
  {
    sum = sum1/sum2;// Tan(x) ==> Sine(x)/Cos(x)
    printf("\n");
    printf("%.1f deg. = %.3f rads\n", y, x); 
    printf("Tan(%.1f) = %.3f\n", y, sum);
  } 

// clean up, done with MPI
  MPI_Finalize();
 
  return 0;
}// End of int main(int argc, char*argv[])


