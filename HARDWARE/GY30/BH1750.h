#ifndef __BH1750_H__
#define __BH1750_H__

 #include "stm32f10x.h"
					
#define uchar unsigned char 
#define uint  unsigned int

#define sda   GPIO_Pin_6    //20
#define scl   GPIO_Pin_7    //21

#define	  SlaveAddress   0x46   //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
                              //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A
															

void Init_BH1750(void);
void conversion(uint temp_data);
void  Single_Write_BH1750(uchar REG_Address);//单个写入数据
uchar Single_Read_BH1750(uchar REG_Address);   //单个读取内部寄存器数据
void  mread(void);         //连续的读取内部寄存器数据

void Delay_5us(void);
void Delay_mms(uint16_t tmp);
void GPIOConfig(void);

void GY30_value(u16 *p);

#endif

