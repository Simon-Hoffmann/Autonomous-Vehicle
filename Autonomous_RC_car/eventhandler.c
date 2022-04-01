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

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------  F U N C T I O N   D E F I N I T I O N ----------------- */

static void initHandler(){
	led_Init();
}

void eventhandler_Handler1(EVENT_T curEvent){
	switch(curEvent.EventID){
		case EVT_NOEVENT:
			break;
		case EVT_INIT:
			initHandler();
			break;
		case EVT_LED_ON:
			led_On();
			break;
		case EVT_LED_OFF:
			led_Off();
			break;
		case EVT_LED_BLINK:
			led_Blink(curEvent.EventParameter);
			break;
		default:
			break;
	}
}
