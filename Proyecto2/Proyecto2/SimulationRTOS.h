/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationRTOS.h
 * Author: kevin
 *
 * Created on November 18, 2019, 9:33 PM
 */

#ifndef SIMULATIONRTOS_H
#define SIMULATIONRTOS_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct SimulationResultStruct RTResults;
    
    struct RTResults 
    {
        int* SchedulingSequence;
        int* CPU_Utiliztion_per_Task;
        int* SchedTestResult;
        int* TasksCount;
    };




#ifdef __cplusplus
}
#endif

#endif /* SIMULATIONRTOS_H */

