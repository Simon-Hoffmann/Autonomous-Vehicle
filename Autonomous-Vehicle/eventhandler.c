/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        eventhandler.c                                           		  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                      															    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   31.03.2022  		 S. Hoff & A. Svatko     creation 									  *
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "eventhandler.h"
#include "led.h"
#include "lcd.h"
#include "isr.h"
#include "us_sensor.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------  F U N C T I O N   D E F I N I T I O N ----------------- */

/**
* @brief  Initialises all Peripherals/Hardware components
* @param  None	
* @retval None
*/
static void initHandler(){
	LED_Init();
	LCD_Init();
	ISR_US_Sensor_Init();
	event_SetEvent(EVT_LED_ON, 0);
}

/**
* @brief  Handler 1 Handles no event, initialisation and LED events
* @param  curEvent:	Current event to be executed
* @retval None
*/
void eventhandler_Handler1(EVENT_T curEvent){
	switch(curEvent.EventID){
		case EVT_NOEVENT:
			break;
		case EVT_INIT:
			initHandler();
			break;
		/* ------------ L E D -----------*/
		case EVT_LED_ON:
			LED_On();
			break;
		case EVT_LED_OFF:
			LED_Off();
			break;
		case EVT_LED_BLINK:
			LED_Blink(curEvent.EventParameter);
			break;
		/* ------------ U.S. S E N S O R -----------*/
		case EVT_US_SENSOR_READ:
			us_sensor_measure_distance(curEvent.EventParameter);
			break;
		case EVT_US_SENSOR_LEFT_DIST:
			us_sensor_setSensor(US_SENSOR_LEFT, curEvent.EventParameter);
			break;
		case EVT_US_SENSOR_MIDDLE_DIST:
			us_sensor_setSensor(US_SENSOR_MIDDLE, curEvent.EventParameter);
			break;
		case EVT_US_SENSOR_RIGHT_DIST:
			us_sensor_setSensor(US_SENSOR_RIGHT, curEvent.EventParameter);
			break;
		/*------------------ L C D -------------------*/
		case EVT_LCD_DISTANCE_UPDATE:
			LCD_Update_US_Sensor(us_sensor_GetDistance_left(), us_sensor_GetDistance_middle(), us_sensor_GetDistance_right());
			break;
		default:
			break;
	}
}
