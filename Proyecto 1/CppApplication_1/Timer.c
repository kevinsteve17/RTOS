/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Timer.h"
#define NULL ((void*)0)


typedef struct itimerval time_val;

/*
 * Esta funcion permite asignar el intervalo de tiempo en milisegundos, para 
 * enviar una señal. 
 * signhandler es para indicar la finalizacion de una señal.
 */
void set_ptTimer(int pWait_Time, void (*signhandler) (int)){
    int sec = pWait_Time / 1000;
    int usec = (pWait_Time % 1000) * 1000;
/*
    time_val.it_interval.tv_sec = 0;
    time_val.it_interval.tv_usec = 0;
    time_val.it_value.tv_sec = sec;
    time_val.it_value.tv_usec = usec;
    if (signhandler != NULL)
        signal(SIGALRM, signhandler);
    setitimer(ITIMER_REAL, &time_val, 0);
*/
}

/*
 * Esta funcion permite detener el ptimer antes de mandar la señal
 */
void stop_pTimer(){
     set_ptTimer(0, NULL);
}

/*
 * Retorna cuanto tiempo ha transcurrido y llama a la función
 * stop_pTimer, para detenerlo.  
 */
int get_pTimer(){
    //getitimer(ITIMER_REAL, &time_val);
    int tiempoRestante = 0; //time_val.it_value.tv_usec;
    stop_pTimer();
    return (tiempoRestante/1000);
}
