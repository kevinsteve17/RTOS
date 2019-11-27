#include "LeastLaxityFirstScheduler.h"
#include "Task.h"
#include <stdio.h>
#include <unistd.h>

// Program Global Variables
extern Task tasks[6];
extern int maxNumberOfTasks;
extern int numberOfTasks;
extern int leastCommonMultiple;

// File Global Variables
int tasksComputation[6];
int tasksDeadline[6];
int tasksPeriod[6];
int tasksLaxity[6];
int minLaxity;
int minLaxityIndex;

// *****************************************************************************
// Function:    LLF_CalculateLeastCommonMultiple
// Description: Calculates the Least Common Multiple of the available tasks.
//              This sets the limit of the simulation time.
void LLF_RunSchedTest()
{   
    printf("Function call: LLF_RunSchedTest()\n");
    
    // Set time limit
    int timeLimit = leastCommonMultiple;
    
    // As part of algorithm init make copies of the user input tasks
    for (int task=0 ; task < numberOfTasks ; task++)
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
                printf("\n *Bombastic! - Task %d can't make its deadline*\n", task);
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






