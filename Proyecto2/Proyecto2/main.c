/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: kevin
 *
 * Created on November 17, 2019, 3:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Task.h"
#include "TexFileGenerator.h"
#include "GraphicalUserInterface.h"
#include "LeastLaxityFirstScheduler.h"


// Control variables (0=Off, 1=On)
extern int isRmEnabled;                 // Rate Monotonic Enable
extern int isEdfEnabled;                // Earliest Deadline First Enable
extern int isLlfEnabled;                // Least Laxity Enable
extern int isSinglePageOutputEnabled;   // Single page Latex output

// Tasks information
extern Task tasks[6];                   // Task struct array, contains GUI input data
extern int maxNumberOfTasks;            // Hardcoded to 6
extern int numberOfTasks;               // Number of tasks with period != 0
extern int leastCommonMultiple;         // LCM of tasks with period != 0



// *****************************************************************************
// *****************************************************************************
void executeScheduler(int tasksID, int execTime, int deadline, int period)
{
    Task newTask;
    
    newTask.Id = tasksID;
    newTask.ComputationTime = execTime;
    newTask.Period = period;
    newTask.Deadline = deadline;
}



// *****************************************************************************
// *****************************************************************************
int main(int argc, char** argv) 
{ 
    //////////////////////// Debug
    GenerateTexFile();
    //////////////////////// Debug End
         
    
    // Start Debug Display
    GtkApplication *app;
    int status;

    // Constructor
    app = gtk_application_new ("Proyecto2.TheScheduler", G_APPLICATION_FLAGS_NONE);

    // Connect application with "activate" function (activate is not executed at this time)
    g_signal_connect (app, "activate", G_CALLBACK (StartGUI), NULL);

    // Run the GUI (calls the connected StartGUI function)
    status = g_application_run (G_APPLICATION (app), argc, argv);

    // CleanUp
    g_object_unref (app);
    
    
    //return status;
    return (EXIT_SUCCESS);
}



// *****************************************************************************
// *****************************************************************************
void DoScheduling(GtkWidget *gtk_control, gpointer data) 
{
    printf("Function call: DoScheduling()\n");
    
    // Read values from debug display spreadsheet grid
    ReadSpreadsheet();
    // Calculate LCM
    CalculateLeastCommonMultiple();
    
    // Start Scheduling
    
    if (isRmEnabled == 1)
    {
        //void CalculateCPU_Utilization(Task* tasks, int taskCount);
        //void CalculateSchedTest(int tasksCount);
        //void RunSchedTest();
    }
    if (isEdfEnabled == 1)
    {
        //void CalculateEdfSchedTest(Task* task, int tasksCount);
        //bool RunEdfSchedTest();
        //void PerformEdfSched(Task* task, int tasksCount);
    }
    if (isLlfEnabled == 1)
    {
        LLF_RunSchedTest();
    }
}


