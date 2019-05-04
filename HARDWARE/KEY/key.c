#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "gizwits_product.h"
#include "common.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//按键驱动代码	   
//BY:豪哥哥
//修改日期:2019/1/10
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
extern bool showtime_flag;		
extern uint32_t irLastTimer2 ;
////按键初始化函数
char KEY_VALUE = 0;
bool touch_flag = 0;
u8 touch_time;
char a;
//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

void KEY_Init(void) //IO初始化
{ 
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM5_Int_Init(30-1,7200-1);//定时3ms scan the key
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}

u8 KEY_Scan()                      
{	 	
	
	if(KEY0==0  && KEY1==0 && KEY2==0 && WK_UP==0)
	{

			if(touch_time<5) //5*3ms == 20ms
			{
				KEY_VALUE=0;
			}
			else 
			{
				if(a == 1)KEY_VALUE=1;
				else if(a == 2)KEY_VALUE=2;
				else if(a == 3)KEY_VALUE=3;
				else if(a == 4)KEY_VALUE=4;
				
				if(a >=1 )irLastTimer2 = gizGetTimerCount(); //让每次按下按键后屏保重新计时
			}		

		a = 0;
		touch_flag = 0;//reflash
		touch_time = 0;//reflash
		
		return KEY_VALUE;
	}

		
		if(KEY0 ==1 && KEY1==0 && KEY2==0  && WK_UP==0)
		{
			a = 1;
			touch_flag=1;
	
		}	
		else if(KEY0==0 && KEY1==1 && KEY2==0  && WK_UP==0)
		{
			a = 2;
			touch_flag=1;

		}	
		else if(KEY0==0 && KEY1==0 && KEY2==1  && WK_UP==0)
		{
			a = 3;
			touch_flag=1;

		}	
		else if(KEY0==0 && KEY1==0 && KEY2==0 && WK_UP==1)
		{
			a = 4;
			touch_flag=1;
		}
		
		return 0;
}


