#include "sys.h"
#include "usart4.h"	  
#include "delay.h"
//注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART4_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//__align(8) u8 USART4_TX_BUF[USART4_MAX_SEND_LEN]; 	//发送缓冲,最大USART3_MAX_SEND_LEN字节
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART4_RX_STA=0;       //接收状态标记	  
  
void uart4_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);	//使能UART4时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//使能GPIOC时钟
	//UART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.10
   
  //UART4_RX	  GPIOC.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.11  

  //Uart4 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //UART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode =  USART_Mode_Tx;	//USART_Mode_Rx |//收发模式

  USART_Init(UART4, &USART_InitStructure); //初始化串口4
//  #ifdef
//  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  #endif
  USART_Cmd(UART4, ENABLE);                    //使能串口4 

}

 void Uart4_Send(u8 *s,int length)
{
	u8 count=0;
	for(count=0;count<length;count++){
		
		if(s[count]== 0x00)USART_SendData(UART4, 0x00);
		else USART_SendData(UART4,s[count]);
		
		delay_ms(1);
		
		if(count == length-1){
			USART_SendData(UART4,0x0A);
			delay_ms(1);
			USART_SendData(UART4,0x0D);
		}
	
	}
}



