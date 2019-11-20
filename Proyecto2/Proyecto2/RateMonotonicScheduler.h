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
    
#include "Task.h"
    
    typedef struct RateMonotTask RMTask;
    
    struct RateMonotTask
    {
        Task TaskInfo;
        double CPU_Utilization;
        double SchedTest;
    };
    
    
    void CalculateCPU_Utilization(Task* tasks, int taskCount);
    void CalculateSchedTest(int tasksCount);
    void RunSchedTest();
    




#ifdef __cplusplus
}
#endif

#endif /* RATEMONOTONICSCHEDULER_H */

