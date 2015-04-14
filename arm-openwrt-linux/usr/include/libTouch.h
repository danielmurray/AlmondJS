/* 
 * File:   libTouch.h
 * Author: Devesh Rai <devesh@securifi.com>
 *
 * Created on 18 January, 2012, 8:20 PM
 */

#ifndef LIBTOUCH_H
#define	LIBTOUCH_H

#ifdef	__cplusplus
extern "C"
{
#endif

void setTouchHandler(void (*touchHandlerToSet) (int x, int y));
void setScreenLockHandler(void (*screenLockHandlerToSet)(void));
/********************************  
 * WARNING!                     *
 * Assign touchHandler BEFORE   *
 * calling libTouchInit();      *
 ********************************/
void libTouchInit(void);
void libTouchInitNoInterrupt(void);
/*Depreciated functions. Avoid calling. Use touchHandler Event*/
int readX(void);
int readY(void);
void waitForPenUp(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIBTOUCH_H */

