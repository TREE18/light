

#ifndef _WS2812_H_
#define _WS2812_H_
#include "sys.h"

/*******************************通信接口配置***********************************/

//sbit DI = P5^5;						    //数据端口

/*----------------------------灯珠串联个数设置--------------------------------*/  
#define SNUM 32
/*--------------------------------函数声明------------------------------------*/   
void IO_Init(void);						//IO端口初始化
void SendOnePix(unsigned char *ptr);	//发送一个LED的24bit数据
void SendOnePix_tem(unsigned char *ptr,u8 tem);
void ResetDataFlow(void);				//芯片复位脉冲，为发送下一帧做准备
void SendOneFrame(unsigned char *ptr);	//发送一帧数据
void SendSameColor(unsigned char *ptr,unsigned char cnt);  //相同颜色发送若干次
void SendOneFrameFrom(unsigned char i,unsigned char *ptr);//从第i个像素开始发送
														  //一帧数据
void SendOneFrameSince(unsigned char i,unsigned char *ptr);//从第i个像素点的数据
														   //开始发送
void PB0_Init(void);

void SendOneFrame_stronge(unsigned char *ptr,unsigned char *zero,int grand);
void SendOneFrame_sample(unsigned char *ptr);
void SendOneFrame_sample_grade(unsigned char *ptr,u8 tem);
#endif

//-------------------------THE END------------------------*/   
