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
#include <ctype.h>
#include "progress_gui.h"
#include "Task.h"
#include "FCFSScheduler.h"
#include "Utilities.h"
#include "Timer.h"
#include "Lottery_Scheduler.h"

#define DEBUG

// Global Variables
int GuiWindowWidth = 100;
int GuiWindowHeight = 100;
int TotalProcessesNumber = 5;
int CurrentRunningProcess = 0;
int MaxTickets = 0;

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


/*typedef struct SSettings Settings;

// Settings struct 
struct SSettings
{
    int SchedulingAlgorithm;
    int PMode;
    int ProcessCount;
    char* ArrivalTime;
    char* WorkLoad;
    int Tickets;
    int Quantum;
    char* Priority;
};*/


Settings* SchedSettings; 

/*
 * Starts Lottery Scheduling
 */
void StartLotteryScheduling(Settings* settings)
{
    printf("--> Process to Execute: %i \n",settings->ProcessCount);
    int priorities[settings->ProcessCount];
    MaxTickets = settings->Tickets;

    char* temp = settings->Priority;
    char* token = strtok(temp, ",");
    int j= 0;

    while(token != NULL)
    {
        priorities[j] = atoi(token);
        token = strtok(NULL, ",");
        j++;
    }

    int workload[settings->ProcessCount];
    char* tempWrkload = settings->WorkLoad;
    char* tokenWL = strtok(tempWrkload, ",");
    
    int k=0;
    while(tokenWL != NULL)
    {
        workload[k] = atoi(tokenWL);
        tokenWL = strtok(NULL, ",");
        k++;
    }

    // init lottery scheduler
    InitLotteryScheduler();

    // Process creation
    for(int i=0;i<settings->ProcessCount;i++)
    {
        processStruct* process = malloc(sizeof(processStruct));
        process->ID = i;
        process->Priority = priorities[i];
        process->BurstTime = workload[i];
        AddProcessClient(process);
    }

    // init lottery tickets pool
    InitLotteryTicketsPool(ticketAssignations, settings->Tickets);

#ifdef DEBUG
    PrintLotteryPool(ticketAssignations, settings->Tickets);
#endif

    // assign tickets to process
    AssignLotteryTickets(settings->Tickets);

#ifdef DEBUG
    PrintLotteryPool(ticketAssignations, settings->Tickets);
#endif

    // init Lottery
    InitTicketRaffle(tickets, settings->Tickets);

#ifdef DEBUG
    PrintLotteryPool(tickets, settings->Tickets);
#endif

    //start scheduler
    Schedule_NonPreemptive();    
}

void CreateFCFSProcesses(Settings* ssettings)
{
    //printf("Creating processes");
    //PrintDebugMessageInDisplay("Creating processes");
    int arrivalTimes[ssettings->ProcessCount];
    char* tempArrivT = ssettings->ArrivalTime;
    char* tokenAT = strtok(tempArrivT, ",");
    int j= 0;
    while(tokenAT != NULL)
    {
        arrivalTimes[j] = atoi(tokenAT);
        tokenAT = strtok(NULL, ",");
        j++;
    }
    
    int workload[ssettings->ProcessCount];
    char* tempWrkload = ssettings->WorkLoad;
    char* tokenWL = strtok(tempWrkload, ",");
    
    int k=0;
    while(tokenWL != NULL)
    {
        workload[k] = atoi(tokenWL);
        tokenWL = strtok(NULL, ",");
        k++;
    }
    
#ifdef DEBUG
    int i;
    for (i = 0; i < 25; i++) {
        printf("Process: %d Arrival Time: %d\n",i,arrivalTimes[i]);
    }
    
    for (i = 0; i < 25; i++) {
        printf("Process: %d, WorkLoad: %d\n",i, workload[i]);
    }
#endif
    
    RunFCFSScheduling(arrivalTimes, workload, ssettings->ProcessCount);
}

void ReadFile(Settings* ssettings)
{
    const int Algortihm = 0;
    const int Mode = 1;
    const int Priority = 2;
    const int ArrivalTime = 3;
    const int Tickets = 6;
    const int Workload = 5;
    const int Quantum = 7;
    const int ProcessesCount = 4;
    
    char lastHeader=malloc(sizeof(char));
    char line[512], fileName[256];
    const char equal[3] = "\n";
    FILE* settings;

    settings = fopen("SchedulerSettings", "r");

    if (settings ==  NULL)
    {
        perror("Error while opening the file. \n");
        exit(EXIT_FAILURE);
    }

    int lineCount = 0;

    while((fgets(line, 512, settings))!= NULL)
    {
        if (line[0] != '#' && isspace(line[0]) == 0) 
        {
            char lineInfo[(int)strlen(line)];
            
            if (lineCount == Algortihm) 
            {
                strcpy(lineInfo, line);
                int lineInfoInt = atoi(lineInfo);
                ssettings->SchedulingAlgorithm = malloc(sizeof(int));
                ssettings->SchedulingAlgorithm = lineInfoInt;
            }
            else if (lineCount == Mode)
            {
                //char mode[(int)strlen(line)];
                strcpy(lineInfo, line);
                int lineInfoInt = atoi(lineInfo);
                ssettings->PMode = malloc(sizeof(int));
                ssettings->PMode = lineInfoInt;
            }
            else if (lineCount == Priority)
            {
                strcpy(lineInfo, line);
                ssettings->Priority = malloc((strlen(lineInfo)+1)*sizeof(char*));
                memcpy(ssettings->Priority, lineInfo, strlen(lineInfo)+1);
            }
            else if (lineCount == ArrivalTime)
            {
                strcpy(lineInfo, line);
                ssettings->ArrivalTime = malloc((strlen(lineInfo)+1)*sizeof(char*));
                memcpy(ssettings->ArrivalTime, lineInfo, strlen(lineInfo)+1);
            }
            else if (lineCount == ProcessesCount)
            {
                strcpy(lineInfo, line);
                int lineInfoInt = atoi(lineInfo);
                ssettings->ProcessCount = malloc(sizeof(int));
                ssettings->ProcessCount = lineInfoInt;
            }
            else if (lineCount == Workload)
            {
                strcpy(lineInfo, line);
                ssettings->WorkLoad = malloc((strlen(lineInfo)+1)*sizeof(char*));
                memcpy(ssettings->WorkLoad, lineInfo, strlen(lineInfo)+1);
            }
            else if (lineCount == Tickets)
            {
                strcpy(lineInfo, line);
                int lineInfoInt = atoi(lineInfo);
                ssettings->Tickets = malloc(sizeof(int));
                ssettings->Tickets = lineInfoInt;
            }
            else if (lineCount == Quantum)
            {
                strcpy(lineInfo, line);
                int lineInfoInt = atoi(lineInfo);
                ssettings->Quantum = malloc(sizeof(int));
                ssettings->Quantum = lineInfoInt;
            }
            lineCount++;
        }
    }
    fclose(settings);
}

// *****************************************************************************
// *****************************************************************************
static void DoScheduling(GtkWidget *button_start, gpointer data) 
{
  
    // Read configuration file
    PrintDebugMessageInDisplay ("Reading config file ...");
    ModifyDisplayedConfigurationValues(SchedSettings->SchedulingAlgorithm, 
                                       SchedSettings->Quantum, 
                                       SchedSettings->PMode, 
                                       SchedSettings->Tickets);

    // Configure Soft timer handler
    PrintDebugMessageInDisplay ("Configuring quantum soft timer handler...");
    SetQuantumSoftTimerHandler();
    
    if (SchedSettings->SchedulingAlgorithm == 1) 
    {
        // FCFS
        CreateFCFSProcesses(SchedSettings);
    }
    else
    {
        // Lottery
    }

    

    
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
void ModifyDisplayedConfigurationValues(int algorithm,
                                       int quantum,
                                       int preemptive,
                                       int totaltickets)
{
    char str[10];
    
    // Update Algorithm and tickets count if applicable
    if (algorithm == 0)
    {
        gtk_label_set_text(GTK_LABEL(label_algorithm_value), "Lottery");
        
        sprintf(str, "%d", totaltickets);
        gtk_label_set_text(GTK_LABEL(label_totaltickets_value), str); 
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(label_algorithm_value), "FCFS");
    }
    
    // Update preemptive mode
    if (preemptive == 0)
    {
        gtk_label_set_text(GTK_LABEL(label_preemtive_value), "Non-Preemptive");  
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(label_preemtive_value), "Preemptive"); 
    }
    
    // Update Quantum
    sprintf(str, "%d", quantum);
    gtk_label_set_text(GTK_LABEL(label_quantum_value), str);  

    // Debug message
    PrintDebugMessageInDisplay("Updating config panel ...");
}

// *****************************************************************************
// *****************************************************************************
void MoveAndUpdateProcessBetweenQueues(int fromQueueNumber,
                                       int toQueueNumber,
                                       int processNumber,
                                       double piValue,
                                       double progressPercentValue)
{
    // Hide Process
    gtk_widget_hide(frame_processborder[fromQueueNumber][processNumber-1]);
    
    // Update label and progress bar values
    char str[64];
    sprintf(str, "%f", piValue);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar_process[toQueueNumber][processNumber-1]), str);
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
                                double piValue,
                                double progressPercentValue)
{
    char str[5];
    sprintf(str, "%.3f", piValue);
    // Update label and progress bar
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar_process[queueNumber][processNumber-1]), str);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar_process[queueNumber][processNumber-1]), progressPercentValue/100);
    
    // Force controls update
    while(gtk_events_pending())
    {
      gtk_main_iteration();
    }
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
    char message[27];
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
        font_desc = pango_font_description_from_string ("Sans 6");
        gtk_widget_override_font(frame_processborder[queueNumber][i], font_desc);
        gtk_widget_override_font(progressbar_process[queueNumber][i], font_desc);
        
        // (WARNINGS!) Modify the color for the widgets 
        gdk_color_parse ("light blue", &color);
        gtk_widget_modify_bg (GTK_WIDGET(grid_processboarder[queueNumber][i]), GTK_STATE_NORMAL, &color);
    }
}

// *****************************************************************************
// *****************************************************************************
static void CreateQueuesAndProcessesBoxes()
{
    // Ready Queue for new processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Ready (0)",
                         READY_QUEUE);

    // Waiting Queue for blocked processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Waiting (1)",
                         WAIT_QUEUE);

    // Done Queue for Finished processes
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "Done (2)",
                         DONE_QUEUE);

    // CPU Queue for running process
    CreateProcessesQueue(frame_queue,
                         grid_queue,
                         "CPU (3)",
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
    // Read settings file
    SchedSettings = malloc(sizeof(Settings));
    ReadFile(SchedSettings);
    TotalProcessesNumber = SchedSettings->ProcessCount;
    
 /* GtkApplication *app;
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
 */
    
    
#ifdef DEBUG
    // Debug print - show read configuration
    printf("Algorithm: %d\n",SchedSettings->SchedulingAlgorithm);
    printf("Preemtive: %d\n",SchedSettings->PMode);
    printf("Priority: %s",SchedSettings->Priority);
    printf("ProcessCount: %d\n",SchedSettings->ProcessCount);
    printf("Quantum: %d\n",SchedSettings->Quantum);
    printf("Tickets: %d\n",SchedSettings->Tickets);
    printf("Workload: %s",SchedSettings->WorkLoad);
    printf("ArrivalTime: %s",SchedSettings->ArrivalTime);
#endif

    if (SchedSettings->PMode == 0)
    {
        StartLotteryScheduling(SchedSettings);
    }
    else if (SchedSettings->PMode == 1)
    {
        CreateFCFSProcesses(SchedSettings);
    }

    return 0;
}

