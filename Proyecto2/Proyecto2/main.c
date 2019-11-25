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


void executeScheduler(int tasksID, int execTime, int deadline, int period)
{
    Task newTask;
    
    newTask.Id = tasksID;
    newTask.ComputationTime = execTime;
    newTask.Period = period;
    newTask.Deadline = deadline;
    
    
}

/*
 * 
 */
int main(int argc, char** argv) 
{ 
    //////////////////////// Debug
    GenerateTexFile();
    //////////////////////// Debug End
         
    /*
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
   */
    
    //return status;
    return (EXIT_SUCCESS);
}

