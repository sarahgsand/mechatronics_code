/*
 * File:   main.c
 * Author: sarah
 *
 * Created on March 13, 2024, 4:52 PM
 */


#include "xc.h"
#pragma config FNOSC = FRC // Configure 8Mhz Oscillator

#include "line_follow.h"
#include "canyon_run.h"

int pwm_counts = 0;

void __attribute__((interrupt, no_auto_psv)) _OC2Interrupt(void){
    _OC2IF = 0;
    pwm_counts++;
}

#include "setup_functions.h"

enum{SLEEP,LINE_FLW,LINE_DETECT, BALL_GET,BALL_DROP,CANYON} state = SLEEP;
int task_num = 1;
int N = 65; //52 is good for full speed, dropped for 1/3 speed

int main(void) {
    _RCDIV = 0;
    setup_pwm();
    setup_dio();
    state = SLEEP;
    
    while(1)
    {
        switch(state) {
            case SLEEP:
                OC2R = 0;
                OC3R = 0;
                if (_RB14)  {
                    OC2R = 5000; //Enable the PWM by setting the duty cycle.
                    OC3R = 5000;
                    state = LINE_FLW;
                }
                break;
                
            case LINE_FLW:
                follow();
                _LATB8 = 1;
                //Detect if task
                if(_RA0 == 0) {     //Task Detector detected white line                   
                    //task_num = 0;
                    _OC2IF = 0; // Set the flag to zero just in case.
                    pwm_counts = 0;
                    _OC2IE = 1; //Enable PWM interrupt
                    int task_num = 1; // Set the line count to 1. The robot has already detected a line when this function is triggered.
                    //Move forward
//                    OC2RS = 9999;
//                    OC2R = 5000;
//                    OC3RS = 9999;
//                    OC3R = 5000;
                    follow();
                    _LATB8 = 0;
                    state = LINE_DETECT;
                }
                break;
            case LINE_DETECT:
                follow_slow();
                if(pwm_counts >= N){
                                //while(1){OC2R = 0; OC3R = 0;} //use for testing distance travelled in N steps
                    //Checks if prox sensor white or black.
                    if(_RA0 == 0){
                        task_num++; // Detected another line.
                        pwm_counts = 0;
                    }
                    else{
                        _OC2IE = 0; //Disable pwm interrupt
                        OC2R = 0;
                        OC3R = 0;
                        if(task_num == 1){
                            _LATB8 = 1;                           
                        }
                        if(task_num == 2){
                            //_LATB8 = 1;
                            state = BALL_GET;
                        }
                        else if(task_num == 3) {
                            //_LATB8 = 1;
                            state = BALL_DROP;
                        }
                        else if(task_num == 4) {
                            //_LATB8 = 1;
                            state = CANYON;
                        }
                    }
                }
                break;
            case BALL_GET:
                OC2R = 5000;
                OC3R = 5000;
                task_num = 1;
                state = LINE_FLW;
                _LATB8 = 0;
                break;
            case BALL_DROP:
                OC2R = 5000;
                OC3R = 5000;
                task_num = 1;
                state = SLEEP;
                break;
            case CANYON:
                OC2R = 5000;
                OC3R = 5000;
                task_num = 1;
                _OC3IE = 1;
                canyon_nav();
                if(_RB12 == 1 && _RB13 ==1){
                    state = SLEEP;
                }
                break;

        }
    }
    return 0;
}
