/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "TexUtilities.h"
#include "TexFileGenerator.h"

void GenerateCoverPage()
{
    
}

void GenerateAlgorithmsResults()
{
    
}

void GenerateTexFile()
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
    
    fputs(tableSectionTemp, texFile);
    fputs(newLine, texFile);
    
    fputs(endDoc, texFile);
    
    fclose(texFile);
           
}
    