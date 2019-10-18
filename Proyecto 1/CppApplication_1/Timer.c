#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN


// Global Variables
timer_t timerid;
struct sigevent sev;
struct itimerspec its;
long long freq_nanosecs;
struct sigaction sa;
int QuantumFlag = 0;


// ****************************************************************************
// ****************************************************************************
void SoftTimerHandler()
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
void StopSoftTimer()
{
    timer_delete(timerid);
}


// ****************************************************************************
// ****************************************************************************
void StartSoftTimer(int freq_nanosecs)
{
    QuantumFlag = 0;
    
    /* Create the timer */

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = &timerid;
    timer_create(CLOCKID, &sev, &timerid);

    /* Start the timer */

    its.it_value.tv_sec = freq_nanosecs / 1000000000;
    its.it_value.tv_nsec = freq_nanosecs % 1000000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    timer_settime(timerid, 0, &its, NULL);
}

// ****************************************************************************
// ****************************************************************************
void SetSoftTimerHandler()
{
    /* Establish handler for timer signal */

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = SoftTimerHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIG, &sa, NULL);
}