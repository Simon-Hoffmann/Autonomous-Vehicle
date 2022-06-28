/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        motor.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   					                                    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   10.05.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/
 
#ifndef _MOTOR_H_
#define _MOTOR_H_


/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void motor_Init(void);
void motor_drive_forward(void);
void motor_drive_backward(void);
void motor_turn_left(void);
void motor_turn_right(void);
void motor_stop_all(void);
void motor_stop_right(void);
void motor_stop_left(void);

#endif
