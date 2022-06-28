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

unsigned char HS_Logo[] = { 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x4F, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x0F, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x00, 
0x00, 0x00, 0x00, 0x1F, 0xFF, 0x1F, 0x80, 0x00, 
0x00, 0x00, 0x40, 0x7F, 0xF0, 0x3F, 0x00, 0x00, 
0x00, 0x00, 0x83, 0xFF, 0xC0, 0x1C, 0x00, 0x00, 
0x00, 0x01, 0x07, 0xFF, 0x00, 0x18, 0x00, 0x00, 
0x00, 0x06, 0x1F, 0xFC, 0x00, 0x10, 0x00, 0x00, 
0x00, 0x04, 0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x03, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x01, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x07, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x40, 0x00, 
0x0F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x00, 
0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x03, 0x00, 0x00, 
0x0F, 0xFF, 0xC0, 0x00, 0x00, 0x08, 0x20, 0x00, 
0x0F, 0xFC, 0x00, 0x00, 0x00, 0x30, 0xE0, 0x00, 
0x0F, 0xFF, 0x3F, 0x06, 0x01, 0x97, 0xC0, 0x00, 
0x0F, 0xFF, 0xFF, 0xF0, 0x0E, 0x1E, 0x80, 0x00, 
0x0F, 0xFF, 0xFF, 0x80, 0xF0, 0xFE, 0x00, 0x00, 
0x07, 0xFF, 0xFE, 0x1F, 0xC7, 0xFC, 0x00, 0x00, 
0x07, 0xFF, 0xFF, 0xFE, 0x3F, 0x1C, 0x00, 0x00, 
0x02, 0xFF, 0xFF, 0xFF, 0xF8, 0x18, 0x00, 0x00, 
0x00, 0x3F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x49, 0xA0, 0x00, 0x00, 0x00, 
0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 
0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

static void LCD_ClearScreen(void);
static void LCD_DrawInitialScreen(void);
void LCD_WriteData8(uint8_t Data, uint8_t Command);
static void LCD_WriteChar(uint8_t Data, uint8_t Command);
void LCD_WriteData16(uint16_t Data, uint8_t Command);
void LCD_WriteCommand(uint8_t Command);
void LCD_SetAddressPointer(uint16_t Address);

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
	LCD_WriteData16(LCD_TEXT_HOME_ADDRESS, LCD_CMD_SET_ADDRESS_POINTER);
	int i =0;
	for(i = 0; i < LCD_TEXT_AREA * 16; i++){
		LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
	}
	LCD_WriteData16(0x200, LCD_CMD_SET_ADDRESS_POINTER);
	for(i = 0; i < LCD_GRAPHICS_AREA * 128; i++){
		LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}
void LCD_DrawBitmap ( uint8_t* bitmap, uint8_t width, uint8_t height, uint8_t x, uint8_t y);
/**
* @brief  Fills screen at beginning
* @param  None
* @retval None
*/
static void LCD_DrawInitialScreen(void){
	LCD_DrawBitmap(HS_Logo, 60, 59, 0, 50);
}

/**
* @brief  Fills screen at beginning
* @param  bitmap		Picture to draw
*					width			Picture pixel width
*					height		Picture pixel height
*					StartX		Starting Position (0-29)
*					StartY		Starting Position (0-127)
* @retval None
*/
void LCD_DrawBitmap ( uint8_t* bitmap, uint8_t width, uint8_t height, uint8_t StartX, uint8_t StartY)
{
	  uint32_t  Address = 0x200 + (StartX + StartY * 30);

		/* Set Address Pointer */
		LCD_SetAddressPointer(Address);

	  for(int j=0;j<height;j++)
	  {
				for(int i=0; i<8;i++)
				{   
					LCD_WriteData8(bitmap[8*j+i], LCD_CMD_DATA_WRITE_INCR_ADP);
				}
				Address += 30; 
				LCD_SetAddressPointer(Address);
	 }
}

/**
* @brief  Sets the Address pointer of LCD
* @param  Address where pointer should be
* @retval None
*/
static void LCD_SetAddressPointer(uint16_t Address){
	LCD_WriteData16(Address, LCD_CMD_SET_ADDRESS_POINTER);
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
* @brief  Writes a 8bit to LCD screen
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
* @brief  Writes a char character to LCD screen
* @param  Data		Char to be written
*					Command	Command for data handling
* @retval None
*/
static void LCD_WriteChar(uint8_t Data, uint8_t Command){
	while((LCD_COMMAND_ADR & 0x3) != 0x3){}
	LCD_DATA_ADDR = Data - 0x20;
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

/**
* @brief  Updates LCD with new US Sensor readings
* @param  dist_left			Left US sensor distance reading
*					dist_middle		Middle US sensor distance reading
*					dist_right		Right US sensor distance reading
* @retval None
*/
void LCD_Update_US_Sensor(uint16_t dist_left, uint16_t dist_middle, uint16_t dist_right){
	LCD_CLR_Text_Area(0, 29);
	LCD_SetAddressPointer(0);
	char distance[3][10] = {0};
	char letter = '\0';
	char position[3] = {'L', 'M', 'R'};
	
	sprintf(distance[0], "%d", dist_left);
	sprintf(distance[1], "%d", dist_middle);
	sprintf(distance[2], "%d", dist_right);
	int i = 0;
	int count;
	for(i = 0; i < 3; i++){
		count = 0;
		LCD_WriteChar(position[i], LCD_CMD_DATA_WRITE_INCR_ADP);
		LCD_WriteChar(':', LCD_CMD_DATA_WRITE_INCR_ADP);
		LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
		do{
			letter = distance[i][count];
			LCD_WriteChar(letter, LCD_CMD_DATA_WRITE_INCR_ADP);
		}while(distance[i][++count] != '\0');
		LCD_WriteChar('c', LCD_CMD_DATA_WRITE_INCR_ADP);
		LCD_WriteChar('m', LCD_CMD_DATA_WRITE_INCR_ADP);
		LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
		LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
	}
}

/**
* @brief  Updates LCD with new Compass reading
* @param  deg		Compass reading
* @retval None
*/
void LCD_Update_Compass(uint16_t deg){
	LCD_CLR_Text_Area(60, 89);
	LCD_SetAddressPointer(60);
	char degrees[10] = {0};
	
	sprintf(degrees, "%d", deg);

	int i = 0;
	do{
		LCD_WriteChar(degrees[i++], LCD_CMD_DATA_WRITE_INCR_ADP);
	}while(degrees[i] != '\0');
	LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
	LCD_WriteChar('D', LCD_CMD_DATA_WRITE_INCR_ADP);
	LCD_WriteChar('e', LCD_CMD_DATA_WRITE_INCR_ADP);
	LCD_WriteChar('g', LCD_CMD_DATA_WRITE_INCR_ADP);
}

/**
* @brief  Updates LCD with Distance driven reading
* @param  distance		odometer reading from left and right
* @retval None
*/
void LCD_Update_Distance_Driven(unsigned int distance){
	LCD_CLR_Text_Area(120, 149);
	LCD_SetAddressPointer(120);
	char distanceDriven[10] = {0};
	
	sprintf(distanceDriven, "%d", distance);

	int i = 0;
	do{
		LCD_WriteChar(distanceDriven[i++], LCD_CMD_DATA_WRITE_INCR_ADP);
	}while(distanceDriven[i] != '\0');
	LCD_WriteChar(' ', LCD_CMD_DATA_WRITE_INCR_ADP);
	LCD_WriteChar('c', LCD_CMD_DATA_WRITE_INCR_ADP);
	LCD_WriteChar('m', LCD_CMD_DATA_WRITE_INCR_ADP);
}

