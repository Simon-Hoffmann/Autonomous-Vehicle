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
#include "event.h"
#include "stm32g474xx.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */


void ISR_US_Sensor_Init(void){
	/*Selecting clock source*/
	//RCC->CR |= RCC_CR_HSEON;						//HSE clock enable
	//while(!(RCC->CR & RCC_CR_HSERDY)); 	//wait for stable clock source
	//RCC->CFGR |= RCC_CFGR_SW_HSE;				//HSE Selected as system clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

	/*Enablind timer registers*/	
	TIM2->PSC = 5 - 1;					//Prescaler 5 * Arr 9 600 000 = 48 000 000
	TIM2->ARR= 4800000 - 1;			//SystemCoreClock = 9 600 000 / 4 800 000 = 2Hz -> every 500ms
	TIM2->CNT=0;
	
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM2->CR1 |= TIM_CR1_CEN;	//Run the Timer
}

static void US_Sensor_Timer(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
	
	/*Enablind timer registers*/	
	TIM6->PSC = 5 - 1;					//Prescaler 5 * Arr 9 600 000 = 48 000 000
	TIM6->ARR= 4800000 - 1;			//SystemCoreClock = 9 600 000 / 4 800 000 = 2Hz -> every 500ms
	TIM6->CNT=0;
	
	TIM6->CR1 |= TIM_CR1_CEN;	//Run the Timer
}

void US_Sensor_Interrupt(uint8_t pin){
	RCC->APB2ENR |= 1;										//clock enable sysconfig
	SYSCFG->EXTICR[1] = ((SYSCFG->EXTICR[1] & ~(2 << 12)) | (2 << 12));	//EXTI channel to PF7
	SYSCFG->EXTICR[2] = ((SYSCFG->EXTICR[2] & ~0x22) | 0x22);						//EXTI channel to PF8 and PF9
	EXTI->IMR1 = ((EXTI->IMR1 & ~(0x7 << 7)) | (0x7 << 7));							//EXTI enable lines 7-9
	
	
	EXTI->RTSR1 = ((EXTI->RTSR1  & ~(0x7 << 7)) | (0x7 << 7));			//rising trigger 
	
	
	NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	

	
	
}

void EXTI9_5_IRQHandler(void){
	switch((EXTI->PR1 >> 7) & 0x7){ //welcher pin :D
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
	EXTI->PR1 &= ~(EXTI_PR1_PIF7 & EXTI_PR1_PIF8 & EXTI_PR1_PIF9); //flags zurueck setzen
	
	EXTI->FTSR1 = ((EXTI->FTSR1  & ~(0x7 << 7)) | (0x7 << 7));			//falling trigger
}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	event_SetEvent(EVT_US_SENSOR_READ, 0);
}


