/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        lcd.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Control of LCD										                                    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   05.04.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*FSMC Adresses and LCD Adresses*/
#define LCD_DATA_ADDR (*((uint8_t*)0x60000000))
#define LCD_COMMAND_ADR (*((uint8_t*)0x60000001))
#define LCD_TEXT_HOME_ADDRESS						0x0000U
#define LCD_GRAPHICS_HOME_ADDRESS				0x0200U

/*LCD Commands*/
#define LCD_CMD_CURSOR_POINTER					0x21U
#define LCD_CMD_SET_ADDRESS_POINTER			0x24U
#define LCD_CMD_TEXT_HOME_ADDRESS				0x40U
#define LCD_CMD_TEXT_AREA								0x41U
#define LCD_CMD_GRAPHICS_HOME_ADDRESS		0x42U
#define LCD_CMD_GRAPHICS_AREA						0x43U
#define LCD_CMD_EXOR_MODE								0x81U
#define LCD_CMD_TEXT_ON_GRAPHICS_ON			0x9CU
#define LCD_CMD_DATA_WRITE_INCR_ADP			0xC0U
#define LCD_CMD_DATA_WRITE_INV_ADP			0xC4U
#define LCD_CMD_ONE_LINE_CURSOR					0xA0U


#define LCD_TEXT_AREA										0x1EU	//30
#define	LCD_GRAPHICS_AREA								0x1EU	//30

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */


/*  - M a c r o s     */
                                                  
/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void LCD_Init(void);
void LCD_Update_US_Sensor(uint16_t dist_left, uint16_t dist_middle, uint16_t dist_right);
void LCD_Update_Compass(uint16_t deg);
void LCD_Update_Distance_Driven(unsigned int distance);

#endif
