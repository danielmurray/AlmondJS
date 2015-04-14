/* 
 * File:   almond_timer.h
 * Author: testsystemforall
 *
 * Created on 22 August, 2012, 12:34 PM
 */

#ifndef ALMOND_TIMER_H
#define	ALMOND_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SET_PID                 0x0A
#define SET_PERIOD              0x0B
#define START_TIMER             0x0C
#define STOP_TIMER              0x0D

typedef struct TIMER_PID_INFO
{
	int pid,mills;
}AlmondTimerInfo;

#ifdef	__cplusplus
}
#endif

#endif	/* ALMOND_TIMER_H */

