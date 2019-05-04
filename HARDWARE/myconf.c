#include "myconf.h"




extern dataPoint_t currentDataPoint;
extern bool auto_flag;
extern char RGBorNORMAL,tem;
extern u16 auto_value,auto_value_last;
extern unsigned char R_G_B[1][3];
extern unsigned char Change_T_stronge[1][3];
u16 link_time = 0;
char link_flag = 0,wifi_gizwit = 0,DHT11_init_flag = 1;
char key = 0;
char pt[4] = {0},ph[4] = {0};//保存温湿度的字符串

u8 music01[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//播放 00001  小朋友记得赶快回来学习哦
u8 music02[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//播放 00002  休息时间到了，赶快休息一下吧   //数组名不对应歌名 注意01与b4对应
u8 music03[6] = {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};	//播放 00003  小朋友请坐端正哦
u8 music04[6] = {0xAA, 0x07, 0x02, 0x00, 0x04, 0xB7};	//播放 00004	  

void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
}


void Gizwits_Init_1MS()
{
	TIM3_Int_Init(9,7199);//1MS系统定时
}

void All_Init()
{
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
/*******************************/
//	uart_init(9600);	 //串口初始化为115200
//	USART2_Init(115200); //距离wifi
	usart3_init(115200);		//初始化串口3 
	uart4_init(9600); //mp3
/*******************************/
	Gizwits_Init_1MS();
	userInit();
    gizwitsInit();
/*******************************/
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
/*******************************/
	SPI2_Init();
	Init_BH1750();
/*******************************/
    IIC_Init();
/*******************************/
	Lcd_Init();

}


u8 Lock = 0;
void Gizwit_Boot()
{
	
	
	
	
		while(link_flag == 0)
		{
					key = KEY_Scan();	//得到键值
					if(key == WKUP_PRES && link_flag == 0)
					{		
						Gizwit_boot_Menu();
						
						printf("--------------------请选择以下连接方式----------------\r\n");
						printf("|                                                    |\r\n");
						printf("|  KEY1_PRES-->Air-link   ||  KEY0_PRES-->SOFT-link  |\r\n");
						printf("|  WKUP_PRES-->link_resrt ||  KEY2_PRES-->NULL       |\r\n");
						printf("|                                                    |\r\n");
						printf("|----------------------------------------------------|\r\n");
						while(1)
						{
							key = KEY_Scan();
							if(key != 0)Gizwit_boot_Menu();		
							switch(key)
							{									
								case WKUP_PRES:	
									gizwitsSetMode(WIFI_RESET_MODE);//WIFI复位
									printf("复位");
									Gui_DrawFont_GBK24(17,10+30,BLACK,RED,(u8*)"-> Wifi Reset");
									break;
								case KEY2_PRES:	//控制LED0翻转
									
									Lock = 1;//用于退出boot
								//	LED0=!LED0;
									break;
								case KEY1_PRES:	
									gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link模式接入
									Gui_DrawFont_GBK24(17,10+30*2,BLACK,RED,(u8*)"->Air-Link");
									printf("Air-link模式接萛\r\n");
									break;
								case KEY0_PRES:	
									LED0=!LED0;
									LED1=!LED1;
									gizwitsSetMode(WIFI_SOFTAP_MODE);
									Gui_DrawFont_GBK24(17,10+30*3,BLACK,RED,(u8*)"->Soft-Reset");
									printf("SOFT-link模式接萛\r\n");				
									break;
							
								default:break;
							}

						    userHandle();
							gizwitsHandle((dataPoint_t *)&currentDataPoint);
							
							if(wifi_gizwit == 1 && Lock == 1)break;//当连接成功后退出配置
						}
						
				}else delay_ms(5); 
					
			userHandle();
			gizwitsHandle((dataPoint_t *)&currentDataPoint);	
		}

}

void Gizwit_boot_Menu()
{				
	Lcd_Clear(GRAY0);  	
	Gui_DrawFont_GBK24(17,10,BLACK,WHITE,(u8*)"Under Configuration");
	Gui_DrawFont_GBK24(17,10+30,BLACK,WHITE,(u8*)"Wifi Reset <WKUP>");
	Gui_DrawFont_GBK24(17,10+30*2,BLACK,WHITE,(u8*)"Air-Link <KEY1>");
	Gui_DrawFont_GBK24(17,10+30*3,BLACK,WHITE,(u8*)"Soft-Reset <KEY0>");
}

void Communi_Interaction()
{
		cmd=zigbee_recevice_cmd("open_red","down_red","posture_good","posture_bad","homework_good","homework_bad");
		if( cmd==1 && night_flag==1)SendOneFrame_sample(&s2500[0][0]);
		else if(cmd == 2)SendOneFrame_sample(&zero[0][0]);
		
//		if( cmd==6 && homework_flag==1)Uart4_Send(music01,6);不用homework功能
//		else if(cmd == 5);
		
		if( cmd==4 && posture_flag==1){Uart4_Send(music03,6);
//		printf("cmd==4 && posture_flag==1");
			}
//		else if(cmd == 3)Uart4_Send(music04,6);
		//------------------------------------------------------//将云端数据写入环形缓存区
		if((link_time > 900 && link_time < 1200))DHT11_Read_Data(&temperature,&humidity);	
		//---------------------------------------------------------//
		if(auto_flag == 1)
		{
		//	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"箭自动调光");
			//printf("-------------------auto_value-----------------\r\n");
			if((link_time%10)<=4){GY30_value(&auto_value);}//printf("-------------------auto_value:%d-----------------\r\n",auto_value);

			if(auto_value != auto_value_last)//防止浪费过多资源
			{
//				printf("-------------------auto_value:%d-----------------\r\n",auto_value);
				if(auto_value<150)
				{
					 if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],3);
					 if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],3);
					 if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],3);
				}
				else if(auto_value<700)
				{
					 if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],2);
					 if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],2);
					 if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],2);
				}
				else if(auto_value<1500)
				{
					 if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],1);
					 if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],1);
					 if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],1);
				}
				else if(auto_value<2500)
				{
					 if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],2);
					 if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],2);
					 if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],2);
				}
				else if(auto_value<3500)
				{
					 if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],3);
					 if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],3);
					 if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],3);
				}
				else if(auto_value>=3500)SendOneFrame_sample(&zero[0][0]);
				 auto_value_last = auto_value;//reflash
			}
		}
		//---------------------------------------------------------//
		userHandle();
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
		//------------------------------------------------------//
}


void Show_Time(u16 x, u16 y)
{
	Gui_DrawFont_Num32(0,y,BLACK,GRAY1,gizwitsProtocol.TimeNTP.hour/10);
	Gui_DrawFont_Num32(0+32,y,BLACK,GRAY1,gizwitsProtocol.TimeNTP.hour%10);
	Gui_DrawFont_Num32(0+32*2,y,BLACK,GRAY1,11);
	Gui_DrawFont_Num32(0+32*3,y,BLACK,GRAY1,gizwitsProtocol.TimeNTP.minute/10);
	Gui_DrawFont_Num32(0+32*4,y,BLACK,GRAY1,gizwitsProtocol.TimeNTP.minute%10);	
}


void Show_TH(char x, char y,u16 fc)
{	
	sprintf(pt,"%d",temperature);
	sprintf(ph,"%d",humidity);

//	printf("pt is %s\n",pt);
//	printf("ph is %s\n",ph);
	Gui_DrawFont_GBK16(x,y,BLACK,fc,(u8 *)"温度");
	Gui_DrawFont_GBK16(x+16*2+2,y,BLACK,fc,(u8 *)(pt));
	Gui_DrawFont_GBK16(x+16*3+2,y,BLACK,fc,(u8 *)"西");
	
	Gui_DrawFont_GBK16(x,y+18,BLACK,fc,(u8 *)"湿度");
	Gui_DrawFont_GBK16(x+16*2+2,y+18,BLACK,fc,(u8 *)(ph));
	Gui_DrawFont_GBK16(x+16*3+2,y+18,BLACK,fc,(u8 *)"%");
}

