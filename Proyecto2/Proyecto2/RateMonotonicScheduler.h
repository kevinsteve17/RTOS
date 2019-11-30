/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RateMonotonicScheduler.h
 * Author: kevin
 *
 * Created on November 18, 2019, 8:04 PM
 */

#ifndef RATEMONOTONICSCHEDULER_H
#define RATEMONOTONICSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "Task.h"

    
    typedef struct RMQueueStruct Queue;
    typedef struct RMClient RMTaskClient;
    typedef struct SchedulingResult RMSchedResult;
    
    struct RMQueueStruct 
    {
        RMTaskClient* head;
        RMTaskClient* tail;
        int QueueSize;
    };

    struct RMClient 
    {
        Task* rMTask;
        RMTaskClient* next;
    };
    
    void ConvertTastToRMTask(Task* tasks);
    int GetHighestPriority(Task* tasks);
    bool CalculateCPU_Utilization(Task* tasks);
    bool CalculateSchedTest();
    void RunRMSchedTest();
    bool MonitorDeadlines(int t);
    bool VerifyRepeatedTasksIdsInQueue(int id, int t);
    void AddRMTaskToReadyQueue(Task* task, int simPeriod);
    bool RemoveRMCompletedTasks();
    void InitRMReadyQueue(Task* task, int tasksCount);
    bool AddNewRMTasks(int t);
    void UpdateRMTaskComputationTime(int id);
    RMTaskClient* GetRMTaskFromReadyQueue();
    void PrintRMMissedDeadlineMessage(RMTaskClient* task, int t);
    
    void RunRMSched();
    





#ifdef __cplusplus
}
#endif

#endif /* RATEMONOTONICSCHEDULER_H */

