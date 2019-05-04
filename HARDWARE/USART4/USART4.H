#ifndef __USART4_H
#define __USART4_H
#include "stdio.h"	
#include "sys.h" 


//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
//#define USART4_MAX_SEND_LEN		200				//最大发送缓存字节数
//#define USART4_RX_EN 			0					//0,不接收;1,接收.
//extern u8  USART4_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART4_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart4_init(u32 bound);
void Uart4_Send(u8 *s,int length);
#endif
