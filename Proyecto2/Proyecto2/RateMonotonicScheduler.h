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
    
    struct RMTask
    {
        Task TaskInfo;
        int CPU_Utilization;
        int SchedTest;
    };
    
    
    void CalculateCPU_Utilization();
    void CalculateSchedTest();
    void RunSchedTest();
    




#ifdef __cplusplus
}
#endif

#endif /* RATEMONOTONICSCHEDULER_H */

