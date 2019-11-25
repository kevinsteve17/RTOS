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
    
    void LLF_PopulateDummyTasks();
    int  LLF_CalculateLeastCommonMultiple();
    int  LLF_CalculateTaskLaxity();
    int  LLF_TaskWithLeastLaxity();
    void LLF_RunSchedTest();



#ifdef __cplusplus
}
#endif

#endif /* LEASTLAXITYFIRSTSCHEDULER_H */

