/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        autodrive.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                         *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   31.05.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */


/*-------------------------- I N C L U D E S ----------------------------*/

#include "autodrive.h"
#include "event.h"
#include "delay.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

bool driveForwardAfterTurn = false;

void driveLogic(uint16_t us_sensor_middle_cm, uint16_t us_sensor_left_cm, uint16_t us_sensor_right_cm, int direction){
	if(driveForwardAfterTurn){
		event_SetEvent(EVT_MOTOR_DRIVE_FORWARD, 0);
		nextDriveEvent = true;
		driveForwardAfterTurn = false;
		return;
	}
	
	if(us_sensor_left_cm <= 15){
		event_SetEvent(EVT_MOTOR_TURN_RIGHT_DEGREES, 30);
	} else if(us_sensor_right_cm <= 15){
		event_SetEvent(EVT_MOTOR_TURN_LEFT_DEGREES, 30);
	} else if(us_sensor_middle_cm <= 15){
		if(us_sensor_right_cm > us_sensor_left_cm){
			event_SetEvent(EVT_MOTOR_TURN_RIGHT_DEGREES, 30);
		}else{
			event_SetEvent(EVT_MOTOR_TURN_LEFT_DEGREES, 30);
		}
	}else	if(us_sensor_left_cm > (us_sensor_middle_cm + 40) && us_sensor_left_cm > (us_sensor_right_cm + 40) ){
		event_SetEvent(EVT_MOTOR_TURN_LEFT_DEGREES, 30);
		driveForwardAfterTurn = true;
	}else if (us_sensor_right_cm > (us_sensor_middle_cm + 40) && us_sensor_right_cm > (us_sensor_left_cm + 40) ){
		event_SetEvent(EVT_MOTOR_TURN_RIGHT_DEGREES, 30);
		driveForwardAfterTurn = true;
	}else {
		event_SetEvent(EVT_MOTOR_DRIVE_FORWARD, 0);
		nextDriveEvent = true;
	}
	
	
	//event_SetEvent(EVT_DELAY_MS, 2000);
	

}
