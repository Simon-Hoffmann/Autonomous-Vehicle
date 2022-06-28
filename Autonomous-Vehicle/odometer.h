/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        odometer.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Reads distance from odometer                                       *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   24.05.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _ODOMETER_H_
#define _ODOMETER_H_

#include "stm32g474xx.h"

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void odometer_Init(void);
void odometer_check_distance(int distance_cm);
void odometer_check_turn(uint16_t degrees);
int getDistanceDriven(void);
void updateDirection(int degrees, uint8_t direction);
int odometer_GetDirection(void);

#endif

