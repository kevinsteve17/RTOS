/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lottery_Scheduler.h
 * Author: kevin
 *
 * Created on October 6, 2019, 4:22 PM
 */

#ifndef LOTTERY_SCHEDULER_H
#define LOTTERY_SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <Task.h>

#ifdef __cplusplus
extern "C" {
#endif

// Structures

typedef struct Lottery_queue lotteryQueue;
typedef struct Lottery_client lotteryClient;

// Client tickets
int lotteryTickets;


struct Lottery_queue 
{
    lotteryClient* head;
    lotteryClient* tail;
    int QueueSize;
}

struct Lottery_client 
{
    processStruct* clientTask;
    lotteryClient* next;
    int clientTickets;
}

void LotterySchedInit();
void LotterySchedEnd();
void AddLotteryClient();
void LotterySwitchContext();
void SetLotteryTickets();
void NextLotteryClient();
void RemoveLotteryClient();
lotteryClient GetLotteryClient();




#ifdef __cplusplus
}
#endif

#endif /* LOTTERY_SCHEDULER_H */

