/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include "FCFSScheduler.h"

FCFSQueue* ProcessQueue;

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

int* FindNextArrivalTime(int processCount, int processArrivT[])
{
    int processesByArrivTime[processCount];
    
    int i, j, k;
    for (i = 0, k=0; i < processCount; ++i)
    {
        int j;
        for (j=i+1; j < processCount; ++j) 
        {
            if (processArrivT[i] > processArrivT[j])
            {
                k = processArrivT[i];
                processArrivT[i] = processArrivT[j];
                processArrivT[j] = k;
            }
        }
    }
    
    
    int n;
    for (n = 0; n < processCount; n++) {
        printf("Process: %d Arrival Time: %d\n",n,processArrivT[n]);
    }

/*
    FCFSElement* client = ProcessQueue->head;
    FCFSElement* nextClient;

    while (client != NULL)
    {
        if (client->clientTask->Arrivaltime > ProcessQueue->head->clientTask->Arrivaltime) 
        {
            nextClient=client;
        }
        client = client->next;
    }
*/
    return processesByArrivTime;
}

void RunFCFSScheduling(int processArrivT[],int processWorkload[], int processCount)
{
    int* processesByArrivTime;
    
    processesByArrivTime = FindNextArrivalTime(processCount,processArrivT);
    
    // Create processes and push them into the queue
    for(int i=0;i<processCount;i++)
    {
/*
        processStruct* process =  malloc(sizeof(processStruct));
        process->ID = i;
        process->Arrivaltime = processinfo->ArrivalTime;
        process->BurstTime = processinfo->BurstTime;
        process->Process_State = CREATED;
        Push(process);
*/
    }
    
    // Find the waiting time for each process
    FindWaitingTime();
    
    // Find the turn around time
    FindTurnAroundTime();
    
    // Init timer 
    
    // trigger timer event of the shortest arrival time
    
    // execute that process
    
    
    
    
    
}