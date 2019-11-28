/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TexFileGenerator.h
 * Author: kevin
 *
 * Created on November 18, 2019, 8:04 PM
 */

#ifndef TEXFILEGENERATOR_H
#define TEXFILEGENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
#include <string.h>
#include "SimulationRTOS.h"
#include "Task.h"
    
    typedef struct CoverPageStruct CoverPage;
    typedef struct AlgorithmsStruct Algorithms;
    typedef struct TexDocumentation TextDoc;
    
    
    struct CoverPageStruct
    {
        char* Title;
        char* Authors;
        char* Course;
    };
    
    struct AlgorithmsStruct
    {
        char* Name;
        RTResults* AlgthmResult;
    };
    
    struct TexDocumentation
    {
        CoverPage TitlePage;
        Algorithms Algs; 
    };
    
    
    void GenerateCoverPage();
    void GenerateAlgorithmsResults();
    void GenerateTexFile(SchedResult* schedResults);
    char * GenerateTableSimContents();




#ifdef __cplusplus
}
#endif

#endif /* TEXFILEGENERATOR_H */

