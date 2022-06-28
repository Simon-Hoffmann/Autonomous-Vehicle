/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        odometer.c                                           			  *
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


#include "odometer.h"
#include "gpio.h"
#include "event.h"
#include <stdbool.h>


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

static volatile unsigned int motorLeft = 0, motorRight = 0, distanceToDrive = 0, distanceDriven = 0, direction_deg = 0;
static volatile bool checkDistanceRight = false, checkDistanceLeft = false;

#define LEFT 0

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initialise odometer GPIO Pins and EXTI interrupt for reading from Encoder
* @param  None
* @retval None
*/
void odometer_Init(void){
	GPIOX_MODE(GPIO_PC2, GPIO_MODE_INPUT);		//Motor Right: Kanal A EXTI2
	GPIOX_MODE(GPIO_PE15, GPIO_MODE_INPUT); 	//Motor Right: Kanal B
	GPIOX_MODE(GPIO_PE0, GPIO_MODE_INPUT);		//Motor Left: Kanal B
	GPIOX_MODE(GPIO_PE1, GPIO_MODE_INPUT);		//Motor Left: Kanal A EXTI1

	/*--------------------------------------------------------------------------------------------------------------------------------------*/
  RCC->APB2ENR |= 1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC | SYSCFG_EXTICR1_EXTI1_PE;
  EXTI->IMR1 = 0x0006; 
  EXTI->RTSR1 = 0x0006;
	
  
  NVIC_EnableIRQ(EXTI1_IRQn); 
  NVIC_SetPriority(EXTI1_IRQn, 5);
	
	NVIC_EnableIRQ(EXTI2_IRQn); 
  NVIC_SetPriority(EXTI2_IRQn, 5);
}

/**
* @brief  Activates the check distance functionality in EXTI interrupts
*						Wheel diameter:							66mm = 6,6cm
*						Segmentscheibe Inkremente:	120
*
*						Umfang rad:									2 * pi * 3,3cm = 20,734511513692
*						Distanz pro Segment:			  20,734511513692/120	= 0,17278759594743862 cm pro Segment
*						Anzahl Segmente pro cm:			1/0,17278759594743862 = 5,7874524760 Segmente
* @param  None
* @retval None
*/
void odometer_check_distance(int distance_cm){
	distanceToDrive = (distance_cm * 57875) / 10000;
	distanceDriven += (((motorLeft + motorRight) /2) /57875) * 10000;
	motorLeft = 0;
	motorRight = 0;
	checkDistanceRight = true;
	checkDistanceLeft = true;
}

/**
* @brief  Activates the check turn degrees functionality in EXTI interrupts
*						Radabstand:			175mm = 17,5cm
*
*						Umfang:						2 * pi * 	8,75cm = 	54,97787143782138 cm
*						Dreh 90°:					54,97787143782138 / 4 = 13,7444678594553454 cm
*						Segmente für 90°:	13,7444678594553454 / 0,17278759594743862 = 79,545454 segmente
* @param  None
* @retval None
*/
void odometer_check_turn(uint16_t degrees){
	distanceToDrive = (degrees/90) * 80;
	motorLeft = 0;
	motorRight = 0;
	checkDistanceRight = true;
	checkDistanceLeft = true;
}

void updateDirection(int degrees, uint8_t direction){
	if(direction == LEFT){
		direction_deg = ((direction_deg - degrees) + 360) % 360;
	}else{
		direction_deg = (direction_deg + degrees) % 360;
	}
}

int odometer_GetDirection(void){
	return direction_deg;
}

/**
* @brief  Returns the total distance driven in cm
* @param  None
* @retval int distance driven
*/
int getDistanceDriven(void){
	return (distanceDriven + ((((motorLeft + motorRight) /2)  * 10000) /57875));
}

/**
* @brief  EXTI interrupt handler for left motor
* @param  None
* @retval None
*/
void EXTI1_IRQHandler(void)
{
  if ((EXTI->PR1 & 0x0002) != 0)  /* Check line 0 has triggered the IT */
  {
    EXTI->PR1 |= 0x0002; /* Clear the pending bit */
    motorLeft++;
		if(checkDistanceLeft){
			if(motorLeft == distanceToDrive){	
				event_SetEvent(EVT_MOTOR_STOP_LEFT, 0);
				checkDistanceLeft = false;
				nextDriveEvent = true;
			}
		}
  }
}

/**
* @brief  EXTI interrupt handler for right motor
* @param  None
* @retval None
*/
void EXTI2_IRQHandler(void)
{
  if ((EXTI->PR1 & 0x0004) != 0)  /* Check line 0 has triggered the IT */
  {
    EXTI->PR1 |= 0x0004; /* Clear the pending bit */
    motorRight++;
		if(checkDistanceRight){
				if(motorRight == distanceToDrive){
					event_SetEvent(EVT_MOTOR_STOP_RIGHT, 0);
					checkDistanceRight = false;
					nextDriveEvent = true;
			}
		}
  }
}
