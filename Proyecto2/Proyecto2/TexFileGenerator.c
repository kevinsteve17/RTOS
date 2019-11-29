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
    
    FILE* texFile;
    
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
    
    fputs(outline, texFile);
    fputs(newLine, texFile);
    
    fputs(algsection, texFile);
    fputs(newLine, texFile);
    
    fputs(frameSectionPage, texFile);
    fputs(newLine, texFile);
    
    // ----------Sim table----------
    
    // Single Page per algorithm
    if (isSinglePageEnabled == 1)
    {
        for (int algorithm=0; algorithm<numberOfAlgorithms; algorithm++)
        {
            fputs(tableSectionHeader, texFile);

            fputs(tableHeader, texFile);
            fputs(GenerateTableContents(schedResults, 0), texFile);
            fputs(tableEnd, texFile);

            if (schedResults->numberOfSimCycles > SIM_COLUMNS)
            {
                fputs(tableHeader, texFile);
                fputs(GenerateTableContents(schedResults, SIM_COLUMNS), texFile);
                fputs(tableEnd, texFile);
            }

            fputs(tableSectionEnd, texFile);
        }
    }
    // Single Page for all algorithms
    else
    {
        fputs(tableSectionHeader, texFile);

        for (int algorithm=0; algorithm<numberOfAlgorithms; algorithm++)
        {
            fputs(tableHeader, texFile);
            fputs(GenerateTableContents(schedResults, 0), texFile);
            fputs(tableEnd, texFile);

            if (schedResults->numberOfSimCycles > SIM_COLUMNS)
            {
                fputs(tableHeader, texFile);
                fputs(GenerateTableContents(schedResults, SIM_COLUMNS), texFile);
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

/*
 * Generates sim table contents based on sim results
 */
char * GenerateTableContents(SchedResult* schedResults, int offset)
{
    bool deadlineMissed = false;
    char row[5048];
    char aux[12];
    char *huge = "\\Large ";
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
                    strcat(row, color);
                    strcat(row, huge);
                    strcat(row, "DANGER");
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
    