/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EarliestDeadlineFirstScheduler.h
 * Author: kevin
 *
 * Created on November 18, 2019, 9:42 PM
 */

#ifndef EARLIESTDEADLINEFIRSTSCHEDULER_H
#define EARLIESTDEADLINEFIRSTSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif
    
    #include "Task.h"
    
    typedef struct EarliestDeadlineFirstTask EDFTask;
    
    struct EDFTask
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

#endif /* EARLIESTDEADLINEFIRSTSCHEDULER_H */

