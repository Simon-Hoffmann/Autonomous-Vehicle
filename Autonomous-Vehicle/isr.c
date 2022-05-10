/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        isr.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Handles all Interrupt service routines                               *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   05.03.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/


/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdbool.h>

#include "isr.h"
#include "event.h"
#include "stm32g474xx.h"
#include "us_sensor.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

static bool initialInterrupt = true;

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initialises/Configures Ultrasound sensor timers and interrupts:
*						-GPIO Interrupt for signal indicating distance
*						-Timer 6 for time measurement of signal indicating distance
*						-Timer 2 Interrupt for constant sensor reading at set intervals 
* @param  None
* @retval None
*/
void ISR_US_Sensor_Init(void){
	/*-----------US sensor GPIO Interrupt-----------*/
	RCC->APB2ENR |= 1;																									//clock enable sysconfig
	SYSCFG->EXTICR[1] = ((SYSCFG->EXTICR[1] & ~(2 << 12)) | (2 << 12));	//EXTI channel to PF7
	SYSCFG->EXTICR[2] = ((SYSCFG->EXTICR[2] & ~0x22) | 0x22);						//EXTI channel to PF8 and PF9
	EXTI->IMR1 = ((EXTI->IMR1 & ~(0x7 << 7)) | (0x7 << 7));							//EXTI enable lines 7-9
	NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
	
	/*--------US sensor signal timer for distance calculation----------*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
	TIM6->PSC = 48 - 1;										//Prescaler 48 000 000 / 48 = 1 000 000 Hz	-> 1us
	TIM6->ARR = 65000 - 1;									
	TIM6->CNT = 0;
	TIM6->CR1 |= TIM_CR1_CEN;
	TIM6->EGR = 1;												//Event generation to update Prescaler to set value
	
	/*------Initialization of Timer interrupt that initiates US sensor read--------*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	TIM2->PSC = 5 - 1;										//Prescaler 5 * Arr 9 600 000 = 48 000 000
	TIM2->ARR= 4800000 - 1;								//SystemCoreClock = 9 600 000 / 4 800 000 = 2Hz -> every 500ms
	TIM2->CNT=0;
	TIM2->DIER = TIM_DIER_UIE;
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1 |= TIM_CR1_CEN;							//Start the Timer
}

/**
* @brief  Starts relevant timers for receiving the US sensor signal 
* @param  None
* @retval None
*/
void ISR_US_sensor_startInterrupt(void){
	EXTI->RTSR1 = ((EXTI->RTSR1  & ~(0x7 << 7)) | (0x7 << 7));			//rising trigger on GPIO interrupt
	EXTI->PR1 |= (EXTI_PR1_PIF7 | EXTI_PR1_PIF8 | EXTI_PR1_PIF9);
	//maybe while loop as well
	NVIC_EnableIRQ(EXTI9_5_IRQn);																		
}

/**
* @brief  Handler for capturing time of signal
* @param  None
* @retval None
*/
void EXTI9_5_IRQHandler(void){
	if(initialInterrupt){
		
		/*Set timer for signal length of US sensor*/
		TIM6->CNT = 0;																									//Run the Timer
		EXTI->RTSR1 = 0x0;																							//disable interrupt on rising trigger
		EXTI->FTSR1 = ((EXTI->FTSR1  & ~(0x7 << 7)) | (0x7 << 7));			//interrupt on falling trigger
		initialInterrupt = false;
		while(NVIC_GetPendingIRQ(EXTI9_5_IRQn)){
			EXTI->PR1 |= (EXTI_PR1_PIF7 | EXTI_PR1_PIF8 | EXTI_PR1_PIF9);	//reset interrupt flag					possibly put this before while, do the same at bottom
			NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
		}
	} else {
		int time_us = TIM6->CNT;
		NVIC_DisableIRQ(EXTI9_5_IRQn);
		switch((EXTI->PR1 >> 7) & 0x7){ 
			case US_SENSOR_LEFT:
				event_SetEvent(EVT_US_SENSOR_SET_LEFT_DIST, time_us);
				event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_MIDDLE);
				break;
			case US_SENSOR_MIDDLE:
				event_SetEvent(EVT_US_SENSOR_SET_MIDDLE_DIST, time_us);
				event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_RIGHT);
				break;
			case US_SENSOR_RIGHT:
				event_SetEvent(EVT_US_SENSOR_SET_RIGHT_DIST, time_us);
			//-------------------------------------------------------update lcd
				event_SetEvent(EVT_LCD_DISTANCE_UPDATE, 0);
				break;
			default:
				break;
		}
		/*Disable and reset timer*/
		EXTI->FTSR1 = 0x0;																			//disable interrupt on falling trigger
		while(NVIC_GetPendingIRQ(EXTI9_5_IRQn)){
			EXTI->PR1 |= (EXTI_PR1_PIF7 | EXTI_PR1_PIF8 | EXTI_PR1_PIF9);	//reset interrupt flag
			NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
		}
		initialInterrupt = true;
	}
}

/**
* @brief  Handler for constant US sensor read
* @param  None
* @retval None
*/
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	//event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_LEFT);
}


