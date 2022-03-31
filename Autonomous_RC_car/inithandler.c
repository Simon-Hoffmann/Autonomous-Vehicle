/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        inithandler.c                                           		  *
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

#include "inithandler.h"
#include "led.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------  F U N C T I O N   D E F I N I T I O N ----------------- */

void inithandler_initialise(void){
	led_Init();
}