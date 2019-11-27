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

/*
Task edf_tasks[NUM_OF_TASKS];
*/

int simulationCicles = 35;

EDFTask* Results;
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
        if (Results->TaskInfo[i].ComputationTime>0 && Results->TaskInfo[i].Period>0)
        {
            Results->CPU_Utilization += (Results->TaskInfo[i].ComputationTime / Results->TaskInfo[i].Period);
        }
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
        if ((t!=0) && ((int)Results->TaskInfo[i].Period != 0) && ((t % (int)Results->TaskInfo[i].Period) == 0))
        {
            Task* task = malloc(sizeof(Task));
            task->Id = Results->TaskInfo[i].Id;
            task->ComputationTime = Results->TaskInfo[i].ComputationTime;
            task->Deadline = Results->TaskInfo[i].Deadline + t;
            task->Period = Results->TaskInfo[i].Period;
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
    bool readyqueueUpdate = false;

    if (EdfRunSchedTest(task, NUM_OF_TASKS))
    {
        // init ready queue
        InitReadyQueue(task, tasksCount);

        // get earliest deadline task
        taskClient* task = GetTaskFromReadyQueue();


        // start sim cicles exec
        for (int t = 0; t < simulationCicles; t++)
        {
            // remove completed tasks from ready queue
            readyqueueUpdate = RemoveCompletedTasks();

            // look for new arrivals in ready queue
            readyqueueUpdate = readyqueueUpdate || AddNewTasks(t);
            
            if (readyqueueUpdate)
            {
                // get earliest deadline task
               task = GetTaskFromReadyQueue();
            }

            if (task != NULL)
            {
                if (task->clientTask->Deadline < t)
                {
                    printf("--> Tastk id: %i FAILED to meet deadline \n", task->clientTask->Id);
                    printf("--> Deadline: %f \n",task->clientTask->Deadline);
                    printf("--> Actual time: %i \n",t);
                    break;
                }

                // update computation time (execute task for one cycle)
                //task->clientTask->ComputationTime --;
                UpdateTaskComputationTime(task->clientTask->Id);

                // update simulation results
                Results->SimulationResults[t] = task->clientTask->Id;
            }
            else
            {
                // update simulation results
                Results->SimulationResults[t] = -1; 
            }

            printf("update simulation (%i ,%i) \n", t, Results->SimulationResults[t]);
            readyqueueUpdate = false;
        }


        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("RESULTS: \n");

        for (int i = 0; i < simulationCicles; i++)
        {
            printf("--> time: %i task: %i \n", i, Results->SimulationResults[i]);
        }
        
        
    }
}

/*
 * Populates dumy tasks for debugging purposes
 */
void RunEdfSched()
{
    // init struct s
    Results = malloc(sizeof(EDFTask));
    ReadyQueue = malloc(sizeof(readyQueue));
    
    // [DEBUG] create dumy tasks
    //EdfPopulateTaskstructures();
    
    Results->CPU_Utilization = 0;
    Results->TaskInfo = tasks;

    EdfStartSched(tasks, NUM_OF_TASKS);
}


// -----------------------------------------------------------------------------------

/*
 * Populates dumy tasks for debugging purposes
 */
void EdfPopulateTaskstructures()
{
}