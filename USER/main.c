#include "myconf.h"
#include <stdio.h>
#include <stdlib.h>

/****
2019-3-4:
switch1 about the alarm time 
valuedata1 about app's data to mcu
switch2 about time_show

2019-4-23:
data1 is the value of the alarm time
data2 is the value of screen show
****/
/**
time:2019-5-1
mender:TREE
note:����һЩ�����ϵ��Ż�������volatile
**/

//----------------------------------------------------//
unsigned char zero[1][3]={{0,0,0}};
unsigned char s6100[4][3]={{242,255,236},{206,255,159},{185,255,105},{166,255,69}};
unsigned char Change_T[1][3]={{161,255,72}};	
unsigned char s2500[1][3]={{166,255,69}};
//----------------------------------------------------//									

 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
/********************/
	All_Init();
	bootDisplay();
/********************/	 
	while(DHT11_Init())
	{
		if(link_time > 600)//Ҫ��Щ  ������ܳ�ʱ
		{
			DHT11_init_flag = 0;
			printf("DHT11��ʱ\r\n");
			break;
		}
	}
	
	printf("DHT11_init_flag is %d\n",DHT11_init_flag);
/********************/
/*********************/
//	SendOneFrame_sample(&zero[0][0]);
	SendOneFrame_stronge(&s6100[1][0],&zero[0][0],1);
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-      ����5s�ڵ�� <WK_UP> ��������������ģʽ       -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");
/********************/
	gizwitsGetNTP();//��wifiģ����ϵ������
/********************/

 	while(1)
	{   
						Gizwit_Boot();

						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                 displayOperation();                -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");
						
						displayOperation();
		
					
	}	

 }

