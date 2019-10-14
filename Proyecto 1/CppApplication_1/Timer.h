/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Timer.h
 * Author: kevin
 *
 * Created on October 13, 2019, 9:11 PM
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


/*
    * Esta funcion permite asignar el intervalo de tiempo en milisegundos, para 
    * enviar una señal. 
    * signhandler es para indicar la finalizacion de una señal.
    */
    void set_ptTimer(int pWait_Time, void (*signhandler) (int));
   /*
    * Esta funcion permite detener el ptimer antes de mandar la señal
    */
    void stop_pTimer();
   /*
    * Retorna cuanto tiempo ha transcurrido y llama a la función
    * stop_pTimer, para detenerlo.  
    */
    int get_pTimer();

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */

