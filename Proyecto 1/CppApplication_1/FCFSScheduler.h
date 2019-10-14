/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FCFSScheduler.h
 * Author: kevin
 *
 * Created on October 13, 2019, 2:17 PM
 */

#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Task.h"


typedef struct FCFSStruct FCFSQueue;
typedef struct FCFSClient FCFSElement;

struct FCFSStruct 
{
    FCFSElement* head;
    FCFSElement* tail;
    int QueueSize;
};

struct FCFSClient 
{
    processStruct* clientTask;
    FCFSElement* next;
};

void InitFCFSSched();
void AddQueueclient(processStruct* process);
void RemoveQueueClient(int processID);
void PrintQueue();
void QueueSize();




#ifdef __cplusplus
}
#endif

#endif /* FCFSSCHEDULER_H */

