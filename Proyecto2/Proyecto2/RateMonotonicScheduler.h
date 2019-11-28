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

    
    typedef struct RateMonotonicSched RMSchedulerTask;
    typedef struct RMQueueStruct Queue;
    typedef struct RMClient Element;
    
    struct RateMonotonicSched
    {
        Task task;
        int currentExecTime;
        int nextDeadline;
        int deadlineMet;
        int scaleFactor;
    };
    
    struct RMQueueStruct 
    {
        Element* head;
        Element* tail;
        int QueueSize;
    };

    struct RMClient 
    {
        RMSchedulerTask* rMTask;
        Element* next;
    };
    
    void ConvertTastToRMTask(Task* tasks);
    int GetHighestPriority(Task* tasks);
    bool CalculateCPU_Utilization(Task* tasks);
    bool CalculateSchedTest();
    void RunSchedTest();
    
    void InitFCFSSched();
    void Push(RMSchedulerTask* process);
    Element* Pop();
    void PrintQueue();
    void QueueSize();




#ifdef __cplusplus
}
#endif

#endif /* RATEMONOTONICSCHEDULER_H */

