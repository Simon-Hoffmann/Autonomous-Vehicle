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
#include "gpio.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Blink(uint8_t blink_amount);


/* ----------------------  F U N C T I O N S --------------------------- */

/**
* @brief  Initialise GPIO Pin PE11 as Output
* @param  None
* @retval None
*/
void LED_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOX_MODE(GPIO_PE11, GPIO_MODE_OUTPUT);
}

/**
* @brief  Turns LED on
* @param  None
* @retval None
*/
void LED_On(void){
	GPIOX_SET(GPIO_PE11);
}

/**
* @brief  Turns LED off
* @param  None
* @retval None
*/
void LED_Off(void){
	GPIOX_CLR(GPIO_PE11);
}


/**
* @brief  Blinks LED (on and off within 1 second) for specified amount of times
* @param  blink_amount:				Amount of times LED turns on and off
*					blink_duration_ms:	Time between turning LED on and off
* @retval None
*/
void LED_Blink(uint8_t blink_amount){
	while(blink_amount > 0){
		GPIOX_SET(GPIO_PE11);
		delayms(500);
		GPIOX_CLR(GPIO_PE11);
		delayms(500);
		blink_amount--;
	}
}

