#ifndef __SPI2_H
#define __SPI2_H
#include "sys.h"

#define SPI2_DMA 1 //0  关闭  1开启   (usart1 dma 冲突)
			  	    													  
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8   SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

#if SPI2_DMA==1
u8 DMA1_Spi2_Init(void);
u8 DMA1_Spi2_RX(u8 *buffer,u32 len);
u8 DMA1_Spi2_TX(u8 *buffer,u32 len);
#endif

#endif

