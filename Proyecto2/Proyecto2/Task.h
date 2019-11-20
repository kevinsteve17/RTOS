/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Task.h
 * Author: kevin
 *
 * Created on November 18, 2019, 8:05 PM
 */

#ifndef TASK_H
#define TASK_H

#ifdef __cplusplus
extern "C" {
#endif

    
    typedef struct SchedTask Task;
    
    struct SchedTask
    {
        int Id;
        int ComputationTime;
        int Deadline;
        int Period;
    };



#ifdef __cplusplus
}
#endif

#endif /* TASK_H */

