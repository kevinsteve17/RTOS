/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUI_APIs.h
 * Author: maestria
 *
 * Created on October 16, 2019, 7:38 PM
 */

#ifndef PROGRESS_GUI_H
#define PROGRESS_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

// Global Constants
#define READY_QUEUE 0
#define CPU_QUEUE 1
    
/*
 * Function: PrintDebugMessageInDisplay
 * Summary: Function to print debug messages in the GUI scrolling window   
 */
void PrintDebugMessageInDisplay(char debugMessage[]);    // String

/*
 * Function: ModifyDisplayedConfigurationValues
 * Summary: Function to modify the labels that display the current 
 *          configuration read from the .txt config file   
 */
void ModifyDisplayedConfigurationValues(int algorithm,     // Lottery/FCFS
                                       int quantum,       // "34"
                                       int preemptive,    // Preemptive/NonPreemptive
                                       int totaltickets); // "122"


/*
 * Function: UpdateProcessDisplayedInfo
 * Summary: Function to update label and progress bar values
 */
void UpdateProcessDisplayedInfo(int queueNumber,              // See Constants values
                                int processNumber,            // integer value P1 (= 1)
                                double piValue,               // Accumulated value from Taylor series
                                double progressPercentValue); // double from 0 to 100

/*
 * Function: MoveProcessBetweenQueues
 * Summary: Function to move process "boxes" in the GUI between
 *          queues.
 */
void MoveProcessBetweenQueues(int fromQueueNumber, // See Constants values
                              int toQueueNumber,   // See Constants values
                              int processNumber);  // integer value P1 (= 1)

void HideProcessInCPU (int processNumber);

#ifdef __cplusplus
}
#endif

#endif /* PROGRESS_GUI_H */

