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
#include "RateMonotonicScheduler.h"
#include "SimulationRTOS.h"
    
    typedef struct CoverPageStruct CoverPage;
    typedef struct AlgorithmsStruct Algorithms;
    typedef struct TexDocumentation TexDoc;
    
    
    struct CoverPage
    {
        char* Title;
        char* Authors;
        char* Course;
    };
    
    struct Algorithms
    {
        char* Name;
        RTResults* AlgthmResult;
    };
    
    struct TextDoc
    {
        CoverPage TitlePage;
        Algorithms Algs; 
    };
    
    
    void GenerateCoverPage();
    void GenerateAlgorithmsResults();
    void GenerateTexFile();
    




#ifdef __cplusplus
}
#endif

#endif /* TEXFILEGENERATOR_H */

