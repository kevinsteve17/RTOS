/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scheduler.c
 * Author: kevin
 *
 * Created on October 5, 2019, 12:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Task.h"
#include "FCFSScheduler.h"

typedef struct SSettings Settings;

enum Algorithm
{
    Lottery,
    FCFS,
    SJF,
    RR,
    PS,
    PSRR,
    MQF,
    MFQS
};

// Preemtive Mode Enum
enum Mode
{
    Preemtive,
    NonPreemtive
};

// Settings struct 
struct Settings
{
    int AlgorithmScheduling;
    int PMode;
    int ProcessCount;
    int TimeExec;
    int WorkLoad;
    int Tickets;
    int Quantum;
    int MQFSQueues;
};


Settings* SchedSettings; 

void ConstructSettings(char* lineTokenized)
{



}

void ReadFile()
{
    char* tok;
    char line, fileName[256];
    const char equal[2] = "=";
    FILE* settings;

     // fileName = "SchedulerSettings.txt";

    settings = fopen(fileName, "r");

    if (settings ==  NULL)
    {
        perror("Error while opening the file. \n");
        exit(EXIT_FAILURE);
    }

    while((line = fgetc(settings))!= EOF)
    {
        tok = strtok(line, equal);
        for(int i=0; i<sizeof(tok); i++)
        {
            if (strcmp(tok[i],"Algorithm"))
            {
                
            }

            

        }

    }

    fclose(settings);




}

void CreateProcess(int processCount)
{

}

/*
 * Main function
 */
int main(int argc, char** argv) 
{
    // Capture arguments
    // Select scheduler
    // Create processes

    processStruct* clientTask1 =  malloc(sizeof(processStruct));
    processStruct* clientTask2 = malloc(sizeof(processStruct));
    processStruct* clientTask3 = malloc(sizeof(processStruct));
    
    clientTask1->ID = 1;
    clientTask1->Process_State=0;
    clientTask1->arguments = NULL;
    clientTask1->process_task = CalculatePi();

    clientTask2->ID = 2;
    clientTask2->Process_State=0;
    clientTask2->arguments = NULL;
    clientTask2->process_task = CalculatePi();
    
/*
    clientTask1->ID = 3;
    clientTask1->Process_State=0;
    clientTask1->arguments = NULL;
    clientTask1->process_task = CalculatePi();
*/

    //clientTask2->process_task = CalculatePi();

    InitFCFSSched();
    AddQueueclient(clientTask1);
    AddQueueclient(clientTask2);
    //AddQueueclient(clientTask3);
    QueueSize();
    PrintQueue();
    
    RemoveQueueClient(1);
    
    QueueSize();
    PrintQueue();


    return (EXIT_SUCCESS);
}

