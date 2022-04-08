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

#include "isr.h"
#include "stm32g474xx.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */


void ISR_Init(void){
	/*Selecting clock source*/
	//RCC->CR |= RCC_CR_HSEON;						//HSE clock enable
	//while(!(RCC->CR & RCC_CR_HSERDY)); 	//wait for stable clock source
	//RCC->CFGR |= RCC_CFGR_SW_HSE;				//HSE Selected as system clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	/*Enablind timer registers*/	
	TIM2->PSC = 3 - 1;					//Prescaler 3 * Arr 1600000 = 4 800 000
	TIM2->ARR= 1600000 - 1;			//SystemCoreClock = 48 000 000 / 4 800 000 = 10Hz -> every 100ms
	TIM2->CNT=0;
	
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM2->CR1 |= TIM_CR1_CEN;	//Run the Timer
	//RCC_APB1ENR1_TIM2EN;
}

void TIM2_IRQHandler(){
	TIM2->SR &= ~TIM_SR_UIF;
}


