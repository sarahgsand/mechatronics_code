/* 
 * File:   ball_get.h
 * Author: wongj_rl8z6
 *
 * Created on March 26, 2024, 9:23 AM
 */

#ifndef BALL_GET_H
#define	BALL_GET_H

#include "canyon_run.h"
#include "ball_sort.h"
#include "line_follow.h"

int N_straight_get = 300;
int N_reverse_get = 385;
int N_really_slow = 60;


void get_ball(void) {
    //count = 0;
    _OC3IE = 1; //Enable pwm interrupt
    while(count < N_straight_get){
        _LATB2 = 0;
        _LATA1 = 0;
        follow();
        }
        count = 0;
        //turn left 90 once in line with platform
        right_90(); 
        stop();
        //reverse
        _LATB2 = 1; //direction 1 means reverse
        _LATA1 = 1;
        //OC2R = 3500;
        //OC3R = 3500;
        //turn wheels # of times
        count = 0;
        while(count<N_reverse_get) {
            drive();
        }
        //stop    
        stop();
        //go forwards until line is detected
        count = 0;
        _LATB2 = 0; //direction 0 to go forwards
        _LATA1 = 0;
        while(count<N_really_slow){
            OC2R = 5000*3;
            OC3R = 5000*3;
            OC2RS = 9999*3;
            OC3RS = 9999*3; 
        }
        while(count<N_reverse_get) {
            //drive();
            OC2R = 5000;
            OC3R = 5000;
            OC2RS = 9999;
            OC3RS = 9999; 
        }
            //turn right
            left_90();
        //start line following
        follow();
}

#endif	/* BALL_GET_H */

