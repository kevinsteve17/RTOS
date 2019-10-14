/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoundRobinScheduler.h
 * Author: kevin
 *
 * Created on October 6, 2019, 5:21 PM
 */

#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H

#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

// Structures 

typedef struct RoundRobin_list RoundRobinList;
typedef struct RoundRobin_client RoundRobinClient;
int Quantum;

struct RoundRobinList 
{
    RoundRobinClient* head;
    RoundRobinClient* tail;
    int ListSize;
}

struct RoundRobinClient 
{
    processStruct* clientTask;
    RoundRobinClient* next;
}


RoundRobinList* RRList;

void RRInit(int quantum, processStruct* process);
void RRAddClient();
void RRSwitchContext();
void RREnd();
void RRQuantumEnd();
int RRClientsCount();







#ifdef __cplusplus
}
#endif

#endif /* ROUNDROBINSCHEDULER_H */

