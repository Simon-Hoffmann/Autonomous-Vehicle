/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        event.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                   																	    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _EVENT_H_
#define _EVENT_H_

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/*---------------------EVENTS------------------*/
#define EVT_NOEVENT 									0
#define EVT_INIT 											1
/*LED*/
#define EVT_LED_ON										2
#define EVT_LED_OFF										3
#define EVT_LED_BLINK									4
/*U.S. Sensor*/
#define EVT_US_SENSOR_READ  					5
#define EVT_US_SENSOR_SET_LEFT_DIST		6
#define EVT_US_SENSOR_SET_MIDDLE_DIST	7
#define EVT_US_SENSOR_SET_RIGHT_DIST	8
/*LCD*/
#define EVT_LCD_DISTANCE_UPDATE				9
#define EVT_LCD_COMPASS_UPDATE				10
#define EVT_LCD_DISTANCE_DRIVEN_UPDATE 11
/*COMPASS*/
#define EVT_COMPASS_GET_DIRECTION			12
/*MOTOR*/
#define EVT_MOTOR_DRIVE_FORWARD				13
#define EVT_MOTOR_DRIVE_BACKWARD			14
#define EVT_MOTOR_TURN_LEFT						15
#define EVT_MOTOR_TURN_RIGHT					16
#define EVT_MOTOR_STOP_ALL						17
#define EVT_MOTOR_STOP_LEFT						18
#define EVT_MOTOR_STOP_RIGHT					19
#define EVT_MOTOR_DRIVE_DISTANCE			20
#define EVT_MOTOR_TURN_LEFT_DEGREES		21
#define EVT_MOTOR_TURN_RIGHT_DEGREES	22
/*ODOMETER*/
/*DELAY*/
#define EVT_DELAY_MS									23
/*AUTONOMOUS DRIVING*/
#define EVT_AUTODRIVE_DRIVELOGIC			24
/*  - T y p e s                                                          */

typedef struct {
	uint16_t EventID;
	uint16_t EventParameter;
}	EVENT_T;

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

/*  - P u p b l i c   V a r i a b l e s                                  */

static volatile bool nextDriveEvent = false;

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void event_SetEvent(uint16_t eventID, uint16_t Parameter);
EVENT_T event_GetEvent(void);

#endif
