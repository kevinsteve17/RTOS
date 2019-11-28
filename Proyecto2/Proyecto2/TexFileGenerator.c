/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "TexUtilities.h"
#include "TexFileGenerator.h"
#include "Utilities.h"

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
    fputs(GenerateTableSimContents(), texFile);
    fputs(tableEnd, texFile);
    fputs(tableSectionEnd, texFile);
    // table
    
    fputs(endDoc, texFile);
    
    fclose(texFile);
           
}

char * GenerateTableSimContents()
{
    return 
    "\\tiny T1& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T2& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline"
    "\\tiny T3& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T4& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n";
}

void contents(SchedResult* schedResults)
{
    char row[2048];
    char aux[12];
    char *tiny = "\\tiny T";
    char *square = "&";
    char *ret = "\n";
    char *green = "\\cellcolor{green}";
    char *grey = "\\cellcolor{grey}";
    char *red = "\\cellcolor{red}";
    char *blue = "\\cellcolor{blue}";
    char *space = " ";

    for (int i = 0; i < numberOfTasks; i++)
    {
        strcpy(row, tiny);
        sprintf(aux, "%d", i);
        strcat(row, aux);
        strcat(row, square);
        strcat(row, space);
        
        for (int t = 0; i < SIM_CYCLES; i++)
        {
            
        }
        
    }    
}
    