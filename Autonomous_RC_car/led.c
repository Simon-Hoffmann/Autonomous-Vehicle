/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        led.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Control of LED at GPIO Pin PE11                                      *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "stm32g474xx.h"
#include "led.h"
#include "delay.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */



void led_Init(void);
void led_On(void);
void led_Off(void);
void led_Blink(uint8_t blink_amount);


/* ----------------------  F U N C T I O N S --------------------------- */

/**
* @brief  Initialise GPIO Pin PE11 as Output
* @param  None
* @retval None
*/
void led_Init(void){
	RCC->AHB2ENR = RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER = (1<<22);
}

/**
* @brief  Turns LED on
* @param  None
* @retval None
*/
void led_On(void){
	GPIOE->BSRR = (1<<11);
}

/**
* @brief  Turns LED off
* @param  None
* @retval None
*/
void led_Off(void){
	GPIOE->BSRR = (1<<27);
}


/**
* @brief  Blinks LED (on and off within 1 second) for specified amount of times
* @param  blink_amount:				Amount of times LED turns on and off
*					blink_duration_ms:	Time between turning LED on and off
* @retval None
*/
void led_Blink(uint8_t blink_amount){
	while(blink_amount > 0){
		GPIOE->BSRR = (1<<11);
		delayms(500);
		GPIOE->BSRR = (1<<27);
		delayms(500);
		blink_amount--;
	}
}

