/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <string.h>
#include "FCFSScheduler.h"
#include "progress_gui.h"

FCFSQueue* ProcessQueue;
extern int CurrentRunningProcess;

void InitFCFSSched()
{
    // initialize the Queue
    ProcessQueue = malloc(sizeof(FCFSQueue));
    ProcessQueue->head =  NULL;
    ProcessQueue->tail = NULL;
    ProcessQueue->QueueSize = 0;
}

void Push(processStruct* process)
{
    FCFSElement* newProcess = malloc(sizeof(FCFSElement));
    newProcess->clientTask = process;

    if (ProcessQueue->tail != NULL)
    {
        newProcess->next = ProcessQueue->head;
        ProcessQueue->head = newProcess;
    }
    else
    {
        ProcessQueue->tail = newProcess;
        ProcessQueue->head = newProcess;
        ProcessQueue->tail->next = NULL;
        //ProcessQueue->head->next = NULL; 
    }

    // Update counter
    ProcessQueue->QueueSize += 1;
}

FCFSElement* Pop()
{
    FCFSElement* neededClient = ProcessQueue->head;
    FCFSElement* tempClient = ProcessQueue->head;

    while (neededClient != ProcessQueue->tail)
    {
        tempClient = neededClient;
        neededClient =  tempClient->next;
    }
    tempClient->next=NULL;
    ProcessQueue->tail = tempClient;
    
    ProcessQueue->QueueSize -= 1;
    
    return neededClient;
}

void QueueSize()
{
    printf("Queue Size: %d \n", ProcessQueue->QueueSize);
}

void PrintQueue()
{
    FCFSElement* client = ProcessQueue->head;

    while (client != NULL)
    {
        printf("ID: %d \n",client->clientTask->ID);
        client = client->next;
    }
}

void FindWaitingTime()
{
    
}

void FindTurnAroundTime()
{
    
}

void FindNextArrivalTime(int processCount, processStruct* processArrivT[])
{
    int i, j;
    processStruct* k;
    for (i = 0; i < processCount; ++i)
    {
        int j;
        for (j=i+1; j < processCount; ++j) 
        {
            if (processArrivT[i]->Arrivaltime >= processArrivT[j]->Arrivaltime)
            {
                k = processArrivT[i];
                processArrivT[i] = processArrivT[j];
                processArrivT[j] = k;
            }
        }
        processArrivT[i]->Process_State = WAITING;
    }
    
#ifdef DEBUG
    int n;
    for (n = 0; n < processCount; n++) {
        printf("Process: %d Arrival Time: %d\n",n,processArrivT[n]->Arrivaltime);
    }
#endif

}

void RunFCFSScheduling(int processArrivT[],int processWorkload[], int processCount)
{
    processStruct* processList[processCount];
    
    
    // Create processes and push them into the queue
    for(int i=0;i<processCount;i++)
    {
        processStruct* process =  malloc(sizeof(processStruct));
        process->ID = i+1;
        process->Arrivaltime = processArrivT[i];
        process->BurstTime = processWorkload[i];
        process->Process_State = CREATED;
        processList[i] = process;
    }
    
    // Find the waiting time for each process
    FindWaitingTime();
    
    // Find the turn around time
    FindTurnAroundTime();
    
    FindNextArrivalTime(processCount, processList);
    
    // execute that process
    InitFCFSSched();
    for(int i=0;i<processCount;i++)
    {
        processList[i]->Process_State = READY;
        Push(processList[i]);
    }
    
    FCFSElement* executingProcess;
    
    int i;
    for (i = 0; i < processCount; i++) 
    {
        memcpy(executingProcess, Pop(), sizeof(FCFSElement*));
        printf("Executing Process: %d\n", executingProcess->clientTask->ID);
        
        // Notify GUI and move winning process to CPU
        CurrentRunningProcess = executingProcess->clientTask->ID;
        MoveProcessBetweenQueues(READY_QUEUE,CPU_QUEUE,executingProcess->clientTask->ID);
        
        executingProcess->clientTask->process_task = CalculatePi(executingProcess->clientTask->BurstTime);
        printf("Process Workload: %d\n", executingProcess->clientTask->BurstTime);
    }
}