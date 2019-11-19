/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeastLaxityFirstScheduler.h
 * Author: kevin
 *
 * Created on November 18, 2019, 9:43 PM
 */

#ifndef LEASTLAXITYFIRSTSCHEDULER_H
#define LEASTLAXITYFIRSTSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Task.h"
    
    typedef struct LeastLAxityFirstTask LLFTask;
    
    struct LLFTask
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

#endif /* LEASTLAXITYFIRSTSCHEDULER_H */

