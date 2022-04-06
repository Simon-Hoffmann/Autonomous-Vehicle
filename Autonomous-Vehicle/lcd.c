/**************************************************************************
 *  Autonom Eingebettete Systeme    (AEiSy)                               *  
 *                                                                        *
 **************************************************************************
 *  PROJECT       MC Mobile  																							*
 *  MODULE        led.c                                           			  *
 *  REVISION      1.0                                                     *
 *  AUTHOR        Simon Hoffmann & Aleksei Svatko            							*
 **************************************************************************
 *  PURPOSE:                                                              *
 *   Control of LCD									                                      *
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "lcd.h"
#include "stm32g474xx.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */


/* ----------------------  F U N C T I O N S --------------------------- */

void lcd_Write(uint16_t Data, uint8_t Code);

/**
* @brief  Initialise GPIO Pins:
					PF10, PD1, PD4-5, PD14-15, PE7-10
					for LCD
* @param  None
* @retval None
*/
void lcd_Init(void){
	
	/*PIN CONFIG*/
	RCC->AHB3ENR = RCC_AHB2ENR_GPIODEN;	//Clock enable
	RCC->AHB3ENR = RCC_AHB2ENR_GPIOFEN;
	GPIOF->MODER = (2<<20);						//PF10
	/*Alernate function low register: AFR[0], high: AFR[1] */
	GPIOF->AFR[1] = 0xC00;						//PF10: AF12 -> FMC_A0
	GPIOD->MODER = 0x28000282;				//PD1, PD4-5, PD14-15
	GPIOD->AFR[0] = 0xCC00C0;					//PD1: AF12 -> FMC_D3,	PD4: AF12 -> FMC_NOE,	 PD5: AF12 -> FMC_NWE
	GPIOD->AFR[1] = 0xCC000000;				//PD14: AF12 -> FMC_D0,  PD15: AF12 -> FMC_D1
	/*GPIO Clock enable in led.c*/
	GPIOE->MODER = 0xAA000;						//PE7-10
	GPIOE->AFR[0] = 0xC0000000;				//PE7: AF12 -> FMC_D4
	GPIOE->AFR[1] = 0xCCC;						//PE8: AF12 -> FMC_D5,  PE9: AF12 -> FMC_D6,  PE10: AF12 -> FMC_D7
	
	/*FSMC CONFIG*/
	RCC->AHB3ENR = RCC_AHB3ENR_FMCEN;
	FMC_Bank1_R->BTCR[0] = 0x00201081;
	FMC_Bank1_R->BTCR[1] = 0xCFFF40FF;
	lcd_Write(0x00, 0x40);							//Set Text Home Address 0x000
	lcd_Write(0x1E, 0x41);							//Set Text Area					30
	lcd_Write(0x200, 0x42);							//Set Graphics					0x200
	lcd_Write(0x1E, 0x43);							//Set Graphics Area 		30
	lcd_Write(0x00, 0x81);							//Enable EXOR mode
	lcd_Write(0x00, 0x9C);							//Enable Graphics and Text Display
	lcd_Write(0x00, 0x24);
	lcd_Write(0x20, 0xC0);
}

void lcd_Write(uint16_t Data, uint8_t Code){
	while(COMMAND != 0x2){}
	DATA = (uint8_t) Data;
	while(COMMAND != 0x2){}
	DATA = Data >> 8;
	COMMAND = Code;
}


//uint8_t lcd_Read(){

//}



