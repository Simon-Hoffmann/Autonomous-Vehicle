/**************************************************************************
 *  COPYRIGHT (C) Peter Raab  2022                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************
 *  PROJECT       AEiSy: Px - Basisproject                                *
 *  MODULE        main.c                                                  *
 *  REVISION      1.0                                                     *
 **************************************************************************
 *  PURPOSE:                                                              *
 *   The main routine is the start of every C-program. The purpose of     *
 *   the main is to initialize the hardware and start the operation       *
 *   system.                                                              *
 *                                                                        *
 **************************************************************************
 *  REMARKS:                                                              *
 *                                                                        *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Revision  Date         Author      Description                       *
 *     1.0      01.02.2022   P. Raab     creation                         *
 *                                                                        *
 *                                                                        *
 *************************************************************************/


/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*  - I n c l u d e s                                                    */

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
