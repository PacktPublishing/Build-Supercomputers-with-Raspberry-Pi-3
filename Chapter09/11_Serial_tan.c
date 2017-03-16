/********************************** 
 **** Serial tangent(x) code. *** *
 *                                *
 * Composite Taylor series        * 
 * representation of the tan(x)   *
 * function.                      * 
 *                                *
 * Author: Carlos R. Morrison     *
 *                                *
 * Date: 1/10/2017                *
 **********************************/

#include <math.h>
#include <stdio.h>

int main(void)
{
/************************************************/
  unsigned int i,j,l;
  unsigned long int k;
  long long int B,D,G,I; 
  int num_loops = 17;
  float y;
  double x;
  double sum=0,sum01=0,sum02=0;
  double A,C,E,F,H,J;
/************************************************/

/************************************************/
  printf("\n");
Z:printf("Enter angle(deg.):\n");
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
/*************************************************/

/*************************************************
 *             ***** SINE BLOCK *****            *
 *************************************************/ 
  sum01 = 0;
  for(i = 0; i < num_loops; i++)
  {    
    A = (double)pow(-1,i);
    B = 2*i+1;
    C = (double)pow(x,B);

    D = 1;
    for(j = 1; j <= B; j++)
    {
      D *= j; 
    }
 
    E = (A*C)/(double)D;
    
    sum01 += E;
  }// End of for(i = 0; i < num_loops; i++)

/*****************************************************
 *            ***** COSINE BLOCK *****               *
 *****************************************************/ 
  sum02 = 0;
  for(k = 0; k < num_loops; k++)
  {    
    F = (double)pow(-1,k);
    G = 2*k;
    H = (double)pow(x,G);

    I = 1;
    for(l = 1; l <= G; l++)
    {
      I *= l; 
    }
 
    J = (F*H)/(double)I;
    
    sum02 += J;
  }// End of for(k = 0; k < num_loops; k++)

/*****************************************************
 *            ***** TANGENT BLOCK *****              *
 *****************************************************/ 

    /*******************/  
     sum = sum01/sum02;  // Tan(x) ==> Sine(x)/Cos(x)
    /*******************/

/*****************************************************/
  printf("\n");
  printf("%.1f deg. = %.3f rads\n", y, x); 
  printf("Tan(%.1f) = %.3f\n", y, sum);
  
  return 0;
}


