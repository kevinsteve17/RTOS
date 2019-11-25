#include "GraphicalUserInterface.h"

// Global Variables
int GuiWindowWidth = 500;
int GuiWindowHeight = 500;

// Main window and grid
GtkWidget *window;
GtkWidget *grid_main;


// *****************************************************************************
// *****************************************************************************
void StartGUI (GtkApplication *app,
               gpointer        user_data)
{  
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
    
    
    // Finally, show all controls
    gtk_widget_show_all (window);
}


// *****************************************************************************
// *****************************************************************************
void CreateMainWindowAndGrid(GtkApplication *app)
{
    // Create a new window
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Proyecto 2 - El Calendarizador Real-Time");
    gtk_window_set_default_size (GTK_WINDOW (window), GuiWindowWidth, GuiWindowHeight);

    // Create main grid
    grid_main = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (window), grid_main);
}


// *****************************************************************************
// *****************************************************************************
void CreateAlgorithmsFrameAndControls()
{
    // 1. Create a frame
    GtkWidget *frame_algoritmos;
    frame_algoritmos = gtk_frame_new("Algoritmos");
    gtk_widget_set_size_request(frame_algoritmos, 10, 10);

    // 2. Add the frame to the main grid (left, top, width, height)
    gtk_grid_attach(GTK_GRID(grid_main), frame_algoritmos, 0,0,1,1);

    // 3. Create a grid inside the frame to hold the controls
    GtkWidget *grid_algoritmos;
    grid_algoritmos = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_algoritmos), grid_algoritmos);
    gtk_grid_set_column_spacing(GTK_GRID(grid_algoritmos), 10);

    // 4. Create check buttons

    // Rate monotonic button
    GtkWidget *checkButton_RM;
    checkButton_RM = gtk_check_button_new_with_label("RM");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_RM), "toggled", G_CALLBACK(toggle_RM), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_RM, 0,0,1,1);
    
    // Earliest Deadline First button
    GtkWidget *checkButton_EDF;
    checkButton_EDF = gtk_check_button_new_with_label("EDF");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_EDF), "toggled", G_CALLBACK(toggle_EDF), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_EDF, 0,1,1,1);
    
    // Least Laxity First button
    GtkWidget *checkButton_LLF;
    checkButton_LLF = gtk_check_button_new_with_label("LLF");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_LLF), "toggled", G_CALLBACK(toggle_LLF), NULL);
    gtk_grid_attach(GTK_GRID(grid_algoritmos), checkButton_LLF, 0,2,1,1);  
}


// *****************************************************************************
// *****************************************************************************
void CreateResultsFrameAndControls()
{
    // 1. Create a frame
    GtkWidget *frame_salida;
    frame_salida = gtk_frame_new("Salida");
    gtk_widget_set_size_request(frame_salida, 10, 10);

    // 2. Add the frame to the main grid (left, top, width, height)
    gtk_grid_attach(GTK_GRID(grid_main), frame_salida, 0,1,1,1);

    // 3. Create a grid inside the frame to hold the controls
    GtkWidget *grid_salida;
    grid_salida = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (frame_salida), grid_salida);
    gtk_grid_set_column_spacing(GTK_GRID(grid_salida), 10);

    // 4. Create check buttons

    // Single slide button
    GtkWidget *checkButton_individualSlide;
    checkButton_individualSlide = gtk_check_button_new_with_label("Filmina Individual");
    g_signal_connect(GTK_TOGGLE_BUTTON(checkButton_individualSlide), "toggled", G_CALLBACK(toggle_Output), NULL);
    gtk_grid_attach(GTK_GRID(grid_salida), checkButton_individualSlide, 0,0,1,1);
}


// *****************************************************************************
// *****************************************************************************
void CreateButtonControls()
{
    GtkWidget *button_addTask;
    button_addTask = gtk_button_new_with_label("Agregar Tarea");
    g_signal_connect(button_addTask, "clicked", G_CALLBACK(DoScheduling), NULL);
    gtk_grid_attach(GTK_GRID(grid_main), button_addTask, 0,2,1,1);
    
    GtkWidget *button_deleteTask;
    button_deleteTask = gtk_button_new_with_label("Borrar Tarea");
    g_signal_connect(button_deleteTask, "clicked", G_CALLBACK(DoScheduling), NULL);
    gtk_grid_attach(GTK_GRID(grid_main), button_deleteTask, 0,3,1,1);
    
    GtkWidget *button_start;
    button_start = gtk_button_new_with_label("Calendarizar");
    g_signal_connect(button_start, "clicked", G_CALLBACK(DoScheduling), NULL);
    gtk_grid_attach(GTK_GRID(grid_main), button_start, 0,4,1,1);
}


// *****************************************************************************
// *****************************************************************************
void DoScheduling(GtkWidget *button_start, gpointer data) 
{
    printf("ejecutar clicked.\n");
}


// *****************************************************************************
// *****************************************************************************
void toggle_RM(GtkWidget *gtk_control, gpointer data) 
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        printf("RM = ON.\n");
    }
    else
    {
        printf("RM = OFF.\n");
    } 
}

// *****************************************************************************
// *****************************************************************************
void toggle_EDF(GtkWidget *gtk_control, gpointer data) 
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        printf("EDF = ON.\n");
    }
    else
    {
        printf("EDF = OFF.\n");
    } 
}

// *****************************************************************************
// *****************************************************************************
void toggle_LLF(GtkWidget *gtk_control, gpointer data) 
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        printf("LLF = ON.\n");
    }
    else
    {
        printf("LLF = OFF.\n");
    } 
}

// *****************************************************************************
// *****************************************************************************
void toggle_Output(GtkWidget *gtk_control, gpointer data) 
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gtk_control)))
    {
        printf("Single Slide = ON.\n");
    }
    else
    {
        printf("Single Slide = OFF.\n");
    } 
}