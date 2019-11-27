/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "EarliestDeadlineFirstScheduler.h"

EDFTask* Results;
readyQueue* ReadyQueue;

Task edf_tasks[NUM_OF_TASKS];
int simulationCicles = 52;

/*
 * Computes EDF schedulability test
 * u = Σ (c/p), u<=1
 */
void EdfCalculateSchedTest(Task* task, int tasksCount)
{
    for (int i = 0; i < tasksCount; i++) 
    {
        Results->CPU_Utilization += (Results->TaskInfo[i].ComputationTime / Results->TaskInfo[i].Period);
    }

    printf("--> EDF schedulability test: %f \n",Results->CPU_Utilization);
}

/*
 * Executes EDF schedulability test
 */
bool EdfRunSchedTest(Task* task, int tasksCount)
{
    EdfCalculateSchedTest(task, tasksCount);    

    if (Results->CPU_Utilization <= 1)
    {
        printf("--> PASSED \n");
        return true;
    }
    else
    {
        printf("--> FAILED \n");
        return false;  
    }        
}

/*
 * Adds task to ready queue
 */
void AddTaskToReadyQueue(Task* task, int simPeriod)
{
    taskClient* newTask = malloc(sizeof(taskClient));
    
    // update deadline given simulation time
    task->Deadline += simPeriod;

    newTask->clientTask = task;

    if (ReadyQueue->tail != NULL)
    {
        newTask->next = ReadyQueue->head;
        ReadyQueue->head = newTask;
    }
    else
    {
        ReadyQueue->tail = newTask;
        ReadyQueue->head = newTask;
        ReadyQueue->tail->next = NULL;
    }
}

/*
 * Gets earliest deadline Task from ReadyQueue
 */
taskClient* GetTaskFromReadyQueue()
{
    taskClient* task = ReadyQueue->head;
    taskClient* target = NULL;

    int earliestDeadline = task->clientTask->Deadline;
    target = task;

    while (task != NULL)
    {
        if (task->next == NULL)
        {
            break;
        }
        else if (task->next->clientTask->Deadline < earliestDeadline)
        {
            target = task->next;
            earliestDeadline = target->clientTask->Deadline;
        }
        
        task = task->next;
    }

    return target;

}

/*
 * Starts EDF scheduler
 */
void EdfStartSched(Task* task, int tasksCount)
{    
    if (EdfRunSchedTest(task, NUM_OF_TASKS))
    {
        // init ready queue
        for (int i = 0; i < tasksCount; i++) 
        {
            Task* t = malloc(sizeof(Task));
            t->Id = task[i].Id;
            t->ComputationTime = task[i].ComputationTime;
            t->Deadline = task[i].Deadline;
            t->Period = task[i].Period;
            AddTaskToReadyQueue(t, 0);
        }

        // get earliest deadline task
        taskClient* t = GetTaskFromReadyQueue();

    }
}

/*
 * Populates dumy tasks for debugging purposes
 */
void EdfPopulateTaskstructures()
{
    edf_tasks[0].Id = 777;
    edf_tasks[0].ComputationTime = 6;
    edf_tasks[0].Period = 19;
    edf_tasks[0].Deadline = edf_tasks[0].Period;
    
    edf_tasks[1].Id = 2;
    edf_tasks[1].ComputationTime = 2;
    edf_tasks[1].Period = 8;
    edf_tasks[1].Deadline = edf_tasks[1].Period;
    
    edf_tasks[2].Id = 3;
    edf_tasks[2].ComputationTime = 1;
    edf_tasks[2].Period = 5;
    edf_tasks[2].Deadline = edf_tasks[2].Period;

    Results->TaskInfo = edf_tasks;
}

/*
 * Populates dumy tasks for debugging purposes
 */
void edf_test()
{
    // init struct s
    Results = malloc(sizeof(EDFTask));
    ReadyQueue = malloc(sizeof(readyQueue));
    
    // [DEBUG] create dumy tasks
    EdfPopulateTaskstructures();
    
    Results->CPU_Utilization = 0;

    EdfStartSched(edf_tasks, NUM_OF_TASKS);
}