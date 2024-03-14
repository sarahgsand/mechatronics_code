/* 
 * File: Task Detection Functions 
 * Author: Sarah
 * Comments:
 * Revision history: Original - 3/13/24 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASK_DETECTION_H
#define	TASK_DETECTION_H

#include <xc.h> // include processor files - each processor file is guarded.
static int pwm_counter = 0;

int task_ident(void){
    //Unused PWM Interrupt Code
        //int N = 171*3;
        //_OC2IF = 0; // Set the flag to zero just in case.
        //pwm_counter = 0;
        //_OC2IE = 0; //Enable PWM interrupt
    
    int count = 1; // Set the line count to 1. The robot has already detected a line when this function is triggered.
    //Move forward
    OC2RS = 9999;
    OC2R = 5000;
    OC3RS = 9999;
    OC3R = 5000;
    while(1){
        TMR1 = 0; //Reset timer
        //Stop when PWM count >= 171 steps
        //if(pwm_counter >= N){
        //    pwm_counter = 0;
        
        if(timeup){
            timeup = 0;
            //Checks if prox sensor white or black.
            if(_RA0 == 0){
                count++; // Detected another line. 
            }
            else{
                _OC2IE = 0; //Disable pwm interrupt
                OC2R = 0;
                OC3R = 0;
                return count;
            }
        }
    }
}

#endif