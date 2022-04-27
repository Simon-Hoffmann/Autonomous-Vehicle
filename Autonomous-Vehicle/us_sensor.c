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

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

static uint16_t us_sensor_middle_cm, us_sensor_left_cm, us_sensor_right_cm;

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

void us_sensor_measure_distance(uint8_t US_sensor_position){
	switch(US_sensor_position){
		case US_SENSOR_LEFT:
			GPIOX_MODE(GPIO_PC7, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC7);
			delayus(10);
			GPIOX_CLR(GPIO_PC7);
			delayus(400);
			GPIOX_MODE(GPIO_PC7, GPIO_MODE_INPUT);
			break;
		case US_SENSOR_MIDDLE:
			GPIOX_MODE(GPIO_PC8, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC8);
			delayus(10);
			GPIOX_CLR(GPIO_PC8);
			delayus(400);
			GPIOX_MODE(GPIO_PC8, GPIO_MODE_INPUT);
			break;
		case US_SENSOR_RIGHT:
			GPIOX_MODE(GPIO_PC9, GPIO_MODE_OUTPUT);
			GPIOX_SET(GPIO_PC9);
			delayus(10);
			GPIOX_CLR(GPIO_PC9);
			delayus(400);
			GPIOX_MODE(GPIO_PC8, GPIO_MODE_INPUT);
			break;
		default:
			break;
	}
}

void us_sensor_setSensor(uint8_t US_sensor_position, uint16_t time){
	time = (time*25)/58;
	switch(US_sensor_position){
		case US_SENSOR_LEFT:
			us_sensor_left_cm = time;
			break;
		case US_SENSOR_MIDDLE:
			us_sensor_middle_cm = time;
			break;
		case US_SENSOR_RIGHT:
			us_sensor_right_cm = time;
			break;
		default:
			break;
	}
}





