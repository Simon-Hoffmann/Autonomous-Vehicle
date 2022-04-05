/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        main.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Main Programm									                                      *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   28.03.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/


/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "stm32g474xx.h"
#include "event.h"
#include "eventhandler.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */



/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */



/* ----------------------- F U N C T I O N S  -------------------------- */




/* --------------  S t a r t    o f    p r o g r a m  -----------------  */

	
int main(void)
{
	EVENT_T curEvent;
	event_SetEvent(EVT_INIT, 0);
	
	while(1)
	{
		curEvent = event_GetEvent();
		eventhandler_Handler1(curEvent);
	}
}
