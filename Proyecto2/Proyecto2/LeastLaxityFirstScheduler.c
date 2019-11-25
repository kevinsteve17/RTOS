#include "LeastLaxityFirstScheduler.h"
#include "Task.h"
#include <stdio.h>
#include <unistd.h>

// Program Global Variables


// File Global Variables
int numberOfTasks = 3;
Task tasks[3];
int leastCommonMultiple = 0;
int tasksComputation[3];
int tasksDeadline[3];
int tasksPeriod[3];
int tasksLaxity[3];
int minLaxity;
int minLaxityIndex;


// Function:    LLF_PopulateDummyTasks
// Description: Debugging purposes, populates 3 tasks
void LLF_PopulateDummyTasks()
{
    tasks[0].Id = 0;
    tasks[0].ComputationTime = 2;
    tasks[0].Period = 6;
    tasks[0].Deadline = tasks[0].Period;
    
    tasks[1].Id = 0;
    tasks[1].ComputationTime = 2;
    tasks[1].Period = 8;
    tasks[1].Deadline = tasks[1].Period;
    
    tasks[2].Id = 0;
    tasks[2].ComputationTime = 3;
    tasks[2].Period = 3;
    tasks[2].Deadline = tasks[2].Period;
}


// Function:    LLF_CalculateLeastCommonMultiple
// Description: Calculates the Least Common Multiple of the available tasks.
//              This sets the limit of the simulation time.
int LLF_CalculateLeastCommonMultiple()
{
    // C program to find LCM of 3 numbers
    int Num1, Num2, Num3;
    
    // Init
    leastCommonMultiple = 1;
    Num1 = tasks[0].Period;
    Num2 = tasks[1].Period;
    Num3 = tasks[2].Period;
    
    
    while(1) // Always True
    {
    	if(leastCommonMultiple % Num1 == 0 && 
           leastCommonMultiple % Num2 == 0 &&
           leastCommonMultiple % Num3 == 0) 
    	{
            return leastCommonMultiple;
	}
 
	++leastCommonMultiple;
    }   
}


// Function:    LLF_CalculateLeastCommonMultiple
// Description: Calculates the Least Common Multiple of the available tasks.
//              This sets the limit of the simulation time.
void LLF_RunSchedTest()
{   
    // Set time limit
    int timeLimit = leastCommonMultiple;
    
    // As part of algorithm init make copies of the user input tasks
    for (int task=0 ; task<numberOfTasks ; task++)
    {
        tasksComputation[task] = tasks[task].ComputationTime;
        tasksDeadline[task] = tasks[task].Deadline;
        tasksPeriod[task] = tasks[task].Period;
    }
    
    // Start of Least Laxity First Algorithm
    for (int time=0; time<timeLimit; time++)
    {
        // Init loop values
        minLaxity = 1000;
        minLaxityIndex = 1000;
        
        // For each task, check its deadline and calculate its laxity
        for (int task=0 ; task<numberOfTasks ; task++)
        {
            // Check tasks deadlines
            if (tasksComputation[task] > tasksDeadline[task])
            {
                // Force the main loop to end
                printf("\n *Bombastic! - Task %d can't make its deadline*\n", task+1);
                time = timeLimit;
            }

            // Check if we need to renew a task values due to new period
            if ((time > 0) && (time % tasksPeriod[task] == 0))
            {
                tasksComputation[task] = tasks[task].ComputationTime;
                tasksDeadline[task] = tasks[task].Deadline;
            }
            
            // Calculate laxity per task and cache minimum value
            if (tasksComputation[task] <= 0)
            {
                // If a task finished, force a big laxity to "ignore it"
                tasksLaxity[task] = 1000;
            }
            else
            {
                // Laxity = Deadline - Computation time
                tasksLaxity[task] = tasksDeadline[task] - tasksComputation[task];
            }          
            
            // Cache minimum laxity value
            if (minLaxity > tasksLaxity[task])
            {
                minLaxityIndex = task;
                minLaxity = tasksLaxity[task];
            }
        }
        
        // Update Timing Diagram
        if (minLaxityIndex == 1000)
        {
            // Special case. Sub-utilization.
            printf("-");
            fflush(stdout);
            
            continue;
        }
        else 
        {
            printf("%d", minLaxityIndex);
            fflush(stdout);
        }
               
        // Decrement running task computation value
        tasksComputation[minLaxityIndex] = tasksComputation[minLaxityIndex] - 1;
        
        // Decrement all deadline values
        for (int task=0 ; task<numberOfTasks ; task++)
        {
            tasksDeadline[task] = tasksDeadline[task] - 1;
        }
        
    } // end for (int time=0; time<timeLimit; timeLimit++)

    // PrintTimingDiagram ();
    return;
    
} // end LLF_RunSchedTest()






