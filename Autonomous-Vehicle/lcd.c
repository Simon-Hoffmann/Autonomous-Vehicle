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

#include "lcd.h"
#include "gpio.h"
#include "stm32g474xx.h"

/* ----------------- G L O B A L    V A R I A B L E S ------------------ */

/* ----------------------  F U N C T I O N S --------------------------- */

static void LCD_WriteData8(uint8_t Data, uint8_t Command);
static void LCD_WriteData16(uint16_t Data, uint8_t Command);
static void LCD_WriteCommand(uint8_t Command);
static void LCD_ClearScreen(void);
void LCD_Write_Line(char* Text);

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
	GPIOF->MODER = (2<<20);						//PF10
	/*Alernate function low register: AFR[0], high: AFR[1] */
	GPIOF->AFR[1] = 0xC00;						//PF10: AF12 -> FMC_A0
	
	GPIOD->MODER = 0xA0008A0A;				//PD0, PD1, PD4, PD5, PD7, PD14-15
	GPIOD->AFR[0] = 0xC0CC00CC;					//PD0: AF12-> FMC_D2, PD1: AF12 -> FMC_D3,	PD4: AF12 -> FMC_NOE,	 PD5: AF12 -> FMC_NWE
	GPIOD->AFR[1] = 0xCC000000;				//PD14: AF12 -> FMC_D0,  PD15: AF12 -> FMC_D1
	/*GPIO Clock enable in led.c*/
	GPIOE->MODER |= 0x2A8000;						//PE7-10
	GPIOE->AFR[0] = 0xC0000000;				//PE7: AF12 -> FMC_D4
	GPIOE->AFR[1] = 0xCCC;						//PE8: AF12 -> FMC_D5,  PE9: AF12 -> FMC_D6,  PE10: AF12 -> FMC_D7
	
	/*FSMC CONFIG*/
	RCC->AHB3ENR = RCC_AHB3ENR_FMCEN;
	FMC_Bank1_R->BTCR[0] = 0x00201081;
	FMC_Bank1_R->BTCR[1] = 0xCFFF40FF;
	
	LCD_WriteData16(LCD_TEXT_HOME_ADDRESS, LCD_CMD_TEXT_HOME_ADDRESS);
	LCD_WriteData16(LCD_TEXT_AREA, LCD_CMD_TEXT_AREA);
	LCD_WriteData16(LCD_GRAPHICS_HOME_ADDRESS, LCD_CMD_GRAPHICS_HOME_ADDRESS);
	LCD_WriteData16(LCD_GRAPHICS_AREA, LCD_CMD_GRAPHICS_AREA);
	LCD_WriteCommand(LCD_CMD_EXOR_MODE);
	LCD_WriteCommand(LCD_CMD_TEXT_ON_GRAPHICS_ON);
	
	LCD_ClearScreen();
}


void LCD_InitTest(void){
	
	/*PIN CONFIG*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;;	//Clock enable
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
	LCD_Write_Line("Start Text");
}

void LCD_Write_Line(char* Text){
	LCD_WriteData16(LCD_TEXT_HOME_ADDRESS, LCD_CMD_SET_ADDRESS_POINTER);
	
	uint8_t i = 0;
	while(Text[i] != 0){
		LCD_WriteData8(Text[i++], LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}

static void LCD_ClearScreen(void){
	LCD_WriteData16(LCD_TEXT_HOME_ADDRESS, LCD_CMD_SET_ADDRESS_POINTER);
	int i =0;
	for(i = 0; i < LCD_TEXT_AREA * 16; i++){
		LCD_WriteData16(0x0, LCD_CMD_DATA_WRITE_INCR_ADP);
	}
	LCD_WriteData16(0x200, LCD_CMD_SET_ADDRESS_POINTER);
	for(i = 0; i < LCD_GRAPHICS_AREA * 128; i++){
		LCD_WriteData16(0x0, LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}

static void LCD_WriteData8(uint8_t Data, uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = Data;
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}

static void LCD_WriteData16(uint16_t Data, uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = (uint8_t) Data;
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = (uint8_t) (Data >> 8);
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}

static void LCD_WriteCommand(uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_COMMAND_ADR = Command;
}




