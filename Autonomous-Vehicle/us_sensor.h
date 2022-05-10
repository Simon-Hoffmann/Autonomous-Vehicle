/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        eventhandler.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                   																	    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   26.04.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _US_SENSOR_H_
#define _US_SENSOR_H_

#include <stdint.h>

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*  - T y p e s                                                          */

#define US_SENSOR_LEFT 		1
#define US_SENSOR_MIDDLE 	2
#define US_SENSOR_RIGHT		4

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void US_sensor_gpio_Init(void);
void us_sensor_measure_distance(uint8_t US_sensor_position);
void us_sensor_setSensor(uint8_t US_sensor_position, uint16_t time_50us);
uint16_t us_sensor_GetDistance_left(void);
uint16_t us_sensor_GetDistance_middle(void);
uint16_t us_sensor_GetDistance_right(void);

#endif
