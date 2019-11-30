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
                    "    Instituto Tecnologico de Costa Rica%\n"
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

    char tableFrameHeader[] = "\\begin{frame}{Scheduling tables}\n";

    char tableSectionHeader[] = "\\setlength{\\arrayrulewidth}{0.1mm}\n"
    "\\setlength{\\tabcolsep}{1pt}\n"
    "\\renewcommand{\\arraystretch}{0.5}\n";
    
    char tasksTableHeader[] = "\\begin{table}[]\n"
    "\\centering\n"
    "\\begin{tabular}{|p{5mm}|p{5mm}|p{3mm}|p{3mm}|}\n"
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
    
    //--------------------------------------------------------------------------
    char llfTheory[] =
    // Divide the theory in 2 colums
    "\\twocolumn\n"
    "\\begin{normal}\n"  
    
    // Algorithm Name
    "\\textbf{Least Laxity First (LLF)}\n"
    
    "\\vspace{4mm}\n"
    "\\end{normal}\n\n"
    "\\begin{footnotesize}\n"
    
    // Theory
    "Tambien conocido como Least Slack Time (LST) es un algoritmo de calendarizacion de tiempo real.\n"
    "Es un algoritmo dinamico en donde la prioridad se asigna a la tarea con el menor laxity en el estado actual.\n"
    
    // Formulas
    "\\[ l = (D-t)-C' \\]\n"
    
    // Bullets
    "En donde:\n"
    "\\begin{itemize}\n"
    "\\item l: laxity\n"
    "\\item D: deadline\n"
    "\\item t: tiempo\n"
    "\\item C': tiempo remanente de computacion\n"
    "\\end{itemize}\n"
      
    "Al igual que el algoritmo Earliest Deadline First (EDF) permite una utilizacion del CPU del 100\\%.\n\n"

    // Images
    "\\begin{center}\n"        
        "\\includegraphics[scale=0.82]{llf_theory_flow}\n"
    "\\end{center}\n"
    
    // Return settings to normal
    "\\onecolumn\n"
    "\\end{footnotesize}\n";
    
    
    //--------------------------------------------------------------------------
    char edfTheory[] =
    // Divide the theory in 2 colums
    "\\twocolumn\n"
    "\\begin{normal}\n"  
    
    // Algorithm Name
    "\\textbf{Earliest Deadline First (EDF)}\n"
    
    "\\vspace{4mm}\n"
    "\\end{normal}\n\n"
    "\\begin{footnotesize}\n"
    
    // Theory
    "Es un algoritmo de sistemas de tiempo real de prioridad dinamica, en donde, la prioridad se asigna a la tarea "
    "con el deadline mas proximo cada vez que una tarea entra en la cola de estado “ready”.\n\n"
    
    "\\vspace{4mm}\n"
    "Su prueba de suficiencia esta dada por:\n"
    
    // Formulas
    "\\[ \\mu = \\sum\\limits_{i=1}^n \\frac{C_i}{P_i} <= 1 \\]\n"
    
    // Bullets
    "En donde:\n"
    "\\begin{itemize}\n"
    "\\item U: utilizacion\n"
    "\\item C: tiempo de computacion\n"
    "\\item P: periodo\n"
    "\\end{itemize}\n"
      
    "Es un algoritmo optimo y permite una utilizacion del CPU del 100\\%.\n\n"

    // Images
    "\\begin{center}\n"        
        "\\includegraphics[scale=0.74]{edf_theory_flow}\n"
    "\\end{center}\n"
    
    // Return settings to normal
    "\\onecolumn\n"
    "\\end{footnotesize}\n";
    
    // -------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    char RMTheory[] =
    // Divide the theory in 2 colums
    "\\twocolumn\n"
    "\\begin{normal}\n"  
    
    // Algorithm Name
    "\\textbf{Rate Monotonic (RM)}\n"
    
    "\\vspace{4mm}\n"
    "\\end{normal}\n\n"
    "\\begin{footnotesize}\n"
    
    // Theory
    "El RM es un algoritmo dinamico en donde la prioridad de cada tarea  es inversamente proporcional a su Deadline. "
    " $\\mu$ es la utilizacion del CPU y debe ser menor o igual a 1. \n\n"
    
    "\\vspace{4mm}\n"
    "Su prueba de suficiencia esta dada por:\n"
    
    // Formulas
    "\\[ \\mu = \\sum_{n=1}^{\\ n} \\frac{C_{i}}{P_{i}} \\] y \\[  U(n) = \\sum_{1}^{\\ n} n(2^{\\frac{1}{n}} - 1) \\]\n"
    
    // Bullets
    "En donde:\n"
    "\\begin{itemize}\n"
    "\\item C: Tiempo de Computacion\n"
    "\\item P: Periodo (Deadline)\n"
    "\\end{itemize}\n"
      
    "Es un algoritmo optimo y permite una utilizacion del CPU del 100\\%.\n\n"

    // Images
    "\\begin{center}\n"        
        "\\includegraphics[scale=0.2]{RM}\n"
    "\\end{center}\n"
    
    // Return settings to normal
    "\\onecolumn\n"
    "\\end{footnotesize}\n";
    
#ifdef __cplusplus
}
#endif

#endif /* TEXUTILITIES_H */

