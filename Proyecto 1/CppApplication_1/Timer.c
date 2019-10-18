#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN


// Global Variables

// Quantum Variables
timer_t quantum_timerid;
struct sigevent quantum_sev;
struct itimerspec quantum_its;
struct sigaction quantum_sa;
int QuantumFlag = 0;

// Process Variables
timer_t process_timerid[25];
struct sigevent process_sev[25];
struct itimerspec process_its[25];
struct sigaction process_sa[25];


// ****************************************************************************
// ****************************************************************************
void QuantumSoftTimerHandler()
{
    /* Note: calling printf() from a signal handler is not safe
             (and should not be done in production programs), since
             printf() is not async-signal-safe; see signal-safety(7).
             Nevertheless, we use printf() here as a simple way of
             showing that the handler was called. */
    
    QuantumFlag = 1;
}


// ****************************************************************************
// ****************************************************************************
int IsQuantumOver()
{
   if (QuantumFlag == 1)
   {
       // Clear QuantumFlag after reading it
       QuantumFlag = 0;
       return 1;
   }
   else
   {
       return 0;
   }
}

// ****************************************************************************
// ****************************************************************************
void StopProcessSoftTimer(int processNumber)
{
    timer_delete(process_timerid[processNumber-1]);
}

// ****************************************************************************
// ****************************************************************************
void StopQuantumSoftTimer()
{
    timer_delete(quantum_timerid);
}

// ****************************************************************************
// ****************************************************************************
void StartProcessSoftTimer(int processNumber,int freq_nanosecs)
{  
    /* Create the timer */

    process_sev[processNumber-1].sigev_notify = SIGEV_SIGNAL;
    process_sev[processNumber-1].sigev_signo = SIG;
    process_sev[processNumber-1].sigev_value.sival_ptr = &process_timerid[processNumber-1];
    timer_create(CLOCKID, &process_sev[processNumber-1], &process_timerid[processNumber-1]);

    /* Start the timer */

    process_its[processNumber-1].it_value.tv_sec = freq_nanosecs / 1000000000;
    process_its[processNumber-1].it_value.tv_nsec = freq_nanosecs % 1000000000;
    process_its[processNumber-1].it_interval.tv_sec = process_its[processNumber-1].it_value.tv_sec;
    process_its[processNumber-1].it_interval.tv_nsec = process_its[processNumber-1].it_value.tv_nsec;

    timer_settime(process_timerid[processNumber-1], 0, &process_its[processNumber-1], NULL);
}

// ****************************************************************************
// ****************************************************************************
void StartQuantumSoftTimer(int freq_nanosecs)
{
    QuantumFlag = 0;
    
    /* Create the timer */

    quantum_sev.sigev_notify = SIGEV_SIGNAL;
    quantum_sev.sigev_signo = SIG;
    quantum_sev.sigev_value.sival_ptr = &quantum_timerid;
    timer_create(CLOCKID, &quantum_sev, &quantum_timerid);

    /* Start the timer */

    quantum_its.it_value.tv_sec = freq_nanosecs / 1000000000;
    quantum_its.it_value.tv_nsec = freq_nanosecs % 1000000000;
    quantum_its.it_interval.tv_sec = quantum_its.it_value.tv_sec;
    quantum_its.it_interval.tv_nsec = quantum_its.it_value.tv_nsec;

    timer_settime(quantum_timerid, 0, &quantum_its, NULL);
}

// ****************************************************************************
// ****************************************************************************
void SetProcessSoftTimerHandler(int processNumber ,void (*processHandlerFunction)())
{
    /* Establish handler for timer signal */

    process_sa[processNumber-1].sa_flags = SA_SIGINFO;
    process_sa[processNumber-1].sa_sigaction = processHandlerFunction;
    sigemptyset(&process_sa[processNumber-1].sa_mask);
    sigaction(SIG, &process_sa[processNumber-1], NULL);
}

// ****************************************************************************
// ****************************************************************************
void SetQuantumSoftTimerHandler()
{
    /* Establish handler for timer signal */

    quantum_sa.sa_flags = SA_SIGINFO;
    quantum_sa.sa_sigaction = QuantumSoftTimerHandler;
    sigemptyset(&quantum_sa.sa_mask);
    sigaction(SIG, &quantum_sa, NULL);
}