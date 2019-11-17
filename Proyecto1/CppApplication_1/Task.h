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

#ifndef TASK_H
#define	TASK_H

#include <stdio.h>
#include <setjmp.h>
#include "Utilities.h"

typedef struct process_struct processStruct;
typedef struct process_info processInfo;

enum PROCESS_STATE
{
     FINISHED,
     READY,
     RUNNING,
     CREATED,
     WAITING
};

struct process_info
{
    int ArrivalTime;
    int BurstTime;
};

struct process_struct
{
    int ID;
    int Priority;
    //int Tickets[MAX_TICKETS];
    int Quantum; 
    int Process_State;
    int Arrivaltime;
    int BurstTime;
    void (*process_task)(void*);
    void *arguments;
    sigjmp_buf environment;
};

#endif	/* TASK_H */