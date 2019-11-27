/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <math.h>
#include <stdio.h>
#include "RateMonotonicScheduler.h"
#include "Utilities.h"


SchedResult* Results;
RMSchedulerTask* RMTs; 
RMSchedulerTask* ReadyQueue; 


void ConvertTastToRMTask(Task* tasks)
{
    for (int i = 0; i < tasksCount; i++) 
    {
        RMSchedulerTask newRMT;
        newRMT.task = tasks[i];
        newRMT.currentExecTime = 0;
        newRMT.scaleFactor = 1;
        newRMT.nextDeadline = tasks[i].Deadline;
        newRMT.deadlineMet = 0;
        RMTs[i] = newRMT;
    }
}

void CalculateCPU_Utilization(Task* task)
{
    int i;
    for (i = 0; i < tasksCount; i++) 
    {
        Results->CPU_Utilization += (double)(task->ComputationTime/task->Deadline);
    }
}

void CalculateSchedTest()
{
    double n = (double)tasksCount;
    
    double schedTest =  n * (powf(0.5, n) - 1.0);
}

int GetHighestPriority(Task* tasks)
{
    int highestPriority = 0;
    for (int i = 1; i < tasksCount; i++) 
    {
        if (tasks[i].Deadline < tasks[i-1].Deadline) 
        {
            highestPriority = i;
        }
    }

    return highestPriority;
}


void RunSchedTest(Task* tasks)
{
    ConvertTastToRMTask(tasks);
    
    // Get CPU utilization factor
    CalculateCPU_Utilization(tasks);
    
    // Evaluate Schedulability Test function
    CalculateSchedTest(tasksCount);
    
    int periods[tasksCount];
    
    for (int i = 0; i < tasksCount; i++) 
    {
        periods[i] = tasks[i].Period;
    }

    // run Least Common Multiple
    int lcm = LCM(periods, tasksCount);
    
    // Set time limit
    int timeLimit = lcm;
    
    int schedTestResult[timeLimit];
    
    for ( int i = 0; i< timeLimit; i++) 
    {
        // Get the highest priority tasks, (i.e. task with the lowest deadline)
        int nextTaskIndex = GetHighestPriority(tasks);
        
        if (tasks[nextTaskIndex].Deadline < tasks[nextTaskIndex].ComputationTime) 
        {
            printf("\n *FATAL ERROR! - Task %d can't make its deadline*\n", nextTaskIndex+1);
        }
            
        if (tasks[nextTaskIndex].Deadline < timeLimit) 
        {
            printf("\n *FATAL ERROR! - Task %d couldn't make its deadline*\n", nextTaskIndex+1);
        }
        
        // Run task
        schedTestResult[i] = RMTs[nextTaskIndex].task.Id;
        
        if (RMTs[nextTaskIndex].currentExecTime == RMTs[nextTaskIndex].task.ComputationTime) {

        }

        
        

    }

    

    
}