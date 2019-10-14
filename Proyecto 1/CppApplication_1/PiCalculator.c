
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
void CalculatePi()
{
    double result = 0.0;
    int n = 0;
    double x = 0; 
    double fac1 = 0;
    double fac2 = 0;
    double factor = 0;
    
    for(n=0;n<50;n++)
    {
      // x = 6.0 * pow(0.5, 2.0*n+1.0);
      // fac1 = factorial(2.0*n);
      // fac2 = pow(factorial(n),2);
      // factor = fac1 / (pow(4,n) * fac2 * (2.0*n+1.0));
      result += (factorial(2.0*n) / (pow(4,n) * pow(factorial(n),2) * (2.0*n+1.0)))*(6.0 * pow(0.5, 2.0*n+1.0));
    }
    
    printf("Serie de taylor de Arcsin para PI: %.63f \n", result);
}