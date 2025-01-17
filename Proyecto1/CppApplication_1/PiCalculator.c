
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Utilities.h"
#include "progress_gui.h"
#include "Timer.h"

extern int CurrentRunningProcess;
extern int QuantumInMilli;
extern int processHasSavedContext;
extern int processCompletedExecution;
float CurrentRunningProcressProgress;

// Context Save
int saved_itt[25];
double saved_aproxPI[25];
int saved_factor1[25];
double saved_factor2[25];


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
    double realPi = 3.14159;
    double factor1 = 0.0;
    double factor2 = 1.0;
    int itt = 1;
    double aproxPI = 0.0;
    
    if (processHasSavedContext == true)
    {
        // Load it!
        itt = saved_itt[CurrentRunningProcess];
        aproxPI = saved_aproxPI[CurrentRunningProcess];
        factor1 = saved_factor1[CurrentRunningProcess];
        factor2 = saved_factor2[CurrentRunningProcess];
    }

    
    for(int n=itt;n<workload*WORKLOAD;n++)
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
        

        // Calculate process var value
        CurrentRunningProcressProgress = (n*100)/(workload*WORKLOAD);

        // Notify the display and update the processes progress bar
        UpdateProcessDisplayedInfo(CPU_QUEUE, CurrentRunningProcess, aproxPI, CurrentRunningProcressProgress);

        // Verify is Quantum is over and take actions
        if (IsQuantumOver() == 1)
        {
            PrintDebugMessageInDisplay("Time.");

            // Stop the clock while we switch context
            StopQuantumSoftTimer();

            // Process Complete.
            HideProcessInCPU(CurrentRunningProcess);           

            // Context Switch
            processHasSavedContext = true;

            // Save context
            saved_itt[CurrentRunningProcess] = n;
            saved_aproxPI[CurrentRunningProcess] = aproxPI;
            saved_factor1[CurrentRunningProcess] = factor1; 
            saved_factor2[CurrentRunningProcess] = factor2;

            // Break out to be able to call CalculatePi again with a new process
            return;
        }

        
        
        
        // Debug Print - Show accumulated PI value
        //system("clear"); 
        //printf("Serie de taylor de Arcsin para PI: %f \n", aproxPI);
    }
       
    // Process Complete.
    UpdateProcessDisplayedInfo(CPU_QUEUE, CurrentRunningProcess, aproxPI, 100);
    HideProcessInCPU(CurrentRunningProcess);
    processCompletedExecution = true;
       
    // Debug Print - Show accumulated PI value
    //printf("Serie de taylor de Arcsin para PI: %.63f \n", aproxPI);
}