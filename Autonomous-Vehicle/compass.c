/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        compass.c                                           			  *
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

#include "compass.h"
#include "gpio.h"
#include "delay.h"


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

uint16_t compass_Deg = 0;

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */
void UART3_SendChar (char c);
uint8_t UART3_GetChar (void);

/* ----------------------- F U N C T I O N S  -------------------------- */



/**
* @brief  Initialise Compass GPIO Pins and USART for reading compass bearing
* @param  None
* @retval None
*/
void compass_Init(void){
	/*PIN CONFIG*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;	//Clock enable
	GPIOX_MODE(GPIO_PB10, GPIO_MODE_AF);
	GPIOX_MODE(GPIO_PB11, GPIO_MODE_AF);

	/*USART 3 enable clock*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;

	GPIOX_AFR(GPIO_PB10, GPIO_AFR_AF7);	//TxD	Transmitter
	GPIOX_AFR(GPIO_PB11, GPIO_AFR_AF7);	//RxD Receiver
	USART3->CR1 = 0;				//set all to 0
	USART3->CR1 |= 12;			// Receiver & transmitter enable						8biut daten maybe problem
	
	int div = 48000000/9600;
	
	USART3->BRR = div;			//baudrate 9600
	USART3->CR1 |= 1;				//Usart enable
}

/**
* @brief  Reads current compass bearing over USART
* @param  None
* @retval None
*/
void compass_getDirection(void){
	UART3_SendChar (0x12);
	compass_Deg =  UART3_GetChar();
	int temp = compass_Deg * 100000;
	temp = (temp / 255) * 360;
	compass_Deg = temp / 100000;
}

/**
* @brief  Returns currently read compass bearing
* @param  None
* @retval compass bearing
*/
uint16_t compass_get_compass_Deg(void){
	return compass_Deg;
}

/**
* @brief  Sends a command to compass over USART
* @param  c 	command
* @retval None
*/
static void UART3_SendChar (char c)
{
	USART3->TDR = c;   // LOad the Data
	while (!(USART3->ISR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

/**
* @brief  Reads value sent from compass over USART
* @param  None
* @retval uint8_t	compass bearing 0 - 255
*/
static uint8_t UART3_GetChar (void)
{
	uint8_t Temp;
	
	while (!(USART3->ISR & (1<<5)));  // Wait for RXNE to SET.. This indicates that the data has been Received
	Temp = USART3->RDR;  // Read the data. 
	return Temp;
}
