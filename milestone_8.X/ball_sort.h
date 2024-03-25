/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BALL_SORT_H
#define	BALL_SORT_H

#include "xc.h"

void stop(void) {
    OC2R = 0;
    OC3R = 0;
}

void drive(void) {
    OC2R = 3500;
    OC3R = 3500;
    OC2RS = 9999;
    OC3RS = 9999;
}

#endif	/* XC_HEADER_TEMPLATE_H */

