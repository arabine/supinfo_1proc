/* ---------------------------------------------------------------- */
/* MONITOR  inc-dec-m.c:                                            */
/*    This monitor provides the following procedures for a counter: */
/*    (1)  CounterInit() - initialize the counter                   */
/*    (2)  INC()         - increase the counter value by one        */
/*    (3)  DEC()         - decrease the counter value by one        */
/*    (4)  SET()         - reset the counter value with a new value */
/*    (5)  GET()         - retrieve the counter value               */
/* To establish mutual exclusion, a mutex lock is used.             */
/* The counter and the lock are static in this file so that they    */
/* cannot be accessed from outside of this function.                */
/*                                                                  */
/* Although several functions return the value of the counter, this */
/* returned value may not be accurate since before the retrieved    */
/* value can be returned to a thread, the counter may have already  */
/* been reset, increased or decreased.                              */
/* ---------------------------------------------------------------- */

#include  <thread.h>
#include  <synch.h>

#include  "inc-dec-m.h"

static  int  count;                     /* the static counter       */

static  mutex_t  MonitorLock;           /* the static mutex lock    */

/* ---------------------------------------------------------------- */
/* FUNCTION  CounterInit() :                                        */
/*      Initialize the simulated monitor.                           */
/* ---------------------------------------------------------------- */

void  CounterInit(int  n)
{
     count = n;
     mutex_init(&MonitorLock, USYNC_THREAD, (void *) NULL);
}

/* ---------------------------------------------------------------- */
/* FUNCTION  INC() :                                                */
/*      Increase the counter value by one.                          */
/* ---------------------------------------------------------------- */

int  INC(void)
{
     int  value;

     mutex_lock(&MonitorLock);          /* lock the monitor         */
          value = (++count);            /* increase and save counter*/
     mutex_unlock(&MonitorLock);        /* release the monitor      */
     return  value;                     /* return the new value     */
}

/* ---------------------------------------------------------------- */
/* FUNCTION  DEC() :                                                */
/*      Decrease the counter value by one.                          */
/* ---------------------------------------------------------------- */

int  DEC(void)
{
     int  value;

     mutex_lock(&MonitorLock);
          value = (--count);
     mutex_unlock(&MonitorLock);
     return  value;
}

/* ---------------------------------------------------------------- */
/* FUNCTION  SET() :                                                */
/*      Set the counter to a new value.                             */
/* ---------------------------------------------------------------- */

void  SET(int  n)
{
     mutex_lock(&MonitorLock);
          count = n;
     mutex_unlock(&MonitorLock);
}

/* ---------------------------------------------------------------- */
/* FUNCTION  GET() :                                                */
/*      Retrieve the counter's value.                               */
/* ---------------------------------------------------------------- */

int  GET(void)
{
     int  value;

     mutex_lock(&MonitorLock);
          value = count;
     mutex_unlock(&MonitorLock);
     return  value;
}


