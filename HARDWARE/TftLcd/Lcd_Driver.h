#ifndef _LCD_DRIVER_H
#define _LCD_DRIVER_H
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"
//#include "GUI.h"
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111



#if 0
#define LCD_CTRL_A   	  	GPIOA		//定义TFT数据端口
#define LCD_CTRL_B   	  	GPIOB		//定义TFT数据端口
#define LCD_CTRL_C   	  	GPIOC		//定义TFT数据端口
#endif

#define LCD_CTRL_D   	  	GPIOD	
#define LCD_LED        	GPIO_Pin_8  //MCU_PB15--->>TFT --BL  
#define LCD_CS        	GPIO_Pin_9 //MCU_PC9--->>TFT --CS/CE
#define LCD_RS         	GPIO_Pin_10	//PC8--->>TFT --RS/DC
#define LCD_RST     	GPIO_Pin_11	//PA8--->>TFT --RST
#define LCD_SDA        	GPIO_Pin_12	//PC7 MOSI--->>TFT --SDA/DIN
#define LCD_SCL        	GPIO_Pin_13	//PC6--->>TFT --SCL/SCK



//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

//液晶控制口置1操作语句宏定义
#define	LCD_CS_SET  	LCD_CTRL_D ->BSRR=LCD_CS    
#define	LCD_RS_SET  	LCD_CTRL_D ->BSRR=LCD_RS    
#define	LCD_SDA_SET  	LCD_CTRL_D ->BSRR=LCD_SDA    
#define	LCD_SCL_SET  	LCD_CTRL_D ->BSRR=LCD_SCL    
#define	LCD_RST_SET  	LCD_CTRL_D ->BSRR=LCD_RST    
#define	LCD_LED_SET  	LCD_CTRL_D ->BSRR=LCD_LED   
    
//液晶控制口置0操作语句宏定义
#define	LCD_CS_CLR  	LCD_CTRL_D ->BRR=LCD_CS    
#define	LCD_RS_CLR  	LCD_CTRL_D ->BRR=LCD_RS    
#define	LCD_SDA_CLR  	LCD_CTRL_D ->BRR=LCD_SDA    
#define	LCD_SCL_CLR  	LCD_CTRL_D ->BRR=LCD_SCL    
#define	LCD_RST_CLR  	LCD_CTRL_D ->BRR=LCD_RST    
#define	LCD_LED_CLR  	LCD_CTRL_D ->BRR=LCD_LED 


#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 
#define X_MAX_PIXEL	        160
#define Y_MAX_PIXEL	        128


void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

#endif

