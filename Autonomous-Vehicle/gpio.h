/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        gpio.h                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   GPIO Defines	and Macros					                                    *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   07.04.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/

/*Gpio Pins used*/	
#define GPIO_PB10					B, 10U
#define GPIO_PB11					B, 11U
#define GPIO_PC2					C, 2U
#define GPIO_PC7					C, 7U
#define GPIO_PC8					C, 8U
#define GPIO_PC9					C, 9U
#define GPIO_PD0          D, 0U					
#define GPIO_PD1          D, 1U	
#define GPIO_PD4          D, 4U	
#define GPIO_PD5          D, 5U	
#define GPIO_PD7          D, 7U		
#define GPIO_PD8          D, 8U	
#define GPIO_PD9          D, 9U	
#define GPIO_PD10         D, 10U	
#define GPIO_PD11         D, 11U	
#define GPIO_PD12         D, 12U	
#define GPIO_PD13         D, 13U	
#define GPIO_PD14         D, 14U				
#define GPIO_PD15         D, 15U	
#define GPIO_PE0          E, 0U	
#define GPIO_PE1          E, 1U	
#define GPIO_PE7          E, 7U					
#define GPIO_PE8          E, 8U			
#define GPIO_PE9          E, 9U	
#define GPIO_PE15         E, 15U	
#define GPIO_PE10         E, 10U	
#define GPIO_PE11					E, 11U
#define GPIO_PF10					F, 10U		

/*GPIO MODER CONFIG*/
#define GPIO_MODE_INPUT		0x0U
#define GPIO_MODE_OUTPUT 	0x1U
#define GPIO_MODE_AF		 	0x2U
#define GPIO_MODE_ANALOG 	0x3U

/*GPIO AFR CONFIG*/
#define GPIO_AFR_AF0			0x0U
#define GPIO_AFR_AF1			0x1U
#define GPIO_AFR_AF2			0x2U
#define GPIO_AFR_AF3			0x3U
#define GPIO_AFR_AF4			0x4U
#define GPIO_AFR_AF5			0x5U
#define GPIO_AFR_AF6			0x6U
#define GPIO_AFR_AF7			0x7U
#define GPIO_AFR_AF8			0x8U
#define GPIO_AFR_AF9			0x9U
#define GPIO_AFR_AF10			0xAU
#define GPIO_AFR_AF11			0xBU
#define GPIO_AFR_AF12			0xCU
#define GPIO_AFR_AF13			0xDU
#define GPIO_AFR_AF14			0xEU
#define GPIO_AFR_AF15			0xFU

/*  - T y p e s                                                          */

/*  - C o n s t a n t s                                                  */

/*  - M a c r o s                                                        */

#define GPIOX_SET_(a, b)      GPIO ## a ->BSRR = (1U << b)
#define GPIOX_SET(a)          GPIOX_SET_(a)

#define GPIOX_CLR_(a, b)      GPIO ## a ->BSRR = (1U << (b + 16))
#define GPIOX_CLR(a)          GPIOX_CLR_(a)

#define GPIOX_MODE_(a, b, c)	GPIO ## a->MODER = ((GPIO ## a->MODER & ~(0x3U << (b * 2U))) | (c << (b * 2U)))
#define GPIOX_MODE(a, b)			GPIOX_MODE_(a, b)

#define GPIOX_AFR_(a, b, c)		GPIO ## a->AFR[((b > 7) ? 1 : 0)] = (GPIO ## a->AFR[((b > 7) ? 1 : 0)] & ~(0xFU << (((b > 7) ? (b - 8U): b) * 4U)) | (c << (((b > 7U) ? (b - 8U): b) * 4U)))				
#define GPIOX_AFR(a, b)				GPIOX_AFR_(a, b)

/*  - P u p b l i c   V a r i a b l e s                                  */

/*  - P u b l i c  F u n c t i o n  P r o t o t y p e s                 */



#endif
