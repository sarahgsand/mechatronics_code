/* 
 * File:   timer_setup.h
 * Author: wongj_rl8z6
 *
 * Created on March 14, 2024, 12:57 PM
 */

#ifndef TIMER_SETUP_H
#define	TIMER_SETUP_H
static int timeup = 0;

#include <xc.h> // include processor files - each processor file is guarded.

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    _T1IF = 0;  //Clear interrupt flag
    timeup = 1;
   
}

void timer_config(void){
//put this in main
// Configure Timer1
    T1CONbits.TON = 1;  //turns timer on
    T1CONbits.TCS = 0;  //use internal clock, not external
    T1CONbits.TCKPS = 0b10;     //1:64 Pre-scale
    //int sec = 3906;
    PR1 = 0.136*OC2RS;        //timer period of 5 sec
    TMR1 = 0;           //Reset timer
    
}

#endif	/* TIMER_SETUP_H */

