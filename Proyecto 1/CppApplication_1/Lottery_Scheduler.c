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
#include "progress_gui.h"

#define DEBUG

lotteryQueue* LotteryQueue;
lotteryClient* LotteryClient;

extern int CurrentRunningProcess;
extern int MaxTickets;

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
    LotteryQueue->QueueSize++;
}

/*
 * Delets process from client's queue
 */
void DeleteProcessClient(int id) 
{
    lotteryClient* client = LotteryQueue->head;
    lotteryClient* target = client, *prev;

    // If head node itself holds the key to be deleted 
    if (target != NULL && target->clientTask->ID == id) 
    { 
        LotteryQueue->head = target->next;   // Changed head 
        free(target);               // free old head
        LotteryQueue->QueueSize--;
        FreeTicketsForFinishedProcess(ticketAssignations, MaxTickets, id); 
        return; 
    } 

    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (target != NULL && target->clientTask->ID != id) 
    { 
        prev = target; 
        target = target->next; 
    } 
  
    // If key was not present in linked list 
    if (target == NULL) 
    {
        return; 
    }
  
    // Unlink the node from linked list 
    prev->next = target->next; 
  
    LotteryQueue->QueueSize--;
    FreeTicketsForFinishedProcess(ticketAssignations, MaxTickets, id); 

    free(target);  // Free memory 
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
 * Set tickets assigned to finished process as unassigned (-1)
 */
void FreeTicketsForFinishedProcess(int *ticketPool, int poolSize, int porcessID)
{
    int i;

    for (i = 0; i < poolSize; ++i) {
        if (ticketPool[i] == porcessID)
        {
            ticketPool[i] = -1;
        }
    } 
}

/*
 * Iterates over queued process to Assign lottery tickets based on its priority
 */
void AssignLotteryTickets(int totalTickets)
{
    lotteryClient* client = LotteryQueue->head;

    while (client != NULL)
    {
        AssignTicketsToProcess(ticketAssignations, totalTickets, client->clientTask->ID, client->clientTask->Priority);
        client = client->next;
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
    while (raffleCounter<MaxTickets)
    {
        int ticketToReturnIndx = tickets[raffleCounter];
        raffleCounter++;       
        int ticketToReturn = ticketPool[ticketToReturnIndx];
        
        if (ticketToReturn != -1)
        {
            ticketPool[ticketToReturnIndx] = -1;
            printf("WinningTicket: %i \n",ticketToReturn);
            return ticketToReturn;
        }
    }

    return -1; 
}

/*
 * Returns lotteryClient struct based on specified processID
 */
lotteryClient* SelectProcessFromLotteryQueue(int processID)
{
    lotteryClient* client = LotteryQueue->head;
    lotteryClient* target = NULL;

    while (client != NULL)
    {
        if (client->clientTask->ID == processID)
        {
            target = client;
            break;
        }
        
        client = client->next;
    }

    return target;
}

/*
 * Performs Lottery Scheduling on queued tasks
 */
void Schedule_NonPreemptive()
{    
    printf("Staring Lottery Scheduler: \n");
    int winnigProcess;
    lotteryClient* client;
    printf("QueueSize: %i \n", LotteryQueue->QueueSize);
    while (LotteryQueue->QueueSize > 0)
    {
        PrintLotteryQueue();
        winnigProcess = Lottery_(ticketAssignations, tickets);
        client = SelectProcessFromLotteryQueue(winnigProcess);
        
        // Notify GUI and move winning process to CPU
        CurrentRunningProcess = winnigProcess+1;
        MoveProcessBetweenQueues(READY_QUEUE,CPU_QUEUE, winnigProcess+1);
        
        client->clientTask->process_task = CalculatePi(client->clientTask->BurstTime);
        DeleteProcessClient(winnigProcess);       
    }

    printf("No more processes on queue \n");
    printf("Good bye! \n");
}



/*
 * Debug utility, prints ticket pool
 */
void PrintLotteryPool(int *ticketPool, int poolSize)
{
    int i;

    printf("Lottery Pool: \n");

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

/*
 * Debug utility, prints lottery queue
 */
void PrintLotteryQueue()
{
    lotteryClient* client = LotteryQueue->head;

    printf("LotteryClient Queue: \n");

    while (client != NULL)
    {
        printf("ID: %d \n",client->clientTask->ID);
        client = client->next;
    }
}

/*
 * Debug utility, executes lottery scheduling
 */
void DebugLotteryScheduler_01()
{
    // process creation
    processStruct* clientTask1 = malloc(sizeof(processStruct));
    processStruct* clientTask2 = malloc(sizeof(processStruct));
    processStruct* clientTask3 = malloc(sizeof(processStruct));

    clientTask1->ID = 17;
    clientTask1->Priority = 25;
    //clientTask1->process_task = CalculatePi();

    clientTask2->ID = 55;
    clientTask2->Priority = 6;
    //clientTask2->process_task = CalculatePi();

    clientTask3->ID = 8;
    clientTask3->Priority = 19;
    //clientTask3->process_task = CalculatePi();

    // init lottery scheduler
    InitLotteryScheduler();
    AddProcessClient(clientTask1);
    AddProcessClient(clientTask2);
    AddProcessClient(clientTask3);
    PrintLotteryQueue();
    
    // init lottery tickets pool
    InitLotteryTicketsPool(ticketAssignations, TOTAL_TICKETS);
    PrintLotteryPool(ticketAssignations, TOTAL_TICKETS);

    // assign tickets to process
    AssignLotteryTickets(TOTAL_TICKETS);
    PrintLotteryPool(ticketAssignations, TOTAL_TICKETS);

    // init Lottery
    InitTicketRaffle(tickets, TOTAL_TICKETS);
    PrintLotteryPool(tickets, TOTAL_TICKETS);

    //start scheduler
    Schedule_NonPreemptive();
}