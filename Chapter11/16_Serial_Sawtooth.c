/*********************************** 
 * *** Serial sawtooth(x) code *** *
 *                                 *
 * Fourier series representation   *
 * of the sawtooth(x) function.    * 
 *                                 *
 * Author: Carlos R. Morrison      *
 *                                 *
 * Date: 2/12/2017                 *
 ***********************************/
#include <math.h>  // math library
#include <stdio.h> // Standard Input / Output library

int main(void)
{
  int j;
  unsigned long int i;
  double sum0,sum1,A,B,C;
  double D[100]={0},x[100]={0},d,dd=10.00,o,oo=10.0*(M_PI/180);
  float Amp;
  float g;
  int m,n,p=36;  
 
  printf("\n");
  printf("#######################################################");
  printf("\n\n");
   
  printf("Enter number of iterations:\n");      
  scanf("%d",&n);
  printf("\n");

  x[0] = 0;
  D[0] = 0;
  o  = 0;
  d  = 0;
 
  for(j = 0; j <= p; j += 1)
  {
    o += oo;// rads
    d += dd;// deg
    x[j+1] = o;
    D[j+1] = d;
  }

  printf("\n"); 
  printf("Enter amplitude:\n");   
  scanf("%f",&Amp);
  printf("\n");

  printf("Enter frequency(Hz.):\n");   
  scanf("%f",&g);
  printf("\n");

  for(m = 0; m <= p; m++)
  {
    sum0 = 0.0;            
    for(i = 1; i <= n; i++)
    { 
      A = 1.0/(double)i;
      B = sin(i*g*x[m]);
    
      C = A*B;
      
      sum0 += C; 
    }// End of for(i = 1; i <= n; i++)

    sum1 = Amp*(0.5-(1.0/M_PI)*sum0);       
    printf("  x = %.3f rad,  Amp. = %.3f,  Deg. = %.1f\n",x[m],sum1,D[m]);
  }// End of for(m = 1; m <= p; m++)
                
  return 0;  
}

























