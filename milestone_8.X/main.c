/*
 * File:   main.c
 * Author: sarah
 *
 * Created on March 13, 2024, 4:52 PM
 */


#include "xc.h"
#include "turning_functions.h"

static int pwm_counts = 0;

void __attribute__((interrupt, no_auto_psv)) _OC2Interrupt(void){
    _OC2IF = 0;
    pwm_counts++;
}

#include "task_detection.h"



#pragma config FNOSC = FRC // Configure 8Mhz Oscillator

#include "setup_functions.h"

int main(void) {
    setup_pwm();
    setup_dio();
        while(1)
    {
        if(_RB14){ //If the button is pressed.
            OC2R = 5000; //Enable the PWM by setting the duty cycle.
            OC3R = 5000;
            while(1){
                //Go straight.
                if(_RB12 == _RB13){
                    OC2RS = 9999;
                    OC2R = 5000;
                    OC3RS = 9999;
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
            }
        }
    }
    return 0;
}
