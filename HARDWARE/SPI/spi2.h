#ifndef __SPI2_H
#define __SPI2_H
#include "sys.h"

#define SPI2_DMA 1 //0  �ر�  1����   (usart1 dma ��ͻ)
			  	    													  
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8   SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�

#if SPI2_DMA==1
u8 DMA1_Spi2_Init(void);
u8 DMA1_Spi2_RX(u8 *buffer,u32 len);
u8 DMA1_Spi2_TX(u8 *buffer,u32 len);
#endif

#endif

