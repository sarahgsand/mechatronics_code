/*
 * File:   canyon_run.h
 * Author: bluev
 *
 * Created on March 14, 2024, 2:01 PM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CANYON_RUN_H
#define	CANYON_RUN_H

#include <xc.h> // include processor files - each processor file is guarded.  

static int count = 0;
// PWM Interrupts.

void __attribute__((interrupt, no_auto_psv)) _OC3Interrupt(void){
    _OC3IF = 0;
    count++;
}


//Code to turn 90 degrees to the right
void right_90(void)
{
    // Turns the robot 90 degrees.
    int N90 = 574/2; 
    count = 0; // Resets the PWM interrupt counter.
    _LATB2 = 1; // The right wheel spins backwards.
    while(count<N90){
        Nop(); // Does nothing while it's turning
    }
    _LATB2 = 0; // The right wheel spins forward again.
}

void left_90(void)
{
    // Turns the robot 90 degrees.
    int N90 = 574/2; 
    count = 0; // Resets the PWM interrupt counter.
    _LATA1 = 1; // The left wheel spins backwards.
    while(count<N90){
        Nop(); // Does nothing while it's turning
    }
    _LATA1 = 0; // The left wheel spins forward again.
}


void go_straight(void)
{
    //int N = 1600;
    count = 0;
    _LATA1 = 0;
    _LATB2 = 0;
    //while(count<N){
        //Nop(); //Does nothing for a specified number of rotations. This is technically blocking code for every time the robot isn't turning so we should have the robot go forward by another method long term.
    //}
}

void canyon_nav(void) {
    OC2RS = 9999;
    OC3RS = 9999;
    OC2R = 5000;
    OC3R = 5000;
    while(1){//Canyon state
        //if detects wall in front, stop and turn
        if(_RB7 == 0){  //changed pin (Pin 11/Front)
        //stop for a certain length of time?
            //OC3R = 0;
            //OC2R = 0;
            _LATB8 = 1;

            //if wall left
            if(_RA2 == 0){  //Pin 7/Left
                 right_90(); //changed
            }
            else{
                left_90(); //changed
            }
        }

        //else if detects line (exiting canyon)
        //else if(_RB12 == 0 && _RB13 == 0){

            //turn 90 right (clockwise around track)
           // right_90();
            //change state to line following
       // }

        //else go straight
        else {
        go_straight();
            }
    }
}
#endif	/* XC_HEADER_TEMPLATE_H */

