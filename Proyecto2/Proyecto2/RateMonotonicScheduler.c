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


RMSchedResult* Results;
Queue* RMReadyQueue;

bool MetDeadline = true;

extern Task tasks[NUM_OF_TASKS];
extern int leastCommonMultiple;



/*
 * Prints Missed Deadline Message
 */
void PrintRMMissedDeadlineMessage(RMTaskClient* task, int t)
{
    printf("\n");
    printf("\n");
    printf("--> Tastk id: %i FAILED to meet deadline \n", task->rMTask->Id);
    printf("--> Deadline: %f \n",task->rMTask->Deadline);
    printf("--> Actual time: %i \n",t);
    printf("XXXXXX Blind grandma brutally killed in a hit and run accident!!! XXXXXX");
    printf("\n");
    printf("\n");    
}



/*
 * Adds task to ready queue
 */
void AddRMTaskToReadyQueue(Task* task, int simPeriod)
{
    RMTaskClient* newTask = malloc(sizeof(RMTaskClient));
    
    // update deadline given simulation time
    task->Deadline += simPeriod;

    newTask->rMTask = task;

    if (RMReadyQueue->tail != NULL)
    {
        newTask->next = RMReadyQueue->head;
        RMReadyQueue->head = newTask;
    }
    else
    {
        RMReadyQueue->tail = newTask;
        RMReadyQueue->head = newTask;
        RMReadyQueue->tail->next = NULL;
    }
    RMReadyQueue->QueueSize++;
}

/*
 * Delets task from ready queue
 */
bool RemoveRMCompletedTasks() 
{
    RMTaskClient* client = RMReadyQueue->head;
    RMTaskClient* target = client, *prev;

    // If head node itself is completed, delete it
    if (target != NULL && target->rMTask->ComputationTime == 0) 
    { 
        RMReadyQueue->head = target->next;    // Changed head 
        // free(target);                       // free old head
        RMReadyQueue->QueueSize--;
        return true; 
    }
    

    // Search task be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (target != NULL && target->rMTask->ComputationTime != 0) 
    { 
        prev = target; 
        target = target->next; 
    }
  
    // If key was not present in linked list 
    if (target == NULL) 
    {
        return false; 
    }
    if (target == RMReadyQueue->tail) 
    {
        // Unlink the node from linked list
        prev->next = NULL;
        RMReadyQueue->tail = prev;
    }
    else
    {
        // Unlink the node from linked list
        prev->next = target->next;
    }

    free(target);  // Free memory 
    return true; 
}

void UpdateRMTaskComputationTime(int id)
{
    RMTaskClient* rmtask = RMReadyQueue->head;

    while (rmtask != NULL)
    {
        if (rmtask->rMTask->Id == id)
        {
            rmtask->rMTask->ComputationTime --;
            break;
        }
        
        rmtask = rmtask->next;
    }
}

/*
 * Gets earliest deadline Task from ReadyQueue
 */
RMTaskClient* GetRMTaskFromReadyQueue()
{
    RMTaskClient* rmtask = RMReadyQueue->head;
    RMTaskClient* rmtarget = NULL;

    if (rmtask != NULL)
    {
        if (rmtask->rMTask != NULL) 
        {
            int minPeriod = rmtask->rMTask->Period;
            rmtarget = rmtask;

            while (rmtask != NULL)
            {
                if (rmtask->next == NULL)
                {
                    break;
                }
                else if (rmtask->next->rMTask->Period < minPeriod)
                {
                    rmtarget = rmtask->next;
                    minPeriod = rmtarget->rMTask->Period;
                }

                rmtask = rmtask->next;
            }

        }

        
    }
    return rmtarget;
}

/*
 * Inits ReadyQueue
 */
void InitRMReadyQueue(Task* task, int tasksCount)
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
                AddRMTaskToReadyQueue(t, 0);                
            }
        }    
    }
}

bool VerifyRepeatedTasksIdsInQueue(int id, int t)
{
    bool missedDeadline = false;
    RMTaskClient* task = malloc(sizeof(RMTaskClient));
    task = RMReadyQueue->head;
    
    while(task != NULL)
    {
        if (task->rMTask->Id == id) 
        {
            if ((task->rMTask->Deadline-1 < t) && (task->rMTask->ComputationTime > 0)) 
            {
                Results->SimulationResults[t] = 666+id;
                Results->numberOfSimCycles = t+1;
                //PrintRMMissedDeadlineMessage(task, t);
                missedDeadline = true;
                MetDeadline = false;
            break;

            }
        }
        task = task->next;
    }
    
    free(task);
    return missedDeadline;
}


bool MonitorDeadlines(int t)
{
    bool  missedDeadline = false;
    for (int i=0; i < NUM_OF_TASKS; i++)
    {
        if (((int)Results->TaskInfo[i].ComputationTime > 0) && ((int)Results->TaskInfo[i].Deadline < t))
        {
            Results->SimulationResults[t] = 666+Results->TaskInfo[i].Id;
            Results->numberOfSimCycles = t+1;
            //PrintRMMissedDeadlineMessage(task, t);
            missedDeadline = true;
            MetDeadline = false;
            break;
        }
    }
    return missedDeadline;
}

/*
 * Adds new tasks to ready queue based on current t and tasks period
 */
bool AddNewRMTasks(int t)
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
            if (VerifyRepeatedTasksIdsInQueue(task->Id, t)) 
            {
                MetDeadline = false;
                break;
            }
            else
            {
                AddRMTaskToReadyQueue(task, 0);
                newTaskAdded = true;
                MetDeadline = true;
            }
/*
            AddRMTaskToReadyQueue(task, 0);
            newTaskAdded = true;
*/
        }
    }
    
    return newTaskAdded;
}


/*
 * Computes RM CPU utilization
 * u = Σ (c/p), u<=1
 */
bool CalculateCPU_Utilization(Task* task)
{
    bool result = true;
    int i;
    for (i = 0; i < tasksCount; i++) 
    {
        if (task[i].Deadline != 0) 
        {
            Results->CPU_Utilization += (double)(task[i].ComputationTime/task[i].Deadline);
        }
    }
    
    if (Results->CPU_Utilization > 1.0) 
    {
        result = false;
        printf("WARNING: CPU utilization for RM is %f and it is greater than one!", Results->CPU_Utilization);
    }
    
    return result;
}

/*
 * Computes RM Schedulability Test.
 * U(n) = n(2^(1/n) - 1)
 */
bool  CalculateSchedTest()
{
    double n = (double)tasksCount;
    
    double schedTest =  n * (powf(2.0, 1.0/n) - 1.0);
    
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

/*
 * 
 * 
 */
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


void RunRMSchedTest(Task* tasks)
{
    bool readyqueueUpdate = false;
    CalculateCPU_Utilization(tasks);

    // Evaluate Schedulability Test function
    CalculateSchedTest(tasksCount);
    
    // All tasks in ready queue at the beginning. 
    InitRMReadyQueue(tasks, tasksCount);
    
    // get earliest deadline task
    RMTaskClient* task = GetRMTaskFromReadyQueue();

    for (int j = 0; j < leastCommonMultiple; j++) 
    {
        // remove completed tasks from ready queue
        readyqueueUpdate = RemoveRMCompletedTasks();
        
        // look for new arrivals in ready queue
        readyqueueUpdate = AddNewRMTasks(j) || readyqueueUpdate;
        
        if (readyqueueUpdate)
        {
            // get high priority task
           task = GetRMTaskFromReadyQueue();
        }
        
        if (MetDeadline == false) 
        {
            break;
        }
        
        if (task != NULL)
        {
            if (task->rMTask->Deadline < j)
            {
                Results->SimulationResults[j] = 666+task->rMTask->Id;
                Results->numberOfSimCycles = j+1;
                PrintRMMissedDeadlineMessage(task, j);
                break;
            }
            
            // update computation time (execute task for one cycle)
            UpdateRMTaskComputationTime(task->rMTask->Id);

            // update simulation Results
            Results->SimulationResults[j] = task->rMTask->Id;
        }
        else
        {
            // update simulation Results
            Results->SimulationResults[j] = -1; 
        }

        printf("update simulation (%i ,%i) \n", j, Results->SimulationResults[j]);
        readyqueueUpdate = false;
    }
    
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Results: \n");

    for (int i = 0; i < SIM_CYCLES; i++)
    {
        printf("--> time: %i task: %i \n", i, Results->SimulationResults[i]);
    }

}

/*
 * Populates dumy tasks for debugging purposes
 */
void RunRMSched()
{
    // init struct s
    Results = malloc(sizeof(RMSchedResult));
    RMReadyQueue = malloc(sizeof(Queue));
    RMReadyQueue->head = NULL;
    RMReadyQueue->tail = NULL;
    RMReadyQueue->QueueSize = 0;
    

    // init results struct members
    Results->CPU_Utilization = 0;
    Results->TaskInfo = tasks;
    Results->numberOfSimCycles = leastCommonMultiple;
    Results->SimulationResults = (int*)malloc(sizeof(int) * Results->numberOfSimCycles);
    Results->algorithmName = "Rate Monotonic (RM)";
    
    // initializes variable
    MetDeadline = true;

    // perform edf sched test and do sched
    RunRMSchedTest(tasks);
}