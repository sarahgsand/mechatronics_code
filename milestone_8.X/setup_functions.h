/*
 * File: Microcontroller Setup Functions 
 * Author: Sarah
 * Comments:
 * Revision history: Original - 3/6/2024 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SETUP_FUNCTIONS_H
#define	SETUP_FUNCTIONS_H

#include "xc.h"

void setup_pwm(void)
{
 //Set up OC2 on pin 4.
OC2CON1 = 0;
OC2CON2 = 0;
OC2CON1bits.OCTSEL = 0b111;
OC2CON2bits.SYNCSEL = 0b11111;
OC2CON2bits.OCTRIG = 0;
OC2RS = 9999; //One rev/sec
OC2R = 0; //Set the duty cycle initially to zero (PWM off)
OC2CON1bits.OCM = 0b110; //Enable PWM.

//Set up OC3 on pin 5.
OC3CON1 = 0;
OC3CON2 = 0;
OC3CON1bits.OCTSEL = 0b111;
OC3CON2bits.SYNCSEL = 0b11111;
OC3CON2bits.OCTRIG = 0;
OC3RS = 9999; //One rev/sec
OC3R = 0; //Set the duty cycle initially to zero (PWM off)
OC3CON1bits.OCM = 0b110; //Enable PWM.

// Set up PWM Interrupt.
_OC2IP = 4; // Set Priority to 4.
_OC2IF = 0; // Set the flag to zero just in case.
}

//Set up digital input/output.
void setup_dio(){
    //Set up the stepper motor pins and set both directions to forward.
    _ANSB2 = 0;
    _TRISB2 = 0;
    _LATB2 = 0;
    
    _ANSA1 = 0;
    _TRISA1 = 0;
    _LATA1 = 0;
    
    // Set up Button on pin 17 as digital input.
    _ANSB14 = 0;
    _TRISB14 = 1;
    
    //Set up line following sensors as digital inputs.
    _ANSB12 = 0;
    _TRISB12 = 1;
    _ANSB13 = 0;
    _TRISB13 = 1;
    
    //Set up Prox sensor for task detection as digital input.
    _ANSA0 = 0;
    _TRISA0 = 1;
}
#endif