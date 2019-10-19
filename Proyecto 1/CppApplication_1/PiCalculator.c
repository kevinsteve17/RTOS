
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Utilities.h"

double factorial(int n)
{
  int c;
  double result = 1.0;
 
  for (c = 1; c <= n; c++)
    result = result * c;
 
  return result;
}


/**
 * pi = 6 * Arcsin(1/2) => serie: 6 * SumInfinita (1/2)^2n+1  2n!/[4^n * n! * 2n+1]  
 * @return 
 */
void CalculatePi(int workload)
{
    double realPi = 3.14159265359;
    double result = 0.0;
    int n = 0;
    double factor1 = 0.0;
    double factor2 = 1.0;
    double aproxPI = 0.0;
    
    
    for(n=1;n<workload*WORKLOAD;n++)
    {
        factor1 = (1.0/(2.0*n-1.0));
        
        
        for (int i = 1; i < n; i++) 
        {
            factor2 = factor2 * (((2.0*i)-1.0)/(2.0*i));
        }
        
        aproxPI += 2*factor1 * factor2;
        factor2 =1.0;
        
        if (realPi - aproxPI < 0.00001)
        {
            break;
        }
        system("clear"); 
        printf("Arcsin Taylor Aprox PI: %f at iteration: %d\n", aproxPI, n);
        
    }
    
    //printf("Serie de taylor de Arcsin para PI: %.63f \n", aproxPI);
}