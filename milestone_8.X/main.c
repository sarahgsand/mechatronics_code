/*
 * File:   main.c
 * Author: sarah
 *
 * Created on March 13, 2024, 4:52 PM
 * Last updated: 3/23/24
 */


#include "xc.h"
#pragma config FNOSC = FRC // Configure 8Mhz Oscillator
//#pragma config ICS = PGx3

#include "line_follow.h"
#include "canyon_run.h"
#include "ball_sort.h"
#include "ball_get.h"

int pwm_counts = 0;

void __attribute__((interrupt, no_auto_psv)) _OC2Interrupt(void){
    _OC2IF = 0;
    pwm_counts++;
}

#include "setup_functions.h"

enum{SLEEP,LINE_FLW,LINE_DETECT, BALL_GET,BALL_DROP,CANYON} state = SLEEP;

// Task Detection Variables.
int task_num = 1;
int N = 65; //52 is good for full speed, dropped for 1/3 speed (Spacing between task detection lines.)

// Ball Sorting Variables: 
int N_straight_sort = 364; //Number of PWM cycles to go straight //OG: 364
int N_reverse = 122; //Number of PWM cycles to go reverse
int isblack = 0; // If the ping-pong ball is black or not.
//int N_straight_get = 300;
//int N_reverse_get = 200;

int main(void) {
    //_RCDIV = 0;
    setup_pwm();
    setup_dio();
    OC2R = 0;
    OC3R = 0;
    //Disabling the interrupts here to try to help with button issues.
    _OC2IE = 0;
    _OC3IE = 0;
    state = SLEEP;
    
    while(1)
    {

//        OC2R = 5000; //Code to check hardware problems,
//        OC3R = 5000; //it just runs the robot straight.
//        OC2RS = 9999;
//        OC3RS = 9999;
       ///*              //Will comment out entire code
        switch(state) {
            case SLEEP:
                if (_RB14)  {
                    OC2R = 5000; //Enable the PWM by setting the duty cycle.
                    OC3R = 5000;
                    //OC2RS = OC2R*2;
                    //OC3RS = OC3R*2;
                    state = LINE_FLW;
                }
                break;
                
            case LINE_FLW:
                follow();
                _LATB8 = 1;
                //Detect if task
                if(_RA0 == 0) {     //Task Detector detected white line                   
                    _OC2IF = 0; // Set the flag to zero just in case.
                    pwm_counts = 0;
                    _OC2IE = 1; //Enable PWM interrupt
                    int task_num = 1; // Set the line count to 1. The robot has already detected a line when this function is triggered.
                    follow();
                    //_LATB8 = 0; This was messing with the button for reasons beyond my comprehension.
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
                            _OC3IE = 1;
                            state = BALL_GET;
                        }
                        else if(task_num == 3) {
                            //_LATB8 = 1;
                            count = 0;  //Reset pwm counter
                            task_num = 1; // Reset task_num
                            OC2RS = 9999;
                            OC3RS = 9999;
                            OC2R = 5000;
                            OC3R = 5000;
                            _OC3IE = 1;
                            state = BALL_DROP;
                        }
                        else if(task_num >= 4) {
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
                count = 0;
                get_ball();
                state = LINE_FLW;
                _LATB8 = 0;
                
                break;
            case BALL_DROP:
                task_num = 1;
                while(count < N_straight_sort){
                    _LATB2 = 0;
                    _LATA1 = 0;
                    follow();
                }
                if(_RB15) { 
                    //if black, go to the right box
                    //turn left 90
                    left_90(); 
                    stop();
                    isblack = 1;
                }
                else  {
                    //turn right 90 
                    right_90();
                    stop();
                    isblack = 0;
                }
                //reverse
                _LATB2 = 1; //direction 1 means reverse
                _LATA1 = 1;
                //turn wheels # of times
                count = 0;
                while(count<N_reverse) {
                    drive();
                }
                //stop    
                stop();
                //go forwards until line is detected
                count = 0;
                _LATB2 = 0; //direction 0 to go forwards
                _LATA1 = 0;
                while(count<N_reverse) {
                    drive();
                }

                if(isblack) {
                    //if black, turn right
                    right_90();
                }
                else {
                    //if white, turn left
                    left_90();
                }
                //start line following
                OC2RS = 9999;
                OC3RS = 9999;
                OC2R = 3500; //Enable the PWM by setting the duty cycle.
                OC3R = 3500;
                state = LINE_FLW;
                _OC3IE = 0; //disable pwm interrupt
                break;
                
                case CANYON:
                    OC2R = 5000;
                    OC3R = 5000;
                    task_num = 1;
                    _OC3IE = 1;
                    canyon_nav();
                    break;

        }
        //*/
    }
    return 0;
}
