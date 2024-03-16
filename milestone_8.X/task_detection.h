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
int pwm_counter = 0;
//int N = 54;

int task_ident(void){
//    while(1){
        //Stop when PWM count >= 54 steps
        if(pwm_counter >= N){
            _LATB8 = 1;
            pwm_counter = 0;
            
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
//    }   
}

#endif