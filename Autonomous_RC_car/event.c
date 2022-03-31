/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        event.c                                           		  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                      															    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation 									  *
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "event.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------  F U N C T I O N   D E F I N I T I O N ----------------- */

#define CIRCLE_BUFFER_SIZE 	50

static EVENT_T circularBuffer[CIRCLE_BUFFER_SIZE] = {0};
static uint8_t readIndex = 0;
static uint8_t writeIndex = 0;
static uint8_t bufferLength = 0;
static EVENT_T event;

/**
* @brief  Adds Event to circleBuffer
* @param  eventID:		placeholder
*					Parameter:	placeholder
* @retval None
*/
void event_SetEvent(uint16_t eventID, uint16_t Parameter){
	if(bufferLength == CIRCLE_BUFFER_SIZE)
		return;
	
	event.EventID = eventID;
	event.EventParameter = Parameter;
	
	circularBuffer[writeIndex++] = event;
	bufferLength++;
	
	if(writeIndex == CIRCLE_BUFFER_SIZE)
		writeIndex = 0;
}

/**
* @brief  Gets oldest event from circleBuffer
* @param  None
* @retval EVENT_T:	The next event that is to happen
*/
EVENT_T event_GetEvent(void){
	if(bufferLength == 0){
		event.EventID = EVT_NOEVENT;
		event.EventParameter = 0;
	} else{
		event = circularBuffer[readIndex++];
		bufferLength--;
	
		if(readIndex == CIRCLE_BUFFER_SIZE)
			readIndex = 0;
	}
	return event;
}

