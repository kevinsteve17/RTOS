/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "TexUtilities.h"
#include "TexFileGenerator.h"
#include <stdbool.h> 

extern int numberOfTasks;
FILE* texFile;
extern int isRmEnabled;                 // Rate Monotonic Enable
extern int isEdfEnabled;                // Earliest Deadline First Enable
extern int isLlfEnabled;                // Least Laxity Enable

void GenerateCoverPage()
{
    
}

void GenerateAlgorithmsResults()
{
    
}

/*
 * Generats .tex file
 */
void GenerateTexFile(SchedResult* schedResults, int numberOfAlgorithms, int isSinglePageEnabled)
{
    char fileName[] = "Proyecto2.tex";
    
    texFile = fopen(fileName, "w");
    
    if (texFile == NULL) 
    {
        printf("Unable to create file\n");
        exit(EXIT_FAILURE);
    }
    
    fputs(header, texFile);
    fputs(newLine, texFile);
    
    fputs(beginDoc, texFile);
    fputs(newLine, texFile);
    
    fputs(titlePage, texFile);
    fputs(newLine, texFile);
    
    //fputs(outline, texFile);
    //fputs(newLine, texFile);
    
    //fputs(algsection, texFile);
    //fputs(newLine, texFile);
    
    fputs(frameSectionPage, texFile);
    fputs(newLine, texFile);
    
    // RM Theory Slide
    if (isRmEnabled == 1)
    {
        fputs(RMTheory, texFile);
        fputs(newLine, texFile);
    }
    
    // EDF Theory Slide
    if (isEdfEnabled == 1)
    {
        fputs(edfTheory, texFile);
        fputs(newLine, texFile);
    }
    
    // LLF Theory Slide
    if (isLlfEnabled == 1)
    {
        fputs(llfTheory, texFile);
        fputs(newLine, texFile);
    }
    
    // ----------Sim table----------
    
    // Single Page per algorithm
    if (isSinglePageEnabled == 1)
    {
        for (int algorithm=0; algorithm<numberOfAlgorithms; algorithm++)
        {
            fputs(tableFrameHeader, texFile);

            //algo task info
            GenerateAlgorithmSimHeadear(&schedResults[algorithm]);

            fputs(tableSectionHeader, texFile);

            fputs(simTableHeader, texFile);
            fputs(GenerateTableContents(&schedResults[algorithm], 0), texFile);
            fputs(tableEnd, texFile);

            if (schedResults->numberOfSimCycles > SIM_COLUMNS)
            {
                fputs(simTableHeader, texFile);
                fputs(GenerateTableContents(&schedResults[algorithm], SIM_COLUMNS), texFile);
                fputs(tableEnd, texFile);
            }

            fputs(tableSectionEnd, texFile);
        }
    }
    // Single Page for all algorithms
    else
    {
        //fputs(tableFrameHeader, texFile);
        fputs(tableSectionHeader, texFile);
        
        for (int algorithm=0; algorithm<numberOfAlgorithms; algorithm++)
        {
            GenerateAlgorithmSimHeadear(&schedResults[algorithm]);
        }
        
        fputs(tableSectionEnd, texFile);

        // sim table
        fputs(tableFrameHeader, texFile);
        fputs(tableSectionHeader, texFile);

        for (int algorithm=0; algorithm<numberOfAlgorithms; algorithm++)
        {
            // slide header (alogorithm name)
            fputs("\\textbf{\n", texFile);
            fputs(schedResults[algorithm].algorithmName, texFile);
            fputs("}\n", texFile);

            fputs(simTableHeader, texFile);
            fputs(GenerateTableContents(&schedResults[algorithm], 0), texFile);
            fputs(tableEnd, texFile);

            if (schedResults->numberOfSimCycles > SIM_COLUMNS)
            {
                fputs(simTableHeader, texFile);
                fputs(GenerateTableContents(&schedResults[algorithm], SIM_COLUMNS), texFile);
                fputs(tableEnd, texFile);
            }

            if (schedResults->numberOfSimCycles > SIM_COLUMNS*2)
            {
                fputs(simTableHeader, texFile);
                fputs(GenerateTableContents(&schedResults[algorithm], SIM_COLUMNS*2), texFile);
                fputs(tableEnd, texFile);
            }            
        }

        fputs(tableSectionEnd, texFile);
    }
    
    // ----------Sim table----------
    
    fputs(endDoc, texFile);
    
    fclose(texFile);
    
    // Compile output tex file
    CompileTex2Pdf();
    
    // Display pdf using default application
    DisplayOutputFile();
}


void GenerateAlgorithmSimHeadear(SchedResult* schedResults)
{
    char aux[12];

    // slide header (alogorithm name)
    fputs("\\textbf{\n", texFile);
    fputs(schedResults->algorithmName, texFile);
    fputs("}\n", texFile);

    // Start the 2 columns section
    fputs("\\begin{multicols}{2}\n", texFile);

    // tasks table
    fputs(tasksTableHeader, texFile);
    fputs(GenerateTaskTable(schedResults), texFile);
    fputs(tableEnd, texFile);
    
    // CPU utilization
    if (schedResults->CPU_Utilization > 0)
    {
        
        fputs("\\[ \\mu = \\sum\\limits_{i=1}^n \\frac{C_i}{P_i} =", texFile);
        sprintf(aux, "%f", schedResults->CPU_Utilization);
        fputs(aux, texFile);
        fputs(" ", texFile);

        if (schedResults->CPU_Utilization > 1)
        {
            fputs(">", texFile);
        }
        else if (schedResults->CPU_Utilization < 1)
        {
            fputs("<", texFile);
        }
        else if (schedResults->CPU_Utilization == 1)
        {
            fputs("=", texFile);
        }

        fputs(" ", texFile);    
        
        fputs("1", texFile);

        fputs("\\]\n", texFile);
        
        }  
        
        // Close the 2 columns section
        fputs("\\end{multicols}\n", texFile);
}

/*
 * Generates tasks table 
 */
char * GenerateTaskTable(SchedResult* schedResults)
{
    char row[5048];
    char aux[12];
    char *tiny = "\\tiny ";
    char *square = "&";
    char *ret = "";
    char *space = " ";
    char *endRow = " \\\\ \\hline\n";
    char *color;

    strcpy(row, tiny);
    strcat(row, "Tarea");
    strcat(row, space);
    strcat(row, square);
    strcat(row, space);
    strcat(row, tiny);
    strcat(row, "Color");
    strcat(row, space);
    strcat(row, square);
    strcat(row, space);
    strcat(row, tiny);
    strcat(row, "$c_i$");
    strcat(row, space);
    strcat(row, square);
    strcat(row, space);
    strcat(row, tiny);
    strcat(row, "$p_i$");
    strcat(row, endRow);

    for (int i = 0; i < numberOfTasks; i++)
    {
        strcat(row, tiny);
        strcat(row, "T");
        sprintf(aux, "%d", i+1);
        strcat(row, aux);
        strcat(row, space);
        strcat(row, square);
        strcat(row, space);
        color = GetTaskColor(i);
        strcat(row, color);
        strcat(row, square);
        strcat(row, tiny);
        strcat(row, space);
        sprintf(aux, "%d", (int)schedResults->TaskInfo[i].ComputationTime);
        strcat(row, aux);
        strcat(row, space);
        strcat(row, square);
        strcat(row, tiny);
        strcat(row, space); 
        sprintf(aux, "%d", (int)schedResults->TaskInfo[i].Period);
        strcat(row, aux);       
        strcat(row, endRow);
    }

    ret = row;
    return ret;     
}

/*
 * Generates sim table contents based on sim results
 */
char * GenerateTableContents(SchedResult* schedResults, int offset)
{
    bool deadlineMissed = false;
    char row[5048];
    char aux[12];
    char *huge = "\\fontsize{4}{4}\\selectfont  ";
    char *tiny = "\\tiny ";
    char *supertiny = "\\fontsize{3.5}{4}\\selectfont ";
    char *square = "&";
    char *ret = "";
    char *space = " ";
    char *endRow = "\\\\ \\hline\n";
    char *color;    

    strcpy(row, square);
    strcat(row, space);

    for (int i = 0; i < SIM_COLUMNS; i++)
    {
        if (i>0)
        {
            strcat(row, space);
        }

        strcat(row, supertiny);
        sprintf(aux, "%d", i+1+offset);
        strcat(row, aux);
        strcat(row, square);
    }

    strcat(row, endRow); 

    strcat(row, tiny);
    strcat(row, "T");

    for (int i = 0; i < numberOfTasks; i++)
    {
        deadlineMissed = false;

        if (i>0)
        {
            strcat(row, tiny);
            strcat(row, "T");
        }
                
        sprintf(aux, "%d", i+1);
        strcat(row, aux);
        strcat(row, square);
        strcat(row, space);
        
        for (int t = 0; t < SIM_COLUMNS; t++)
        {
            if (t>0)
            {
                strcat(row, space);
                strcat(row, space);
            }

            if (!deadlineMissed && (t+offset < schedResults->numberOfSimCycles))
            {
                if (schedResults->SimulationResults[t+offset] == i)
                {
                    color = GetTaskColor(i);
                    strcat(row, color);
                }

                if (schedResults->SimulationResults[t+offset] == -1)
                {
                    color = GetTaskColor(-1);
                    strcat(row, color);
                }

                if ((schedResults->SimulationResults[t+offset] >= 666) && (schedResults->SimulationResults[t+offset]-666==i))
                {
                    deadlineMissed = true;
                    color = GetTaskColor(666);
                    //strcat(row, color);
                    strcat(row, huge);
                    strcat(row, "\\color{red} ");
                    strcat(row, "\\ding{54}");
                }
            }            
            
            strcat(row, square);
        }

        strcat(row, endRow);        
    }

    ret = row;
    return ret;    
}

/*
 * Returns task color based on ID
 */
char * GetTaskColor(int i)
{
    // 
    char *tag = "\\cellcolor{";
    char *endTag = "}";
    char color[20];
    char *aux = "blue";
    char *ret = "";

    if (i==1)
    {
        aux = "green";
    }
    else if (i==2)
    {
        aux = "orange";
    }
    else if (i==3)
    {
        aux = "yellow";
    }               
    else if (i==4)
    {
        aux = "brown";
    }
    else if (i==5)
    {
        aux = "purple";
    }  
    else if (i==-1)
    {
        aux = "white";
    }
        else if (i==666)
    {
        aux = "red";
    }

    strcpy(color, tag);
    strcat(color, aux);
    strcat(color, endTag);

    ret = color;
    return ret;      
}



void CompileTex2Pdf()
{
    system("pdflatex -interaction=nonstopmode Proyecto2.tex");
}


void DisplayOutputFile()
{
    system("xdg-open Proyecto2.pdf");
}
    