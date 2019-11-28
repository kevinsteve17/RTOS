/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "RateMonotonicScheduler.h"
#include "Utilities.h"


SchedResult* Results;
Queue* ReadyQueue;

void InitFCFSSched()
{
    // initialize the Queue
    ReadyQueue = malloc(sizeof(Queue));
    ReadyQueue->head =  NULL;
    ReadyQueue->tail = NULL;
    ReadyQueue->QueueSize = 0;
}

void Push(Task* process)
{
    Element* newProcess = malloc(sizeof(Element));
    newProcess->rMTask = process;

    if (ReadyQueue->tail != NULL)
    {
        newProcess->next = ReadyQueue->head;
        ReadyQueue->head = newProcess;
    }
    else
    {
        ReadyQueue->tail = newProcess;
        ReadyQueue->head = newProcess;
        ReadyQueue->tail->next = NULL;
        //ProcessQueue->head->next = NULL; 
    }

    // Update counter
    ReadyQueue->QueueSize += 1;
}

Element* Pop()
{
    Element* neededClient = ReadyQueue->head;
    Element* tempClient = ReadyQueue->head;

    while (neededClient != ReadyQueue->tail)
    {
        tempClient = neededClient;
        neededClient =  tempClient->next;
    }
    tempClient->next=NULL;
    ReadyQueue->tail = tempClient;
    
    ReadyQueue->QueueSize -= 1;
    
    return neededClient;
}

void QueueSize()
{
    printf("Queue Size: %d \n", ReadyQueue->QueueSize);
}

void PrintQueue()
{
    Element* client = ReadyQueue->head;

    while (client != NULL)
    {
        printf("ID: %d \n",client->rMTask->Id);
        client = client->next;
    }
}



bool CalculateCPU_Utilization(Task* task)
{
    bool result = true;
    int i;
    for (i = 0; i < tasksCount; i++) 
    {
        Results->CPU_Utilization += (double)(task->ComputationTime/task->Deadline);
    }
    
    if (Results->CPU_Utilization > 1) 
    {
        result = false;
        printf("WARNING: CPU utilization for RM is %f and it is greater than one!", Results->CPU_Utilization);
    }
    
    return result;
}

bool  CalculateSchedTest()
{
    double n = (double)tasksCount;
    
    double schedTest =  n * (powf(0.5, n) - 1.0);
    
    Results->SchedTest = schedTest;
    
    if (schedTest <= 1) 
    {
        printf("RM Schedulability Test PASSED! \n");
    }
    else
    {
        printf("RM Schedulability Test FAILED! \n");
    }
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
    
    if (CalculateCPU_Utilization(tasks)) {

    }

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
    
    // All tasks in ready queue at the beginning.    

    for (int j = 0; j < tasksCount; j++) 
    {
        //Push(tasks[j]);
    }

}