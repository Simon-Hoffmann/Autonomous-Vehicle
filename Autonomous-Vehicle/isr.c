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

static volatile unsigned int countHandlerCalls = 0;

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

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
* @brief  Handler for constant US sensor read
* @param  None
* @retval None
*/
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	countHandlerCalls++;
	event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_LEFT);
	event_SetEvent(EVT_COMPASS_GET_DIRECTION, 0);
	if((countHandlerCalls % 2) == 2){
		event_SetEvent(EVT_LCD_COMPASS_UPDATE, 0);
		event_SetEvent(EVT_LCD_DISTANCE_DRIVEN_UPDATE, 0);
	}else if(countHandlerCalls == 4){
			if(nextDriveEvent){
				event_SetEvent(EVT_AUTODRIVE_DRIVELOGIC, 0);
				nextDriveEvent = false;
			}
			countHandlerCalls = 0;
	}

}


