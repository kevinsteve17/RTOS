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
int main(int argc, char** argv) {
    
    GenerateTexFile();
    return (EXIT_SUCCESS);
}

