/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        pwm.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                         *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   24.05.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */
 

/*-------------------------- I N C L U D E S ----------------------------*/

#include "pwm.h"
#include "stm32g474xx.h"


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */


/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initialise PWM for controlling the motors
* @param  None
* @retval None
*/
void PWM_Init(void){	
	/*PWM for Motors propulsion*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	TIM4->PSC = 1 - 1;										
	TIM4->ARR= 4800 - 1;								//SystemCoreClock = 48 000 000 / 4 800 = 10 000Hz
	TIM4->CNT=0;
	
	TIM4->CCR1 = 2400;
	TIM4->CCR2 = 2400;
	/* Select PWM mode 1 on OC1  (OC1M = 110), enable preload register on OC1 (OC1PE = 1) */
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;	 
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;	 
	/* Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
	/* Enable output (MOE = 1)*/
  TIM4->BDTR |= TIM_BDTR_MOE;
	/*Enable counter*/
  TIM4->CR1 |= TIM_CR1_CEN; 
	/*Update event*/
  TIM4->EGR |= TIM_EGR_UG; 
}
