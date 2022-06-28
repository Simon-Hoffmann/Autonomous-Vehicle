/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        motor.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                         *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   10.05.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */
 

/*-------------------------- I N C L U D E S ----------------------------*/


#include "stm32g474xx.h"
#include "gpio.h"
#include "motor.h"
#include "pwm.h"
#include "delay.h"


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initializes GPIOs for motors
* @param  None
* @retval None
*/
void motor_Init(void){
	GPIOX_MODE(GPIO_PD8, GPIO_MODE_OUTPUT);		//Right C
	GPIOX_MODE(GPIO_PD9, GPIO_MODE_OUTPUT);		//Right D
	GPIOX_MODE(GPIO_PD10, GPIO_MODE_OUTPUT);	//Left C
	GPIOX_MODE(GPIO_PD11, GPIO_MODE_OUTPUT);	//Left D
	GPIOX_MODE(GPIO_PD12, GPIO_MODE_AF);			//Right PWM
	GPIOX_MODE(GPIO_PD13, GPIO_MODE_AF);			//Left PWM
	
	GPIOX_AFR(GPIO_PD12, GPIO_AFR_AF2);				//AF -> TIM4 Channel 1
	GPIOX_AFR(GPIO_PD13, GPIO_AFR_AF2);				//AF -> TIM4 Channel 2
	
	GPIOX_CLR(GPIO_PD8);
	GPIOX_CLR(GPIO_PD9);
	GPIOX_CLR(GPIO_PD10);
	GPIOX_CLR(GPIO_PD11);
	PWM_Init();
}


/**
* @brief  Sets GPIO pins for motor drive forward
* @param  None
* @retval None
*/
void motor_drive_forward(void){
	GPIOX_SET(GPIO_PD8);
	GPIOX_CLR(GPIO_PD9);
	GPIOX_SET(GPIO_PD10);
	GPIOX_CLR(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for motor drive backward
* @param  None
* @retval None
*/
void motor_drive_backward(void){
	GPIOX_CLR(GPIO_PD8);
	GPIOX_SET(GPIO_PD9);
	GPIOX_CLR(GPIO_PD10);
	GPIOX_SET(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for motor turn left
* @param  None
* @retval None
*/
void motor_turn_left(void){
	GPIOX_SET(GPIO_PD8);
	GPIOX_CLR(GPIO_PD9);
	GPIOX_CLR(GPIO_PD10);
	GPIOX_SET(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for motor turn right
* @param  None
* @retval None
*/
void motor_turn_right(void){
	GPIOX_CLR(GPIO_PD8);
	GPIOX_SET(GPIO_PD9);
	GPIOX_SET(GPIO_PD10);
	GPIOX_CLR(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for motors stop
* @param  None
* @retval None
*/
void motor_stop_all(void){
	GPIOX_CLR(GPIO_PD8);
	GPIOX_CLR(GPIO_PD9);
	GPIOX_CLR(GPIO_PD10);
	GPIOX_CLR(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for left motor stop
* @param  None
* @retval None
*/
void motor_stop_left(void){
	GPIOX_CLR(GPIO_PD10);
	GPIOX_CLR(GPIO_PD11);
}

/**
* @brief  Sets GPIO pins for right motor stop
* @param  None
* @retval None
*/
void motor_stop_right(void){
	GPIOX_CLR(GPIO_PD8);
	GPIOX_CLR(GPIO_PD9);
}


