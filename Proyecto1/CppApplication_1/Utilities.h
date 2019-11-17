/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utilities.h
 * Author: kevin
 *
 * Created on October 16, 2019, 4:49 PM
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define WORKLOAD 50
#define MINPROCESSES 5
#define MAX_TICKETS 500
#define TOTAL_TICKETS 50

typedef struct SSettings Settings;

// Settings struct 
struct SSettings
{
    int SchedulingAlgorithm;
    int PMode;
    int ProcessCount;
    char* ArrivalTime;
    char* WorkLoad;
    int Tickets;
    int Quantum;
    char* Priority;
};


#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */

