/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        us_sensor.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *                                  *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   26.04.2022  		 S. Hoff & A. Svatko     creation              				*
 *                                                                        *
 *************************************************************************/


/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "us_sensor.h"
#include "gpio.h"
#include "stm32g474xx.h"
#include "delay.h"
#include "isr.h"
#include "event.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

static uint16_t us_sensor_middle_cm, us_sensor_left_cm, us_sensor_right_cm;

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initialise US sensor GPIO Pins
* @param  None
* @retval None
*/
void US_sensor_gpio_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	//Clock enable
}


/**
* @brief  Handles the measuring of distance with the US sensor
* @param  US_sensor_position: left, middle or right sensor	
* @retval None
*/
void us_sensor_measure_distance(uint8_t US_sensor_position){
	int time;
	switch(US_sensor_position){
		case US_SENSOR_LEFT:
			GPIOX_MODE(GPIO_PC7, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC7);
			delayus(15);
			GPIOX_CLR(GPIO_PC7);
			delayus(400);
			GPIOX_MODE(GPIO_PC7, GPIO_MODE_INPUT);			
			while(((GPIOC->IDR) & 1<<7) == 0){}
			TIM6->CNT = 0;
			delayus(80);
			while((GPIOC->IDR & 1<<7) == (1<<7)){}
			time = TIM6->CNT;
			us_sensor_setSensor(US_SENSOR_LEFT, time);
			event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_MIDDLE);
			break;
		case US_SENSOR_MIDDLE:
			GPIOX_MODE(GPIO_PC8, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC8);
			delayus(15);
			GPIOX_CLR(GPIO_PC8);
			delayus(400);
			GPIOX_MODE(GPIO_PC8, GPIO_MODE_INPUT);
			while(((GPIOC->IDR) & 1<<8) == 0){}
			TIM6->CNT = 0;
			delayus(80);
			while((GPIOC->IDR & 1<<8) == (1<<8)){}
			time = TIM6->CNT;
			us_sensor_setSensor(US_SENSOR_MIDDLE, time);
			event_SetEvent(EVT_US_SENSOR_READ, US_SENSOR_RIGHT);
			break;
		case US_SENSOR_RIGHT:
			GPIOX_MODE(GPIO_PC9, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC9);
			delayus(15);
			GPIOX_CLR(GPIO_PC9);
			delayus(400);
			GPIOX_MODE(GPIO_PC9, GPIO_MODE_INPUT);
			while(((GPIOC->IDR) & 1<<9) == 0){}
			TIM6->CNT = 0;
			delayus(80);
			while((GPIOC->IDR & 1<<9) == (1<<9)){}
			time = TIM6->CNT;
			us_sensor_setSensor(US_SENSOR_RIGHT, time);
			event_SetEvent(EVT_LCD_DISTANCE_UPDATE,0);
			break;
		default:
			break;
	}
}

/**
* @brief  Sets the currently measured distance of a sensor
* @param  US_sensor_position: left, middle or right sensor	
*					time_50us:					time x 50us
* @retval None
*/
void us_sensor_setSensor(uint8_t US_sensor_position, uint16_t time_us){
	uint16_t dist = time_us/58;
	switch(US_sensor_position){
		case US_SENSOR_LEFT:
			us_sensor_left_cm = dist;
			break;
		case US_SENSOR_MIDDLE:
			us_sensor_middle_cm = dist;
			break;
		case US_SENSOR_RIGHT:
			us_sensor_right_cm = dist;
			break;
		default:
			break;
	}
}

/**
* @brief  Returns Left US sensor distance reading
* @param  None
* @retval US sensor reading
*/
uint16_t us_sensor_GetDistance_left(void){
	return us_sensor_left_cm;
}

/**
* @brief  Returns Middle US sensor distance reading
* @param  None
* @retval US sensor reading
*/
uint16_t us_sensor_GetDistance_middle(void){
	return us_sensor_middle_cm;
}

/**
* @brief  Returns Right US sensor distance reading
* @param  None
* @retval US sensor reading
*/
uint16_t us_sensor_GetDistance_right(void){
	return us_sensor_right_cm;
}



