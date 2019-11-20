/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <math.h>
#include "RateMonotonicScheduler.h"

RMTask* Results;

void CalculateCPU_Utilization(Task* task, int tasksCount)
{
    int i;
    for (i = 0; i < tasksCount; i++) 
    {
        Results->CPU_Utilization += (double)(task->ComputationTime/task->Deadline);
    }
}
void CalculateSchedTest(int taskCount)
{
    double n = (double)taskCount;
    
    double schedTest =  n * (powf(0.5, n) - 1.0);
}
void RunSchedTest(Task* task, int tasksCount)
{
    CalculateCPU_Utilization(task, tasksCount);
    CalculateSchedTest(tasksCount);
    
    // run RM

    
}