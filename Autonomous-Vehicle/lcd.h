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

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*FSMC Adresses and LCD Adresses*/
#define LCD_DATA_ADDR (*((uint8_t*)0x60000000))
#define LCD_COMMAND_ADR (*(uint8_t*)0x60000001)
#define LCD_TEXT_HOME_ADDRESS						0x000
#define LCD_GRAPHICS_HOME_ADDRESS				0x200

/*LCD Commands*/
#define LCD_CMD_CURSOR_POINTER					0x21
#define LCD_CMD_SET_ADDRESS_POINTER			0x24
#define LCD_CMD_TEXT_HOME_ADDRESS				0x40
#define LCD_CMD_TEXT_AREA								0x41
#define LCD_CMD_GRAPHICS_HOME_ADDRESS		0x42
#define LCD_CMD_GRAPHICS_AREA						0x43
#define LCD_CMD_EXOR_MODE								0x81
#define LCD_CMD_TEXT_ON_GRAPHICS_ON			0x9C
#define LCD_CMD_DATA_WRITE_INCR_ADP			0xC0


#define LCD_TEXT_AREA										30
#define	LCD_GRAPHICS_AREA								30

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s     */
                                                  
/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */

void LCD_Init(void);
void LCD_InitTest(void);

#endif
