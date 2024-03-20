// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LINE_FOLLOW_H
#define	LINE_FOLLOW_H

#include <xc.h> // include processor files - each processor file is guarded. 

void follow(void){
    //Go straight.
    if(_RB12 == _RB13){
        OC2RS = 9999;
        OC2R = 5000;
        OC3RS = 9999    ;
        OC3R = 5000;
    }
    if(_RB12^_RB13){
    //The robot is too far right.
        if(_RB12==0){ // Proximity sensor is white (low).
            //Left wheel stays the same.
            OC2RS = 9999;
            OC2R = 5000;
            //Right wheel goes faster
            OC3RS = 29999;
            OC3R = 15000;
        }
        //The robot is too far left.
        if(_RB13==0){
            // Left wheel goes faster.
            OC2RS = 29999;
            OC2R = 15000;
            // Right wheel stays the same.
            OC3RS = 9999;
            OC3R = 5000;
        }
    }
}

void follow_slow(void){
    //Go straight.
    if(_RB12 == _RB13){
        OC2RS = 9999*3;
        OC2R = 5000*3;
        OC3RS = 9999*3;
        OC3R = 5000*3;
    }
    if(_RB12^_RB13){
    //The robot is too far right.
        if(_RB12==0){ // Proximity sensor is white (low).
            //Left wheel stays the same.
            OC2RS = 9999*3;
            OC2R = 5000*3;
            //Right wheel goes faster
            OC3RS = 30000*3;
            OC3R = 15000*3;
        }
        //The robot is too far left.
        if(_RB13==0){
            // Left wheel goes faster.
            OC2RS = 30000*3;
            OC2R = 15000*3;
            // Right wheel stays the same.
            OC3RS = 9999*3;
            OC3R = 5000*3;
        }
    }
}

#endif

