/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TexUtilities.h
 * Author: kevin
 *
 * Created on November 19, 2019, 5:52 PM
 */

#ifndef TEXUTILITIES_H
#define TEXUTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif
    
    
    char header[] = "\\documentclass[aspectratio=43, xcolor=table]{beamer}\n"
                    "\\usepackage[english]{babel}\n"
                    "\\usepackage[table,xcdraw]{xcolor}\n"
                    "\\input{preamble}\n"
                    "\\title{RTOS Schedulability}\n"
                    "\\subtitle{Proyecto 2}\n"
                    "\\author[F. Paris, E. Rivera, K. Viquez]{Fernando Paris, Esteban Rivera, Kevin Viquez}\n"
                    "\\institute[ITCR]{\n"
                    "    Maestria en Sistemas Empotrados%\n"
                    "    \\\\%\n"
                    "    Instituto Tenologico de Costa Rica%\n"
                    "}"
                    "\\date{Diciembre 07, 2019}\n";
    
    
    char beginDoc[] = "\\begin{document}\n";
    
    char titlePage[] = "\\frame{\\titlepage}\n";
    
    char endDoc[] = "\\end{document}\n";
    
    char outline[] = "\\begin{frame}{Summary}\n"
                     "\\tableofcontents\n"
                     "\\end{frame}\n";
    
    char algsection[] = "\\section{Algorithms}\n";
    
    char frameSectionPage[] = "\\frame{\\sectionpage}\n";
    
    char newLine[]= "\n";
    
    char beginSection[] = "";
    char endSection[] = "";
    
    char tableSectionTemp[] = "\\begin{frame}{Schedulability Test Table}\n"
    "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|c|c|c|c|c|c|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|l|}\n"
    "\\hline\n"
    "\\cellcolor{red} &                          &                          &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline"
    "                         & \\cellcolor{green} &                          &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline"
    "                         &                          & \\cellcolor{blue} &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "                         &                          &                          &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\end{tabular}\n"
    "\\end{table}\n"
    "\\end{frame}\n";
    
    




#ifdef __cplusplus
}
#endif

#endif /* TEXUTILITIES_H */

