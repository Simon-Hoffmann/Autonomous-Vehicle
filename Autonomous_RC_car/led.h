/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        led.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Control of LED at GPIO Pin PE11                                      *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _LED_H_
#define _LED_H_

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/
#include <stdint.h>

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void led_Init(void);
void led_on(void);
void led_off(void);
void led_Blink(uint8_t blink_amount, uint16_t blink_duration_ms);


#endif
