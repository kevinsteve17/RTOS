/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EarliestDeadlineFirstScheduler.h
 * Author: FPK
 *
 * Created on November 21, 2019, 11:02 PM
 */

#ifndef EARLIESTDEADLINEFIRSTSCHEDULER_H
#define EARLIESTDEADLINEFIRSTSCHEDULER_H
#define NUM_OF_TASKS 3

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>    
#include "Task.h"

// Structures
typedef struct ready_queue readyQueue;
typedef struct task_client taskClient;
typedef struct SchedulingResult EDFTask;

struct ready_queue 
{
    taskClient* head;
    taskClient* tail;
    int QueueSize;
};

struct task_client 
{
    Task* clientTask;
    taskClient* next;
};

void EdfCalculateSchedTest(Task* task, int tasksCount);
bool EdfRunSchedTest();
void EdfStartSched(Task* task, int tasksCount);
void AddTaskToReadyQueue(Task* task, int simPeriod);
taskClient* GetTaskFromReadyQueue();

// debug utils
void EdfPopulateTaskstructures();
void edf_test();


#ifdef __cplusplus
}
#endif

#endif /* EARLIESTDEADLINEFIRSTSCHEDULER_H */

