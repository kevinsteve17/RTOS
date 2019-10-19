/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */ 

/* 
 * File:   Lottery_Scheduler.h
 * Author: FPK
 *
 * Created on October 16, 2019
 */

#ifndef LOTTERY_SCHEDULER_H
#define LOTTERY_SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "Utilities.h"

#ifdef __cplusplus
extern "C" {
#endif

// Structures
typedef struct Lottery_queue lotteryQueue;
typedef struct Lottery_client lotteryClient;

// tickets and assigned process, -1 means not assigned
// index (ticket number) -> |0 |1 |2 |3 |4 |5 |6 |7 |
// assigned procces      -> |60|60|60|60|04|04|17|-1|
int ticketAssignations[MAX_TICKETS];

// raffled tickets
int tickets[MAX_TICKETS];

// used as raffle control
int raffleCounter;

struct Lottery_queue 
{
    lotteryClient* head;
    lotteryClient* tail;
    int QueueSize;
};

struct Lottery_client 
{
    processStruct* clientTask;
    lotteryClient* next;
    int clientTickets;
};

/*void LotterySchedEnd();
void LotterySwitchContext();
void SetLotteryTickets();
void RemoveLotteryClient();
lotteryClient GetLotteryClient();*/

// Lottery scheduler
void InitLotteryScheduler();
void AddProcessClient(processStruct* process);
void RemoveLotteryClient();
void AssignLotteryTickets(int totalTickets);
void Schedule_NonPreemptive();
void DeleteProcessClient(int id);
lotteryClient* SelectProcessFromLotteryQueue(int processID);

// Lotery Utils
//void StartLotteryScheduling(Settings* settings);
void InitLotteryTicketsPool(int *ticketPool, int poolSize);
void AssignTicketsToProcess(int *ticketPool, int poolSize, int procID, int procPriority);
void FreeTicketsForFinishedProcess(int *ticketPool, int poolSize, int porcessID);
void InitTicketRaffle(int *tickets, int ticketPoolSize);
int Lottery_(int *ticketPool, int *tickets);

// Debug
void PrintLotteryPool(int *ticketPool, int poolSize);
void DebugLotteryUtils();
void PrintLotteryQueue();
void DebugLotteryScheduler_01();

#ifdef __cplusplus
}
#endif

#endif /* LOTTERY_SCHEDULER_H */

