/*
 * File:   main.c
 * Author: sarah
 *
 * Created on March 13, 2024, 4:52 PM
 */


#include "xc.h"
#pragma config FNOSC = FRC // Configure 8Mhz Oscillator

#include "turning_functions.h"
#include "timer_setup.h"

int pwm_counts = 0;
void delay(int s)   //this creates the delay function, s is in milliseconds
{
    int k = 0;
    while(k < s)
        k++;
}


void __attribute__((interrupt, no_auto_psv)) _OC2Interrupt(void){
    _OC2IF = 0;
    pwm_counts++;
}

#include "task_detection.h"

#include "setup_functions.h"

enum{SLEEP,LINE_FLW,BALL_GET,BALL_DROP,CANYON} state = SLEEP;
int task_num = 0;

int main(void) {
    setup_pwm();
    setup_dio();
    
   
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
                //Detect if task
                if(_RA0 == 0) {     //Task Detector detected white line                   
                    task_num=0;
                    task_num = task_ident();
                    if(task_num){
                        OC2R = 0; //Stop robot
                        OC3R = 0;
                        if(task_num = 2){
                            state = BALL_GET;
                        }
                        else if(task_num = 3) {
                            state = BALL_DROP;
                        }
                        else if(task_num = 4) {
                            state = CANYON;
                        }
                    }
                }
                //Go straight.
                if(_RB12 == _RB13){
                    OC2RS = 9999;
                    OC2R = 5000;
                    OC3RS = 9999    ;
                    OC3R = 5000;
                }
                if(_RB12^_RB13){
                //The robot is too far right.
                while(_RB12==0){ // Proximity sensor is white (low).
                    turn_left();
                }
                //The robot is too far left.
                while(_RB13==0){
                    turn_right();
                }
                }
            case BALL_GET:
                delay(2000);
                OC2R = 5000;
                OC3R = 5000;
                state = LINE_FLW;
                break;
            case BALL_DROP:
                delay(5000);
                OC2R = 5000;
                OC3R = 5000;
                state = LINE_FLW;
                break;
            case CANYON:
                OC2R = 5000;
                OC3R = 5000;
                state = LINE_FLW;
                break;

        }
    }
    return 0;
}
