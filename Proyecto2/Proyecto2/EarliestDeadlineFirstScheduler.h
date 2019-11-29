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

// EDF
void EdfCalculateSchedTest(Task* task, int tasksCount);
bool EdfRunSchedTest();
void EdfStartSched(Task* task, int tasksCount);
void RunEdfSched();

// ready queue
void AddTaskToReadyQueue(Task* task, int simPeriod);
bool RemoveCompletedTasks();
void InitReadyQueue(Task* task, int tasksCount);
bool AddNewTasks(int t);
void UpdateTaskComputationTime(int id);
taskClient* GetTaskFromReadyQueue();

// debug utils
void EdfPopulateTaskstructures();
void PrintMissedDeadlineMessage(taskClient* task, int t);

#ifdef __cplusplus
}
#endif

#endif /* EARLIESTDEADLINEFIRSTSCHEDULER_H */

