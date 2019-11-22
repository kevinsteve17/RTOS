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
    
    #include "Task.h"
    
    typedef struct EarliestDeadlineFirstTask EDFTask;
    
    struct EarliestDeadlineFirstTask
    {
        Task TaskInfo;
        int CPU_Utilization;
        int SchedTest;
    };
    
    void CalculateEdfSchedTest(Task* task, int tasksCount);
    bool RunEdfSchedTest();
    void PerformEdfSched(Task* task, int tasksCount);


#ifdef __cplusplus
}
#endif

#endif /* EARLIESTDEADLINEFIRSTSCHEDULER_H */

