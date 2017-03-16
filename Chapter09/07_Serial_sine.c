/******************************** 
 * *** Serial sine(x) code ***  *
 *                              *
 * Taylor series representation *
 * of the sine(x) functon.      * 
 *                              *
 * Author: Carlos R. Morrison   *
 *                              *
 * Date: 1/10/2017              *
 ********************************/

#include <math.h>
#include <stdio.h>

int main(void)
{
  unsigned int j;
  unsigned long int k;
  long long int B,D; 
  int num_loops = 17;
  float y;
  double x;
  double sum0=0,A,C,E;
  
/******************************************************/
  printf("\n");
  printf("Enter angle(deg.):\n");
  printf("\n");
  scanf("%f",&y);
  if(y <= 180.0)
  {      
    x = y*(M_PI/180.0);
  }
  else
  x = -(360.0-y)*(M_PI/180.0);
/******************************************************/ 
   
  sum0 = 0;
  for(k = 0; k < num_loops; k++)
  {    
    A = (double)pow(-1,k);// (-1^k)
    B = 2*k+1;
    C = (double)pow(x,B);

    D = 1;
    for(j=1; j <= B; j++)// (2k+1)!
    {
      D *= j; 
    }
 
    E = (A*C)/(double)D;
    
    sum0 += E;
  }
  
  printf("\n");
  printf(" %.1f deg. = %.3f rads\n", y, x);
  printf("Sine(%.1f) = %.4f\n", y, sum0);

  return 0;
}














