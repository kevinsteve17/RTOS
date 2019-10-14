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

void AddQueueclient(processStruct* process)
{
    FCFSElement* newProcess = malloc(sizeof(FCFSElement));
    newProcess->clientTask = process;

    if (ProcessQueue->head != NULL)
    {
        ProcessQueue->tail->next = newProcess;
        ProcessQueue->tail = newProcess;
        ProcessQueue->tail->next = NULL;
    }
    else
    {
        ProcessQueue->head = newProcess;
        ProcessQueue->tail = newProcess;
        //ProcessQueue->head->next = NULL; 
    }

    // Update counter
    ProcessQueue->QueueSize += 1;
}

void RemoveQueueClient(int processID)
{
    FCFSElement* neededClient = ProcessQueue->head;
    FCFSElement* tempClient = ProcessQueue->head;

    if (neededClient->clientTask->ID == processID)
    {
        tempClient = ProcessQueue->head->next;
        ProcessQueue->head = tempClient;
        ProcessQueue->QueueSize -= 1;
        free(neededClient);
        return;
    }

    while (neededClient->next != NULL)
    {
        if (neededClient->clientTask->ID == processID)
        {
            tempClient = neededClient->next;
            free(neededClient);
            ProcessQueue->QueueSize -= 1;
            break;
        }

        tempClient = neededClient;
        neededClient =  tempClient->next;
    }
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

void RunFCFSScheduling(processInfo* processinfo, int processCount)
{
    // Create processes
    for(int i=0;i<processCount;i++)
    {
        processStruct* process =  malloc(sizeof(processStruct));
        process->ID = i;
        process->Arrivaltime = processinfo->ArrivalTime;
        process->BurstTime = processinfo->BurstTime;
        process->Process_State = CREATED;
        AddQueueclient(process);
    }
    
    // 
    
    
    
}