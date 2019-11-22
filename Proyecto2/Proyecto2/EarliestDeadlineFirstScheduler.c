/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <math.h>
#include <stdbool.h>
#include "EarliestDeadlineFirstScheduler.h"

EDFTask* Results;

/*
 * Computes EDF schedulability test
 * u = Σ (c/p), u<=1
 */
void CalculateEdfSchedTest(Task* task, int tasksCount)
{
    int i;
    for (i = 0; i < tasksCount; i++) 
    {
        Results->CPU_Utilization += (double)(task->ComputationTime/task->Deadline);
    }
}

/*
 * Executes EDF schedulability test
 */
bool RunEdfSchedTest(Task* task, int tasksCount)
{
    CalculateEdfSchedTest(task, tasksCount);

    if (Results->CPU_Utilization >= 1)
    {
        return true;
    }
    else
    {
        return false;  
    }        
}

/*
 * Starts EDF scheduler
 */
void PerformEdfSched(Task* task, int tasksCount)
{

}