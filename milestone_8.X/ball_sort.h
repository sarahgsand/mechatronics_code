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
    OC2R = 5000*3/2;
    OC3R = 5000*3/2;
    OC2RS = 9999*3/2;
    OC3RS = 9999*3/2; //changed
}

#endif	/* XC_HEADER_TEMPLATE_H */

