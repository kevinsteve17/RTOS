/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "TexUtilities.h"
#include "TexFileGenerator.h"

extern int numberOfTasks;

void GenerateCoverPage()
{
    
}

void GenerateAlgorithmsResults()
{
    
}

void GenerateTexFile(SchedResult* schedResults)
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
    
    // table
    fputs(tableSectionHeader, texFile);
    fputs(tableHeader, texFile);
    fputs(GenerateTableContents(schedResults), texFile);
    fputs(tableEnd, texFile);
    fputs(tableSectionEnd, texFile);
    // table
    
    fputs(endDoc, texFile);
    
    fclose(texFile);
           
}

char * GenerateTableContents(SchedResult* schedResults)
{
    char row[5048];
    char aux[12];
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
        sprintf(aux, "%d", i+1);
        strcat(row, aux);
        strcat(row, square);
    }

    strcat(row, endRow); 

    strcat(row, tiny);
    strcat(row, "T");

    for (int i = 0; i < numberOfTasks; i++)
    {
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

            if (t < schedResults->numberOfSimCycles)
            {
                if (schedResults->SimulationResults[t] == i)
                {
                    color = GetTaskColor(i);
                    strcat(row, color);
                }

                if (schedResults->SimulationResults[t] == -1)
                {
                    color = GetTaskColor(-1);
                    strcat(row, color);
                }
            }            
            
            strcat(row, square);
        }

        strcat(row, endRow);        
    }

    ret = row;
    return ret;    
}

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
        aux = "red";
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
        aux = "orange";
    }  
    else if (i==-1)
    {
        aux = "white";
    }

    strcpy(color, tag);
    strcat(color, aux);
    strcat(color, endTag);

    ret = color;
    return ret;      
}
    