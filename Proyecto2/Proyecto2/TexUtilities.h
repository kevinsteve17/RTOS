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

#define SIM_COLUMNS 64

#ifdef __cplusplus
extern "C" {
#endif
    
    
    char header[] = "\\documentclass[aspectratio=43, xcolor=table]{beamer}\n"
                    "\\usepackage[english]{babel}\n"
                    "\\usepackage{pifont}\n"
                    "\\usepackage{amsmath}\n"
                    "\\usepackage[utf8]{inputenc}\n"
                    "% \\usepackage[table,xcdraw]{xcolor}\n"
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
    
    char tableSectionTemp[] = "\\begin{frame}{Scheduling tables}\n"
    "\\setlength{\\arrayrulewidth}{0.1mm}\n"
    "\\setlength{\\tabcolsep}{1pt}\n"
    "\\renewcommand{\\arraystretch}{0.5}\n"
    "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|p{3mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|}\n"
    "\\hline\n"
    "\\tiny T1& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T2& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\cellcolor{green}&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline"
    "\\tiny T3& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T4& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\end{tabular}\n"
    "\\end{table}\n"
    "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|p{3mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|}\n"
    "\\hline\n"
    "\\tiny T1&  \\cellcolor{red}&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T2&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T3&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T4&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\end{tabular}\n"
    "\\end{table}\n"
    "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|p{3mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|}\n"
    "\\hline\n"
    "\\tiny T1&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\cellcolor{blue}&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline \n"
    "\\tiny T2&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline \n"
    "\\tiny T3&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline \n"
    "\\tiny T4&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline \n"
    "\\end{tabular}\n"
    "\\end{table}\n"
    "\\end{frame}\n";
    
    char tableSectionHeader[] = "\\begin{frame}{Scheduling tables}\n"
    "\\setlength{\\arrayrulewidth}{0.1mm}\n"
    "\\setlength{\\tabcolsep}{1pt}\n"
    "\\renewcommand{\\arraystretch}{0.5}\n";
    
    char tasksTableHeader[] = "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|r|r|r|r|}\n"
    "\\hline\n";

    char simTableHeader[] = "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|p{3mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|p{1mm}|}\n"
    "\\hline\n";
    
    char tableContents[] ="\\tiny T1& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T2& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\cellcolor{green}&  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline"
    "\\tiny T3& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n"
    "\\tiny T4& &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  &  \\\\ \\hline\n";
    
    char tableEnd[] = "\\end{tabular}\n"
    "\\end{table}\n";
    
    char tableSectionEnd[] ="\\end{frame}\n";
    




#ifdef __cplusplus
}
#endif

#endif /* TEXUTILITIES_H */

