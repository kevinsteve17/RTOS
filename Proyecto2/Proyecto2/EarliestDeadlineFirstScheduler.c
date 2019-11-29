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

EDFTask* edfResutls;
readyQueue* ReadyQueue;

extern Task tasks[NUM_OF_TASKS];
extern int leastCommonMultiple;

/*
 * Computes EDF schedulability test
 * u = Σ (c/p), u<=1
 */
void EdfCalculateSchedTest(Task* task, int tasksCount)
{
    for (int i = 0; i < tasksCount; i++) 
    {
        if (edfResutls->TaskInfo[i].ComputationTime>0 && edfResutls->TaskInfo[i].Period>0)
        {
            edfResutls->CPU_Utilization += (edfResutls->TaskInfo[i].ComputationTime / edfResutls->TaskInfo[i].Period);
        }
    }

    printf("--> EDF schedulability test: %f \n",edfResutls->CPU_Utilization);
}

/*
 * Executes EDF schedulability test
 */
bool EdfRunSchedTest(Task* task, int tasksCount)
{
    EdfCalculateSchedTest(task, tasksCount);    

    if (edfResutls->CPU_Utilization <= 1)
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
 * Delets task from ready queue
 */
bool RemoveCompletedTasks() 
{
    taskClient* client = ReadyQueue->head;
    taskClient* target = client, *prev;

    // If head node itself is completed, delete it
    if (target != NULL && target->clientTask->ComputationTime == 0) 
    { 
        ReadyQueue->head = target->next;    // Changed head 
        free(target);                       // free old head
        ReadyQueue->QueueSize--;
        return true; 
    }

    // Search task be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (target != NULL && target->clientTask->ComputationTime != 0) 
    { 
        prev = target; 
        target = target->next; 
    }
  
    // If key was not present in linked list 
    if (target == NULL) 
    {
        return false; 
    }
  
    // Unlink the node from linked list 
    prev->next = target->next;

    free(target);  // Free memory 
    return true; 
}

void UpdateTaskComputationTime(int id)
{
    taskClient* task = ReadyQueue->head;

    while (task != NULL)
    {
        if (task->clientTask->Id == id)
        {
            task->clientTask->ComputationTime --;
            break;
        }
        
        task = task->next;
    }
}

/*
 * Gets earliest deadline Task from ReadyQueue
 */
taskClient* GetTaskFromReadyQueue()
{
    taskClient* task = ReadyQueue->head;
    taskClient* target = NULL;

    if (task != NULL)
    {
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
    }

    /*printf("--> GetTaskFromReadyQueue() \n");
    printf("--> id: %i \n",target->clientTask->Id);
    printf("--> ComputationTime: %f \n",target->clientTask->ComputationTime);
    printf("--> Deadline: %f \n",target->clientTask->Deadline);*/

    return target;
}

/*
 * Inits ReadyQueue
 */
void InitReadyQueue(Task* task, int tasksCount)
{
    if (task != NULL)
    {
        for (int i = 0; i < tasksCount; i++) 
        {
            if (task[i].ComputationTime>0 && task[i].Period>0)
            {
                Task* t = malloc(sizeof(Task));
                t->Id = task[i].Id;
                t->ComputationTime = task[i].ComputationTime;
                t->Deadline = task[i].Deadline;
                t->Period = task[i].Period;
                AddTaskToReadyQueue(t, 0);                
            }
        }    
    }
}

/*
 * Adds new tasks to ready queue based on current t and tasks period
 */
bool AddNewTasks(int t)
{
    bool newTaskAdded = false;

    for (int i=0; i < NUM_OF_TASKS; i++)
    {
        if ((t!=0) && ((int)edfResutls->TaskInfo[i].Period != 0) && ((t % (int)edfResutls->TaskInfo[i].Period) == 0))
        {
            Task* task = malloc(sizeof(Task));
            task->Id = edfResutls->TaskInfo[i].Id;
            task->ComputationTime = edfResutls->TaskInfo[i].ComputationTime;
            task->Deadline = edfResutls->TaskInfo[i].Deadline + t;
            task->Period = edfResutls->TaskInfo[i].Period;
            AddTaskToReadyQueue(task, 0);

            newTaskAdded = true; 
        }
    }
    
    return newTaskAdded;
}

/*
 * Starts EDF scheduler
 */
void EdfStartSched(Task* task, int tasksCount)
{
    bool readyQueueUpdate = false;

    if (EdfRunSchedTest(task, NUM_OF_TASKS))
    {
        // init ready queue
        InitReadyQueue(task, tasksCount);

        // get earliest deadline task
        taskClient* task = GetTaskFromReadyQueue();

        // start sim cycles exec
        for (int t = 0; t < leastCommonMultiple; t++)
        {
            // remove completed tasks from ready queue
            readyQueueUpdate = RemoveCompletedTasks();

            // look for new arrivals in ready queue
            readyQueueUpdate = AddNewTasks(t) || readyQueueUpdate;
            
            if (readyQueueUpdate)
            {
                // get earliest deadline task
               task = GetTaskFromReadyQueue();
            }

            if (task != NULL)
            {
                // check task's deadline is still on time
                if (task->clientTask->Deadline < t)
                {
                    printf("--> Tastk id: %i FAILED to meet deadline \n", task->clientTask->Id);
                    printf("--> Deadline: %f \n",task->clientTask->Deadline);
                    printf("--> Actual time: %i \n",t);
                    break;
                }

                // update computation time (execute task for one cycle)
                UpdateTaskComputationTime(task->clientTask->Id);

                // update simulation edfResutls
                edfResutls->SimulationResults[t] = task->clientTask->Id;
            }
            else
            {
                // update simulation edfResutls
                edfResutls->SimulationResults[t] = -1; 
            }

            printf("update simulation (%i ,%i) \n", t, edfResutls->SimulationResults[t]);
            readyQueueUpdate = false;
        }

        printf("\n");
        printf("edfResutls: \n");

        for (int i = 0; i < leastCommonMultiple; i++)
        {
            printf("--> time: %i task: %i \n", i, edfResutls->SimulationResults[i]);
        }
    }
}

/*
 * Populates dumy tasks for debugging purposes
 */
void RunEdfSched()
{
    // init struct s
    edfResutls = malloc(sizeof(EDFTask));
    ReadyQueue = malloc(sizeof(readyQueue));
    
    // init results struct members
    edfResutls->CPU_Utilization = 0;
    edfResutls->TaskInfo = tasks;
    edfResutls->numberOfSimCycles = leastCommonMultiple;
    edfResutls->SimulationResults = (int*)malloc(sizeof(int) * leastCommonMultiple);

    // perform edf sched test and start sched
    EdfStartSched(tasks, NUM_OF_TASKS);
}


// -----------------------------------------------------------------------------------

/*
 * Populates dumy tasks for debugging purposes
 */
void EdfPopulateTaskstructures()
{
}