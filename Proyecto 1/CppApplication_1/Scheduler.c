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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "progress_gui.h"
#include "Task.h"
#include "FCFSScheduler.h"
#include "Utilities.h"
#include "Timer.h"
#include "Lottery_Scheduler.h"

// Global Variables
int GuiWindowWidth = 100;
int GuiWindowHeight = 100;
int TotalProcessesNumber = 5;

// Main window and grid
GtkWidget *window;
GtkWidget *grid_main;

// Configuration - controls
GtkWidget *frame_configuration;
GtkWidget *grid_configuration;
GtkWidget *label_algorithm;
GtkWidget *label_algorithm_value;
GtkWidget *label_quantum;
GtkWidget *label_quantum_value;
GtkWidget *label_preemtive;
GtkWidget *label_preemtive_value;
GtkWidget *label_totaltickets;
GtkWidget *label_totaltickets_value;

// Event Log - controls
GtkTextBuffer *buffer_eventlog;
GtkTextIter end_iter_eventlog;
GtkWidget *frame_eventlog;
GtkWidget *textview_eventlog;
GtkWidget *scrolled_eventlog;
GtkTextMark *mark;

// Queue - controls
GtkWidget *frame_queue[4];
GtkWidget *grid_queue[4];
GtkWidget *frame_processborder[4][25];
GtkWidget *grid_processboarder[4][25];
GtkWidget *progressbar_process[4][25];

// GUI - Color and Font overrides
PangoFontDescription *font_desc;
GdkColor color;


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
    int SchedulingAlgorithm;
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
            if (strcmp(tok[i],"#Algorithm"))
            {
                
            }
            else if(strcmp(tok[i],"#Mode"))
            {
                
            }
            else if(strcmp(tok[i],"#ProcessesCount"))
            {
                
            }
            else if(strcmp(tok[i],"#TimeExec"))
            {
                
            }
            

            

        }

    }

    fclose(settings);




}

/*
void CreateProcess(int processCount)
{
    printf("Creating processes");

}
*/

void CreateProcess()
{
    //printf("Creating processes");
    PrintDebugMessageInDisplay("Creating processes");

}

// *****************************************************************************
// *****************************************************************************
static void DoScheduling(GtkWidget *button_start, gpointer data) 
{
    // ---------------------------
    // Start of Scheduling Program .... un ejemplo de como actualizar el GUI
    // ---------------------------
    
    // Read configuration file
    PrintDebugMessageInDisplay ("Reading config file ...");
    //ReadConfigurationFile();
    
    sleep(1);
    // Update configuration controls in GUI
    ModifyDisplayedConfigurationValues("Lottery", "114", "Preemptive", "1045");

    sleep(1);
    // Configure Soft timer handler
    PrintDebugMessageInDisplay ("Configuring quantum soft timer handler...");
    SetQuantumSoftTimerHandler();
    
    sleep(1);
    // Start Scheduling
    //LotteryScheduling();
    MoveAndUpdateProcessBetweenQueues(READY_QUEUE,WAIT_QUEUE,1,"0.1",5);
    MoveAndUpdateProcessBetweenQueues(READY_QUEUE,DONE_QUEUE,5,"3.14",100);
    MoveAndUpdateProcessBetweenQueues(READY_QUEUE,CPU_QUEUE,2,"0.135",27);
    
    //----------------------------------------------
    // Contenido de MAIN antes de cambios de RIVERA
    //----------------------------------------------
    
    // Capture arguments
    // Select scheduler
    // Create processes
    
    SetProcessSoftTimerHandler(1, CreateProcess);
    StartProcessSoftTimer(1, 2000000000);


    
    processStruct* clientTask1 =  malloc(sizeof(processStruct));
    processStruct* clientTask2 = malloc(sizeof(processStruct));
    processStruct* clientTask3 = malloc(sizeof(processStruct));
    

    clientTask1->ID = 1;
 /*   clientTask1->Process_State=0;
    clientTask1->arguments = NULL;
    clientTask1->process_task = CalculatePi();
*/
    clientTask2->ID = 2;
/*    clientTask2->Process_State=0;
    clientTask2->arguments = NULL;
    clientTask2->process_task = CalculatePi();
*/
    
/*
    clientTask1->ID = 3;
    clientTask1->Process_State=0;
    clientTask1->arguments = NULL;
    clientTask1->process_task = CalculatePi();
*/

    //clientTask2->process_task = CalculatePi();

    InitFCFSSched();
    Push(clientTask1);
    Push(clientTask2);
    //AddQueueclient(clientTask3);
    QueueSize();
    PrintQueue();
    
    Pop();
    
    QueueSize();
    PrintQueue();
    
}

// *****************************************************************************
// *****************************************************************************
void PrintDebugMessageInDisplay(char debugMessage[])
{
  // Local variables
  char changeOfLine[] = "\n";
  
  char *result = malloc(strlen(debugMessage) + strlen(changeOfLine) + 1); // +1 for the null-terminator
  strcpy(result, debugMessage);
  strcat(result, changeOfLine);
  
  // Insert message in text buffer
  gtk_text_buffer_insert(buffer_eventlog, &end_iter_eventlog, result, -1);
  
  // Get mark position and move text view iterator
  mark = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER(buffer_eventlog), "end");
  
  // Focus viewer in Mark's position
  gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW(textview_eventlog), mark);
  
  // Force controls update
  while(gtk_events_pending())
  {
    gtk_main_iteration();
  }
}

// *****************************************************************************
// *****************************************************************************
void ModifyDisplayedConfigurationValues(char algorithm_string[],
                                       char quantum_string[],
                                       char preemptive_string[],
                                       char totaltickets_string[])
{
    // Update labels
    gtk_label_set_text(GTK_LABEL(label_algorithm_value), algorithm_string);
    gtk_label_set_text(GTK_LABEL(label_quantum_value), quantum_string);  
    gtk_label_set_text(GTK_LABEL(label_preemtive_value), preemptive_string);  
    gtk_label_set_text(GTK_LABEL(label_totaltickets_value), totaltickets_string);  
    
    // Debug message
    PrintDebugMessageInDisplay("Updating config panel ...");
}

// *****************************************************************************
// *****************************************************************************
void MoveAndUpdateProcessBetweenQueues(int fromQueueNumber,
                                       int toQueueNumber,
                                       int processNumber,
                                       char textValue[],
                                       double progressPercentValue)
{
    // Hide Process
    gtk_widget_hide(frame_processborder[fromQueueNumber][processNumber-1]);
    
    // Update label and progress bar values
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar_process[toQueueNumber][processNumber-1]), textValue);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar_process[toQueueNumber][processNumber-1]), progressPercentValue/100);
    
    // Reveal hidden control
    gtk_widget_show(frame_processborder[toQueueNumber][processNumber-1]);
    
    // Debug Message
    char message[100];
    snprintf(message, 100, "Moving P%d from queue %d to %d. Progress = %d%%", processNumber, fromQueueNumber, toQueueNumber, (int)progressPercentValue);
    PrintDebugMessageInDisplay(message);
}

// *****************************************************************************
// *****************************************************************************
void UpdateProcessDisplayedInfo(int queueNumber,
                                int processNumber,
                                char textValue[],
                                double progressPercentValue)
{
    // Update label and progress bar
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar_process[queueNumber][processNumber]), textValue);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar_process[queueNumber][processNumber]), progressPercentValue/100);
    
    // Debug message
    char message[100];
    snprintf(message, 100, "Updating P%d. Progress = %d%%", processNumber, (int)progressPercentValue);
    PrintDebugMessageInDisplay(message);
}

// *****************************************************************************
// *****************************************************************************
void MoveProcessBetweenQueues(int fromQueueNumber,
                              int toQueueNumber,
                              int processNumber)
{
    // Hide Process
    gtk_widget_hide(frame_processborder[fromQueueNumber][processNumber-1]);
    // Reveal hidden control
    gtk_widget_show(frame_processborder[toQueueNumber][processNumber-1]);
    
    // Debug message
    char message[100];
    snprintf(message, 100, "Moving P%d from queue %d to %d", processNumber, fromQueueNumber, toQueueNumber);
    PrintDebugMessageInDisplay(message);
}

// *****************************************************************************
// *****************************************************************************
static void HideProcessesInQueue(int queueNumber)

{
    // Hide Processes in selected queue ... used for GUI init
    for (int j=0; j<TotalProcessesNumber; j++)
    {
        gtk_widget_hide(frame_processborder[queueNumber][j]);
    }
}

// *****************************************************************************
// *****************************************************************************
static void CreateProcessesQueue(GtkWidget *frame_queue[],
                                 GtkWidget *grid_queue[],
                                 char queueName[],
                                 int queueNumber)
{
    int i = queueNumber;
    
    // Create Queue Frame
    frame_queue[i] = gtk_frame_new(queueName);
    gtk_widget_set_size_request(frame_queue[i], 80, 300);

    // Add Queue Frame to main grid
    gtk_grid_attach(GTK_GRID(grid_main), frame_queue[i], i+1,0,1,2);

    // Create inner grid to hold the X processes in the queue
    grid_queue[i] = gtk_grid_new();

    // Add inner grid to Queue Frame
    gtk_container_add (GTK_CONTAINER (frame_queue[i]), grid_queue[i]); 
}



// *****************************************************************************
// *****************************************************************************
static void CreateProcessesInQueue(GtkWidget *frame_processborder[][25],
                                   GtkWidget *grid_processboarder[][25],
                                   GtkWidget *progressbar_process[][25],
                                   int queueNumber)
{      
    // Local variables
    char processName[10];
    
    for (int i=0 ; i<TotalProcessesNumber ;i++)
    {
        // Strings are hard to deal with in C ...
        snprintf(processName, 12, "P%d", i+1);
        
        // Create Process Frame
        frame_processborder[queueNumber][i] = gtk_frame_new(processName);
        
        gtk_widget_set_size_request(frame_processborder[queueNumber][i], 80, 20);
        
        // Add Frame to main grid
        gtk_grid_attach(GTK_GRID(grid_queue[queueNumber]), frame_processborder[queueNumber][i], 0,i,1,1);

        // Create Process Grid contained (for label + progress bar)
        grid_processboarder[queueNumber][i] = gtk_grid_new();

        // Add Process Grid to Process Frame
        gtk_container_add (GTK_CONTAINER (frame_processborder[queueNumber][i]), grid_processboarder[queueNumber][i]);

        // Add Process Bar control to Grid
        progressbar_process[queueNumber][i] = gtk_progress_bar_new();
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar_process[queueNumber][i]), 0);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar_process[queueNumber][i]), "N/A");
        gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progressbar_process[queueNumber][i]), TRUE);
        gtk_grid_attach(GTK_GRID(grid_processboarder[queueNumber][i]), progressbar_process[queueNumber][i], 0,1,1,1);
        
        // (WARNINGS!) Modify the font size for the widgets 
        //font_desc = pango_font_description_from_string ("Sans 6");
        //gtk_widget_override_font(frame_processborder[queueNumber][i], font_desc);
        //gtk_widget_override_font(progressbar_process[queueNumber][i], font_desc);
        
        // (WARNINGS!) Modify the color for the widgets 
        //gdk_color_parse ("light blue", &color);
        //gtk_widget_modify_bg (GTK_WIDGET(grid_processboarder[queueNumber][i]), GTK_STATE_NORMAL, &color);
    }
}

// *****************************************************************************
// *****************************************************************************
static void CreateQueuesAndProcessesBoxes()
{
    // Ready Queue for new processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Ready",
                         READY_QUEUE);

    // Waiting Queue for blocked processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Waiting",
                         WAIT_QUEUE);

    // Done Queue for Finished processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Done",
                         DONE_QUEUE);

    // CPU Queue for running process
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "CPU",
                         CPU_QUEUE);
 
    // Create X processes per Queue (we will later on hide them)
    for (int i=0; i<4; i++)
    {
      CreateProcessesInQueue(frame_processborder,
                             grid_processboarder,
                             progressbar_process,
                             i);
    }
}

// *****************************************************************************
// *****************************************************************************
static void CreateEventLogFrameAndControls()
{
    // 1. Create a frame
    frame_eventlog = gtk_frame_new("Event Log");
    gtk_widget_set_size_request(frame_eventlog, 300, 10);

    // 2. Add the frame to the main grid
    gtk_grid_attach(GTK_GRID(grid_main), frame_eventlog, 0,1,1,1);

    // 3. Create scroll window control
    scrolled_eventlog = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_add (GTK_CONTAINER (frame_eventlog), scrolled_eventlog);

    // Enable scrolling
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_eventlog), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 

    // 4. Create TextView canvas
    textview_eventlog = gtk_text_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_eventlog), textview_eventlog);

    // 5. Configure text buffer
    // Obtaining the buffer associated with the widget. 
    buffer_eventlog = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview_eventlog));
    // Set the default buffer text.
    gtk_text_buffer_set_text (buffer_eventlog, "Project 1 - The Scheduler\n", -1);

    // To auto-scroll to bottom, create a permanent mark and iter at the "end"          
    gtk_text_buffer_get_end_iter(buffer_eventlog, &end_iter_eventlog);      
    gtk_text_buffer_create_mark (buffer_eventlog, "end", &end_iter_eventlog, FALSE);

    mark = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER(buffer_eventlog), "end");
    gtk_text_buffer_get_iter_at_mark (buffer_eventlog, &end_iter_eventlog, mark);
    gtk_text_view_scroll_mark_onscreen (GTK_TEXT_VIEW(textview_eventlog), mark);
}

// *****************************************************************************
// *****************************************************************************
static void CreateConfigurationFrameAndControls()
{
    // 1. Create a frame
    frame_configuration = gtk_frame_new("Configuration");
    gtk_widget_set_size_request(frame_configuration, 180, 100);

    // 2. Add the frame to the main grid
    gtk_grid_attach(GTK_GRID(grid_main), frame_configuration, 0,0,1,1);

    // 3. Create a grid (4 rows, 2 col) inside the frame to hold the controls
    grid_configuration = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_configuration), grid_configuration);
    gtk_grid_set_column_spacing(GTK_GRID(grid_configuration), 10);

    // 4. Create the label controls

    // Algorithm Label and value
    label_algorithm = gtk_label_new("Algorithm");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_algorithm, 0,0,1,1);
    label_algorithm_value = gtk_label_new("N/A");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_algorithm_value, 1,0,1,1);

    // Algorithm Label and value
    label_quantum = gtk_label_new("Quantum");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_quantum, 0,1,1,1);
    label_quantum_value = gtk_label_new("N/A");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_quantum_value, 1,1,1,1);

    // Algorithm Label and value
    label_preemtive = gtk_label_new("Mode");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_preemtive, 0,2,1,1);
    label_preemtive_value = gtk_label_new("N/A");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_preemtive_value, 1,2,1,1);

    // Algorithm Label and value
    label_totaltickets = gtk_label_new("Total Tickets");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_totaltickets, 0,3,1,1);
    label_totaltickets_value = gtk_label_new("N/A");
    gtk_grid_attach(GTK_GRID(grid_configuration), label_totaltickets_value, 1,3,1,1);
    
    GtkWidget *button_start;
    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(DoScheduling), NULL);
    gtk_grid_attach(GTK_GRID(grid_configuration), button_start, 0,4,2,1);
}


// *****************************************************************************
// *****************************************************************************
static void CreateMainWindowAndGrid(GtkApplication *app)
{
    // Create a new window
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Proyecto 1 - The Scheduler");
    gtk_window_set_default_size (GTK_WINDOW (window), GuiWindowWidth, GuiWindowHeight);

    // Create main grid (2 rows, 4 column)
    grid_main = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (window), grid_main);

}

// *****************************************************************************
// *****************************************************************************
static void StartGUI (GtkApplication *app,
                      gpointer        user_data)
{  
    // ---------------
    // GUI constructor
    // ---------------
    
    // 1. Create main window and grid
    CreateMainWindowAndGrid(app);
    // 2. Create configuration frame
    CreateConfigurationFrameAndControls();
    // 3. Create log scrolling window
    CreateEventLogFrameAndControls();
    // 4. Create queues and processes boxes
    CreateQueuesAndProcessesBoxes();
    // 5. Finally, show all controls
    gtk_widget_show_all (window);
    // 6. Hide processes in wait, done and cpu queues until they are scheduled 
    HideProcessesInQueue(WAIT_QUEUE);
    HideProcessesInQueue(DONE_QUEUE);
    HideProcessesInQueue(CPU_QUEUE);

    // 7. Debug display initialization complete
    PrintDebugMessageInDisplay("Debug Display GUI controls started.");
}

/*
 * Main function
 */
int main(int argc, char** argv)  
{
    //DebugLotteryUtils();

    GtkApplication *app;
    int status;

    // Constructor
    app = gtk_application_new ("Proyecto1.TheScheduler", G_APPLICATION_FLAGS_NONE);

    // Connect application with "activate" function (activate is not executed at this time)
    g_signal_connect (app, "activate", G_CALLBACK (StartGUI), NULL);

    // Run the GUI (calls the connected StartGUI function)
    status = g_application_run (G_APPLICATION (app), argc, argv);

    // CleanUp
    g_object_unref (app);

    return status;
}

