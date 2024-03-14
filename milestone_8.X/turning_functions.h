/* 
 * File: Turning Functions for Line Following  
 * Author: Sarah
 * Comments:
 * Revision history: Original - 3/6/2024 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TURNING_FUNCTIONS_H
#define	TURNING_FUNCTIONS_H

#include <xc.h> // include processor files - each processor file is guarded. 

void turn_right(void){
    //Left wheel stays the same.
    OC2RS = 9999;
    OC2R = 5000;
    //Right wheel goes faster
    OC3RS = 29999;
    OC3R = 15000;
}

void turn_left(void){
    // Left wheel goes faster.
    OC2RS = 29999;
    OC2R = 15000;
    // Right wheel stays the same.
    OC3RS = 9999;
    OC3R = 5000;
    
}

#endif

