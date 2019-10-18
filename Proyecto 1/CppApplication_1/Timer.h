/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Timer.h
 * Author: kevin
 *
 * Created on October 13, 2019, 9:11 PM
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

void SetSoftTimerHandler();
int IsQuantumOver();
void StopSoftTimer();
void StartSoftTimer(int freq_nanosecs);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */

