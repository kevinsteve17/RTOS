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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "Lottery_Scheduler.h"

lotteryQueue* LotteryQueue;
lotteryClient* LotteryClient;

/*
 * Inits lottery queue
 */
void InitLotteryScheduler()
{
    // initialize the Queue
    LotteryQueue = malloc(sizeof(lotteryQueue));
    LotteryQueue->head =  NULL;
    LotteryQueue->tail = NULL;
    LotteryQueue->QueueSize = 0;
}

/*
 * Adds process to client's queue
 */
void AddProcessClient(processStruct* process)
{
    lotteryClient* newProcess = malloc(sizeof(lotteryClient));
    newProcess->clientTask = process;

    if (LotteryQueue->tail != NULL)
    {
        newProcess->next = LotteryQueue->head;
        LotteryQueue->head = newProcess;
    }
    else
    {
        LotteryQueue->tail = newProcess;
        LotteryQueue->head = newProcess;
        LotteryQueue->tail->next = NULL;
    }

    // Update counter
    LotteryQueue->QueueSize += 1;
}

/*
 * Inits lottery tickets as unassigned (-1)
 */
void InitLotteryTicketsPool(int *ticketPool, int poolSize)
{
    int i;

    for (i = 0; i < poolSize; ++i) {
        ticketPool[i] = -1;
    } 
}

/*
 * Assigns lottery tickets to process based on its priority
 */
void AssignTicketsToProcess(int *ticketPool, int poolSize, int procID, int procPriority)
{
    bool exit = false;
    int i = 0;

    for (i = 0; i < poolSize; i++) {
        if (ticketPool[i] == -1)
        {
            ticketPool[i] = procID;
            procPriority--;             
        }
        
        if (procPriority == 0)
        {
            break;
        }
    }
}

/*
 * Creates a Non-repeating random ticket array
 */
void InitTicketRaffle(int *tickets, int poolSize)
{
    raffleCounter = 0;

    int n, k;
    int count;
    int i=0;
    int size = poolSize-1;

    srand(time(NULL));

    for(count=0;count<size;count++){
        tickets[count]=rand()%size+1;
    }

    while(i<size){
        int r=rand()%size+1;

        for (n = 0; n < i; n++)
        {
            if(tickets[n]==r){
                break;
            }
        }
        if(n==i){
            tickets[i++]=r;
        }
    }

    return 0;
}

/*
 * Lottery. Returns raffled ticked
 */
int Lottery_(int *ticketPool, int *tickets)
{
    if (raffleCounter<TOTAL_TICKETS)
    {
        int ticketToReturnIndx = tickets[raffleCounter];
        raffleCounter++;       
        int ticketToReturn = ticketPool[ticketToReturnIndx];
        ticketPool[ticketToReturnIndx] = -1;
        return ticketToReturn;
    }
    else
    {
        return -1;
    }   
}

/*
 * Debug utility, prints ticket pool
 */
void PrintLotteryPool(int *ticketPool, int poolSize)
{
    int i;

    for (i = 0; i < poolSize; ++i) {
        printf("Ticket: %i \n", ticketPool[i]);
    }    
}    

/*
 * Debug utility, exercises lottery utils
 */
void DebugLotteryUtils()
{
    InitLotteryTicketsPool(ticketAssignations, TOTAL_TICKETS);
    AssignTicketsToProcess(ticketAssignations, TOTAL_TICKETS, 666, 33);
    AssignTicketsToProcess(ticketAssignations, TOTAL_TICKETS, 3, 5);
    AssignTicketsToProcess(ticketAssignations, TOTAL_TICKETS, 11, 12);
    PrintLotteryPool(ticketAssignations, TOTAL_TICKETS);
    printf("Raffle init \n");
    InitTicketRaffle(tickets, TOTAL_TICKETS);
    PrintLotteryPool(tickets, TOTAL_TICKETS);

    for (int i = 0; i < TOTAL_TICKETS; ++i) {
        int proccesToexec = Lottery_(ticketAssignations, tickets);
        printf("--> Process to Execute: %i \n", proccesToexec);
    }
}