/************************************* 
 *     *** Serial pi code.  ***      *
 *                                   *
 * This program calculates pi using  *
 * serial computing.                 * 
 *                                   *
 * Author: Carlos R. Morrison        *
 *                                   *
 * Date: 7/14/2017                   *
 *************************************/

#include <math.h>
#include <stdio.h>


int main(void)
{
  long num_rects = 300000;//1000000000;
  long i;
  double x,height,width,area;
  double sum;
 
  width = 1.0/(double)num_rects; // width of a segment
  
  sum = 0;
  for(i = 0; i < num_rects; i++)
  {
    x = (i+0.5) * width; // x: distance to center of i(th) segment
    height = 4/(1.0 + x*x);
    sum += height; // sum of individual segment height   
  }
  
// approximate area of segments (Pi value) 
  area = width * sum;
  
  printf("\n");
  printf(" Calculated Pi = %.16f\n", area);
  printf("          M_PI = %.16f\n", M_PI);
  printf("Relative error = %.16f\n", fabs(area - M_PI));
  printf("\n");
  return 0;
}

