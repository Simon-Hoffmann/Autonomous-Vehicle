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
 *   Control of LCD																												*
		*
 *                                                                        *
 **************************************************************************
 *  CHANGE HISTORY:                                                       *
 *   Date  		       Author      						 Description       				    *
 *   29.03.2022  		 S. Hoff & A. Svatko     creation & implementation  	*
 *                                                                        *
 *************************************************************************/
 
/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdio.h>

#include "lcd.h"
#include "gpio.h"
#include "stm32g474xx.h"


/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

static void LCD_ClearScreen(void);
static void LCD_DrawInitialScreen(void);
void LCD_WriteData8(uint8_t Data, uint8_t Command);
void LCD_WriteData16(uint16_t Data, uint8_t Command);
void LCD_WriteCommand(uint8_t Command);

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* @brief  Initialise GPIO Pins:
					PF10, PD1, PD4-5, PD14-15, PE7-10
					for LCD
					FSMC pin setup:
			PF10 							Address bus A0					
			PD14							Data Bus D0							
			PD15							Data Bus D1							
			PD0								Data Bus D2
			PD1								Data Bus D3							
			PE7								Data Bus D4
			PE8								Data Bus D5
			PE9								Data Bus D6
			PE10							Data Bus D7
			PD4 							Output enable /OE				
			PD5 							Write enable /WE				
			PD7 							Chip select /CS0
* @param  None
* @retval None
*/
void LCD_Init(void){
	
	/*PIN CONFIG*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;	//Clock enable
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
	
	
	/*Set Gpio mode to alternate function FSMC*/
	GPIOX_MODE(GPIO_PF10, GPIO_MODE_AF);	//Address Bus A0
	GPIOX_MODE(GPIO_PD14, GPIO_MODE_AF);	//Data Bus D0
	GPIOX_MODE(GPIO_PD15, GPIO_MODE_AF);	//Data Bus D1
	GPIOX_MODE(GPIO_PD0, GPIO_MODE_AF);		//Data Bus D2
	GPIOX_MODE(GPIO_PD1, GPIO_MODE_AF);		//Data Bus D3
	GPIOX_MODE(GPIO_PE7, GPIO_MODE_AF);		//Data Bus D4
	GPIOX_MODE(GPIO_PE8, GPIO_MODE_AF);		//Data Bus D5
	GPIOX_MODE(GPIO_PE9, GPIO_MODE_AF);		//Data Bus D6
	GPIOX_MODE(GPIO_PE10, GPIO_MODE_AF);	//Data Bus D7
	GPIOX_MODE(GPIO_PD4, GPIO_MODE_AF);		//Output Enable /OE
	GPIOX_MODE(GPIO_PD5, GPIO_MODE_AF);		//Write Enable /WE
	GPIOX_MODE(GPIO_PD7, GPIO_MODE_AF);		//Chip Select /CS0
	
	/*Set the alternate functions of GPIO for FSMC for T6963C*/
	GPIOX_AFR(GPIO_PF10, GPIO_AFR_AF12);	//Address Bus A0
	GPIOX_AFR(GPIO_PD14, GPIO_AFR_AF12);	//Data Bus D0
	GPIOX_AFR(GPIO_PD15, GPIO_AFR_AF12);	//Data Bus D1
	GPIOX_AFR(GPIO_PD0, GPIO_AFR_AF12);		//Data Bus D2
	GPIOX_AFR(GPIO_PD1, GPIO_AFR_AF12);		//Data Bus D3
	GPIOX_AFR(GPIO_PE7, GPIO_AFR_AF12);		//Data Bus D4
	GPIOX_AFR(GPIO_PE8, GPIO_AFR_AF12);		//Data Bus D5
	GPIOX_AFR(GPIO_PE9, GPIO_AFR_AF12);		//Data Bus D6
	GPIOX_AFR(GPIO_PE10, GPIO_AFR_AF12);	//Data Bus D7
	GPIOX_AFR(GPIO_PD4, GPIO_AFR_AF12);		//Output Enable /OE
	GPIOX_AFR(GPIO_PD5, GPIO_AFR_AF12);		//Write Enable /WE
	GPIOX_AFR(GPIO_PD7, GPIO_AFR_AF12);		//Chip Select /CS0
	
	/*FSMC Config*/
	RCC->AHB3ENR = RCC_AHB3ENR_FMCEN;
	FMC_Bank1_R->BTCR[0] = 0x00201081;
	FMC_Bank1_R->BTCR[1] = 0xCFFF40FF;
	
	/*LCD Configurations*/
	LCD_WriteData16(LCD_TEXT_HOME_ADDRESS, LCD_CMD_TEXT_HOME_ADDRESS);
	LCD_WriteData16(LCD_TEXT_AREA, LCD_CMD_TEXT_AREA);
	LCD_WriteData16(LCD_GRAPHICS_HOME_ADDRESS, LCD_CMD_GRAPHICS_HOME_ADDRESS);
	LCD_WriteData16(LCD_GRAPHICS_AREA, LCD_CMD_GRAPHICS_AREA);
	LCD_WriteCommand(LCD_CMD_EXOR_MODE);
	LCD_WriteCommand(LCD_CMD_TEXT_ON_GRAPHICS_ON);
	
	LCD_ClearScreen();
	
	LCD_DrawInitialScreen();
}

/**
* @brief  Clears the LCD screen of all set pixels
* @param  None
* @retval None
*/
static void LCD_ClearScreen(void){
	LCD_WriteData16(0x000, LCD_CMD_SET_ADDRESS_POINTER);
	int i =0;
	for(i = 0; i < 480; i++){
		LCD_WriteData16(0x0, LCD_CMD_DATA_WRITE_INCR_ADP);
	}
	LCD_WriteData16(0x200, LCD_CMD_SET_ADDRESS_POINTER);
	for(i = 0; i < 3840; i++){
		LCD_WriteData16(0x0, LCD_CMD_DATA_WRITE_INCR_ADP);
	}
	LCD_WriteData16(0x000, LCD_CMD_SET_ADDRESS_POINTER);
}

/**
* @brief  Fills screen at beginning
* @param  None
* @retval None
*/
static void LCD_DrawInitialScreen(void){

}

/**
* @brief  Sets the Address pointer of LCD
* @param  Address where pointer should be
* @retval None
*/
static void LCD_SetAddressPointer(uint16_t Address){
	LCD_WriteData16(0x000, LCD_CMD_SET_ADDRESS_POINTER);
}

/**
* @brief  Clears specified address range on LCD
* @param  StartAddress:	Beginning
*					EndAddress:		End
* @retval None
*/
static void LCD_CLR_Text_Area(uint16_t StartAddress, uint16_t EndAddress){
	LCD_WriteData16(StartAddress, LCD_CMD_SET_ADDRESS_POINTER);
	uint16_t i =StartAddress;
	for(i = StartAddress; i < EndAddress; i++){
		LCD_WriteData16(0x0, LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}

/**
* @brief  Writes a char character to LCD screen
* @param  Data		Char to be written
*					Command	Command for data handling
* @retval None
*/
static void LCD_WriteData8(uint8_t Data, uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = Data;
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}

/**
* @brief  Writes two char characters to LCD screen
* @param  Data		Chars to be written
*					Command	Command for data handling
* @retval None
*/
static void LCD_WriteData16(uint16_t Data, uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = (uint8_t) Data;
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = (uint8_t) (Data >> 8);
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}

/**
* @brief  Sends command to LCD screen
* @param  Command for data handling
* @retval None
*/
static void LCD_WriteCommand(uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}

void LCD_Update_US_Sensor(uint16_t dist_left, uint16_t dist_middle, uint16_t dist_right){
	LCD_CLR_Text_Area(0, 30);
	LCD_SetAddressPointer(0);
	char distance[3][10] = {0};
	char letter = '\0';
	
	sprintf(distance[0], "%d", dist_left);
	sprintf(distance[1], "%d", dist_middle);
	sprintf(distance[2], "%d", dist_right);
	int i = 0;
	int count;
	for(i = 0; i < 3; i++){
		count = 0;
		do{
			char letter = distance[i][count];
			LCD_WriteData8(letter, LCD_CMD_DATA_WRITE_INCR_ADP);
		}while(distance[i][++count] != '\0');
		LCD_WriteData8('|', LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}


