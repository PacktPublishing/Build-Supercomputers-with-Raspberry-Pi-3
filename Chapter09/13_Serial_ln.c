/******************************** 
 *  *** Serial ln(x) code ***   *
 *                              *
 * Taylor series representation *
 * of the trigonometric ln(x).  * 
 *                              *
 * Author: Carlos R. Morrison   *
 *                              *
 * Date: 1/10/2017              *
 ********************************/

#include <math.h>
#include <stdio.h>

int main(void)
{
  unsigned int n;
  unsigned long int k;
  double A,B,C; 
  double sum=0;
  long int num_loops;
  float x,y;
    
/******************************************************/
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
/******************************************************/ 
   
  sum = 0;
  for(k = 1; k < n; k++)
  {    
    A = 1.0/(double)(2*k-1);
    B = pow(((x-1)/(x+1)),(2*k-1));
    C = A*B;
    
    sum += C;
  }
  
  printf("\n");
  printf("ln(%.1f) = %.16f\n", y, 2.0*sum);
  printf("\n");

  return 0;
}


