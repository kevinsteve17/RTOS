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
const int READY_QUEUE = 0;
const int WAIT_QUEUE = 1;
const int DONE_QUEUE = 2;
const int CPU_QUEUE = 3;
    
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
void ModifyDisplayedConfigurationValues(char algorithm_string[],     // Lottery/FCFS
                                       char quantum_string[],       // "34"
                                       char preemptive_string[],    // Preemptive/NonPreemptive
                                       char totaltickets_string[]); // "122"

/*
 * Function: MoveAndUpdateProcessBetweenQueues
 * Summary: Function to move process "boxes" in the GUI between
 *          queues. Also updates values of interest.
 */
void MoveAndUpdateProcessBetweenQueues(int fromQueueNumber,          // See Constants values
                                       int toQueueNumber,            // See Constants values
                                       int processNumber,            // integer value P1 (= 1)
                                       char textValue[],             // Accumulated value from Taylor series
                                       double progressPercentValue); // double from 0 to 100

/*
 * Function: UpdateProcessDisplayedInfo
 * Summary: Function to update label and progress bar values
 */
void UpdateProcessDisplayedInfo(int queueNumber,              // See Constants values
                                int processNumber,            // integer value P1 (= 1)
                                char textValue[],             // Accumulated value from Taylor series
                                double progressPercentValue); // double from 0 to 100

/*
 * Function: MoveProcessBetweenQueues
 * Summary: Function to move process "boxes" in the GUI between
 *          queues.
 */
void MoveProcessBetweenQueues(int fromQueueNumber, // See Constants values
                              int toQueueNumber,   // See Constants values
                              int processNumber);  // integer value P1 (= 1)

#ifdef __cplusplus
}
#endif

#endif /* PROGRESS_GUI_H */

