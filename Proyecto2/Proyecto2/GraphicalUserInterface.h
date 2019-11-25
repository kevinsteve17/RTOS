/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphicalUserInterface.h
 * Author: maestria
 *
 * Created on November 25, 2019, 10:45 AM
 */

#ifndef GRAPHICALUSERINTERFACE_H
#define GRAPHICALUSERINTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gtk/gtk.h>

// -----------------------------
// DISPLAY CONSTRUCTOR FUNCTIONS    
// -----------------------------
// Main function
void StartGUI (GtkApplication *app, gpointer user_data);
// Create main windows and grid
void CreateMainWindowAndGrid(GtkApplication *app);
// Create check buttons to select algorithms
void CreateAlgorithmsFrameAndControls();
// Create check buttons to select slides output format
void CreateResultsFrameAndControls();
// Create add/delete/start buttons
void CreateButtonControls();
// Create task spreadsheet
void CreateTaskSpreadsheet();

// ----------------------
// DISPLAY EVENT HANDLERS
// ----------------------
void toggle_RM(GtkWidget *gtk_control, gpointer data);
void toggle_EDF(GtkWidget *gtk_control, gpointer data);
void toggle_LLF(GtkWidget *gtk_control, gpointer data);
void toggle_Output(GtkWidget *gtk_control, gpointer data);
void DoScheduling(GtkWidget *button_start, gpointer data);
    
    
#ifdef __cplusplus
}
#endif

#endif /* GRAPHICALUSERINTERFACE_H */

