#include "GraphicalUserInterface.h"
#include "Task.h"

// Main window and grid
int GuiWindowWidth = 1;
int GuiWindowHeight = 1;
GtkWidget *window;
GtkWidget *grid_main;

// Task Spreadsheet
GtkWidget *entry_computation[6];
GtkWidget *entry_period[6];

// Tasks struct
int leastCommonMultiple = 1;
int maxNumberOfTasks = 6;
int numberOfTasks;
Task tasks[6];

// Control variables (0=Off, 1=On)
int isRmEnabled = 0;
int isEdfEnabled = 0;
int isLlfEnabled = 0;
int isSinglePageOutputEnabled = 0;


// *****************************
// DISPLAY CONSTRUCTOR FUNCTIONS    
// *****************************

// *****************************************************************************
// Function:    StartGUI
// Description: GUI constructor main function
//
void StartGUI (GtkApplication *app,
               gpointer        user_data)
{  
    printf("Function call: StartGUI()\n");
    
    // ---------------
    // GUI constructor
    // ---------------
    
    // Create main window and grid
    CreateMainWindowAndGrid(app);
    // Create algorithms frame and controls
    CreateAlgorithmsFrameAndControls();
    // Create output frame and controls
    CreateResultsFrameAndControls();
    // Create add/delete/start buttons
    CreateButtonControls();
    // Create spreadsheet grid
    CreateTaskSpreadsheet();
    
    // Finally, show all controls
    gtk_widget_show_all (window);
}


// *****************************************************************************
// Function:    CreateMainWindowAndGrid
// Description: Creates main window and main grid
//
void CreateMainWindowAndGrid(GtkApplication *app)
{
    printf("Function call: CreateMainWindowAndGrid()\n");
    
    // Create a new window
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Proyecto 2 - El Calendarizador Real-Time");
    gtk_window_set_default_size (GTK_WINDOW (window), GuiWindowWidth, GuiWindowHeight);

    // Create main grid
    grid_main = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (window), grid_main);
}


// *****************************************************************************
// Function:    CreateAlgorithmsFrameAndControls
// Description: Creates the algorithm selection section
//
void CreateAlgorithmsFrameAndControls()
{
    printf("Function call: CreateAlgorithmsFrameAndControls()\n");
    
    // 1. Create a frame
    GtkWidget *frame_algoritmos;
    frame_algoritmos = gtk_frame_new("Algoritmos");
    gtk_widget_set_size_request(frame_algoritmos, 1, 1);

    // 2. Add the frame to the main grid (left, top, width, height)
    gtk_grid_attach(GTK_GRID(grid_main), frame_algoritmos, 0,0,1,1);

    // 3. Create a grid inside the frame to hold the controls
    GtkWidget *grid_algoritmos;
    grid_algoritmos = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_algoritmos), grid_algoritmos);
    gtk_grid_set_column_spacing(GTK_GRID(grid_algoritmos), 1);

    // 4. Create check buttons

    // Rate monotonic button
    GtkWidget *checkButton_RM;
    checkButton_RM = gtk_check_button_new_with_label("RM");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_RM), "toggled", G_CALLBACK(Toggle_RM), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_RM, 0,0,1,1);
    
    // Earliest Deadline First button
    GtkWidget *checkButton_EDF;
    checkButton_EDF = gtk_check_button_new_with_label("EDF");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_EDF), "toggled", G_CALLBACK(Toggle_EDF), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_EDF, 0,1,1,1);
    
    // Least Laxity First button
    GtkWidget *checkButton_LLF;
    checkButton_LLF = gtk_check_button_new_with_label("LLF");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_LLF), "toggled", G_CALLBACK(Toggle_LLF), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_LLF, 0,2,1,1);  
}


// *****************************************************************************
// Function:    CreateAlgorithmsFrameAndControls
// Description: Creates the latex output configuration controls
//
void CreateResultsFrameAndControls()
{
    printf("Function call: CreateResultsFrameAndControls()\n");
    
    // 1. Create a frame
    GtkWidget *frame_salida;
    frame_salida = gtk_frame_new("Salida");
    gtk_widget_set_size_request(frame_salida, 1, 1);

    // 2. Add the frame to the main grid (left, top, width, height)
    gtk_grid_attach(GTK_GRID(grid_main), frame_salida, 0,1,1,1);

    // 3. Create a grid inside the frame to hold the controls
    GtkWidget *grid_salida;
    grid_salida = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_salida), grid_salida);
    gtk_grid_set_column_spacing(GTK_GRID(grid_salida), 1);

    // 4. Create check buttons

    // Single slide button
    GtkWidget *checkButton_individualSlide;
    checkButton_individualSlide = gtk_check_button_new_with_label("Filmina Individual");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_individualSlide), "toggled", G_CALLBACK(Toggle_Output), NULL);
    gtk_grid_attach(GTK_GRID(grid_salida), checkButton_individualSlide, 0,0,1,1);
}


// *****************************************************************************
// Function:    CreateButtonControls
// Description: Creates the button controls
//
void CreateButtonControls()
{
    printf("Function call: CreateButtonControls()\n");
    
    //GtkWidget *button_addTask;
    //button_addTask = gtk_button_new_with_label("Agregar Tarea");
    //g_signal_connect(button_addTask, "clicked", G_CALLBACK(DoScheduling), NULL);
    //gtk_grid_attach(GTK_GRID(grid_main), button_addTask, 0,2,1,1);
    
    //GtkWidget *button_deleteTask;
    //button_deleteTask = gtk_button_new_with_label("Borrar Tarea");
    //g_signal_connect(button_deleteTask, "clicked", G_CALLBACK(DoScheduling), NULL);
    //gtk_grid_attach(GTK_GRID(grid_main), button_deleteTask, 0,3,1,1);
    
    GtkWidget *button_start;
    button_start = gtk_button_new_with_label("Calendarizar");
    g_signal_connect(button_start, "clicked", G_CALLBACK(DoScheduling), NULL);
    gtk_grid_attach(GTK_GRID(grid_main), button_start, 0,2,1,1);
}


// *****************************************************************************
// Function:    CreateTaskSpreadsheet
// Description: Creates spreadsheet grid section
//
void CreateTaskSpreadsheet()
{
    printf("Function call: CreateTaskSpreadsheet()\n");
    
    // 1. Create a frame
    GtkWidget *frame_tasks;
    frame_tasks = gtk_frame_new("Tareas");
    gtk_widget_set_size_request(frame_tasks, 1, 1);

    // 2. Add the frame to the main grid (left, top, width, height)
    gtk_grid_attach(GTK_GRID(grid_main), frame_tasks, 1,0,1,3);

    // 3. Create a grid inside the frame to hold the controls
    GtkWidget *grid_tasks;
    grid_tasks = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_tasks), grid_tasks);
    gtk_grid_set_column_spacing(GTK_GRID(grid_tasks), 1);
    
    
    // Columns Title
    GtkWidget *label_taskId;
    label_taskId = gtk_label_new("ID");
    gtk_grid_attach(GTK_GRID(grid_tasks), label_taskId, 0,0,1,1);
    
    GtkWidget *label_taskComputation;
    label_taskComputation = gtk_label_new("Ejecucion");
    gtk_grid_attach(GTK_GRID(grid_tasks), label_taskComputation, 1,0,1,1);
    
    GtkWidget *label_taskPeriod;
    label_taskPeriod = gtk_label_new("Periodo");
    gtk_grid_attach(GTK_GRID(grid_tasks), label_taskPeriod, 2,0,1,1);

    // Create entries
    
    // ID
    GtkWidget *label_id[maxNumberOfTasks];
    for(int i=0; i < maxNumberOfTasks; i++)
    {
        char str[2];
        sprintf(str, "%d", i);
        
        label_id[i] = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(grid_tasks), label_id[i], 0,i+1,1,1);
    }
    
    // Computation   
    for(int i=0; i < maxNumberOfTasks; i++)
    {
        entry_computation[i] = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry_computation[i]), "0");
        gtk_entry_set_max_length(GTK_ENTRY(entry_computation[i]), 2);
        gtk_entry_set_max_width_chars(GTK_ENTRY(entry_computation[i]), 2);
        gtk_grid_attach(GTK_GRID(grid_tasks), entry_computation[i], 1,i+1,1,1);
    }
    
    // Period    
    for(int i=0; i < maxNumberOfTasks; i++)
    {
        entry_period[i] = gtk_entry_new();
        gtk_entry_set_text(GTK_ENTRY(entry_period[i]), "0");
        gtk_entry_set_max_length(GTK_ENTRY(entry_period[i]), 2);
        gtk_entry_set_max_width_chars(GTK_ENTRY(entry_period[i]), 2);
        gtk_grid_attach(GTK_GRID(grid_tasks), entry_period[i], 2,i+1,1,1);
    } 
}

// **************
// EVENT HANDLERS
// **************

// *****************************************************************************
// Function:    toggle_RM
// Description: Check button event handler
//
void Toggle_RM(GtkWidget *gtk_control, gpointer data) 
{
    printf("Function call: Toggle_RM()\n");
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        // ON
        isRmEnabled = 1;
    }
    else
    {
        // OFF
        isRmEnabled = 0;
    } 
}

// *****************************************************************************
// Function:    toggle_EDF
// Description: Check button event handler
//
void Toggle_EDF(GtkWidget *gtk_control, gpointer data) 
{
    printf("Function call: Toggle_EDF()\n");
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        // ON
        isEdfEnabled = 1;
    }
    else
    {
        // OFF
        isEdfEnabled = 0;
    } 
}

// *****************************************************************************
// Function:    toggle_LLF
// Description: Check button event handler
//
void Toggle_LLF(GtkWidget *gtk_control, gpointer data) 
{
    printf("Function call: Toggle_LLF()\n");
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        // ON
        isLlfEnabled = 1;
    }
    else
    {
        // OFF
        isLlfEnabled = 0;
    } 
}

// *****************************************************************************
// Function:    toggle_Output
// Description: Check button event handler
//
void Toggle_Output(GtkWidget *gtk_control, gpointer data) 
{
    printf("Function call: Toggle_Output()\n");
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        // ON
        isSinglePageOutputEnabled = 1;
    }
    else
    {
        // OFF
        isSinglePageOutputEnabled = 0;
    } 
}

// *****************
// UTILITY FUNCTIONS
// *****************

// *****************************************************************************
// Function:    ReadSpreadsheet
// Description: Utility function, reads the spreadsheet grid in the GUI and 
//              populates the task struct array
//
void ReadSpreadsheet()
{
    printf("Function call: ReadSpreadsheet()\n");
    
    // Read task spreadsheet 
    const gchar *text;
    int computation;
    int period;
    numberOfTasks = 0;
    
    // For each row
    for(int i=0; i < maxNumberOfTasks; i++)
    {
        // Read computation time
        text = gtk_entry_get_text (GTK_ENTRY (entry_computation[i]));
        sscanf(text, "%d", &computation); 
        // Read period
        text = gtk_entry_get_text (GTK_ENTRY (entry_period[i]));
        sscanf(text, "%d", &period); 
        
        // Populate task struct array
        tasks[i].Id = i;
        tasks[i].ComputationTime = computation;
        tasks[i].Period = period;
        tasks[i].Deadline = period;
        
        // For each task with period > 0 increment the task counter
        if (period > 0)
        {
            numberOfTasks++;
        }
    }
}



// *****************************************************************************
// Function:    CalculateLeastCommonMultiple
// Description: Calculates the Least Common Multiple of the available tasks.
//              This sets the limit of the simulation time.
//
void CalculateLeastCommonMultiple()
{  
    printf("Function call: CalculateLeastCommonMultiple()\n");
    
    int num[maxNumberOfTasks];
    
    for (int i = 0; i < maxNumberOfTasks; i++)
    {
        if (tasks[i].Period > 0)
        {
            num[i] = tasks[i].Period;
        }
        else
        {
            num[i] = 1;
        }    
    }

    // Always True
    while(1) 
    {
    	if (leastCommonMultiple % num[0] == 0 && 
            leastCommonMultiple % num[1] == 0 &&
            leastCommonMultiple % num[2] == 0 &&
            leastCommonMultiple % num[3] == 0 &&
            leastCommonMultiple % num[4] == 0 &&
            leastCommonMultiple % num[5] == 0)
        {
            printf ("LeastCommonMultiple = %d\n", leastCommonMultiple);
            return;
        }
        
        leastCommonMultiple++;
    }   
}