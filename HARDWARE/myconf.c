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
char pt[4] = {0},ph[4] = {0};//������ʪ�ȵ��ַ���

u8 music01[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//���� 00001  С���ѼǵøϿ����ѧϰŶ
u8 music02[6] = {0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//���� 00002  ��Ϣʱ�䵽�ˣ��Ͽ���Ϣһ�°�   //����������Ӧ���� ע��01��b4��Ӧ
u8 music03[6] = {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};	//���� 00003  С������������Ŷ
u8 music04[6] = {0xAA, 0x07, 0x02, 0x00, 0x04, 0xB7};	//���� 00004	  

void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
}


void Gizwits_Init_1MS()
{
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
}

void All_Init()
{
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
/*******************************/
//	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
//	USART2_Init(115200); //����wifi
	usart3_init(115200);		//��ʼ������3 
	uart4_init(9600); //mp3
/*******************************/
	Gizwits_Init_1MS();
	userInit();
    gizwitsInit();
/*******************************/
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
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
					key = KEY_Scan();	//�õ���ֵ
					if(key == WKUP_PRES && link_flag == 0)
					{		
						Gizwit_boot_Menu();
						
						printf("--------------------��ѡ���������ӷ�ʽ----------------\r\n");
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
									gizwitsSetMode(WIFI_RESET_MODE);//WIFI��λ
									printf("��λ");
									Gui_DrawFont_GBK24(17,10+30,BLACK,RED,(u8*)"-> Wifi Reset");
									break;
								case KEY2_PRES:	//����LED0��ת
									
									Lock = 1;//�����˳�boot
								//	LED0=!LED0;
									break;
								case KEY1_PRES:	
									gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-linkģʽ����
									Gui_DrawFont_GBK24(17,10+30*2,BLACK,RED,(u8*)"->Air-Link");
									printf("Air-linkģʽ���\\r\n");
									break;
								case KEY0_PRES:	
									LED0=!LED0;
									LED1=!LED1;
									gizwitsSetMode(WIFI_SOFTAP_MODE);
									Gui_DrawFont_GBK24(17,10+30*3,BLACK,RED,(u8*)"->Soft-Reset");
									printf("SOFT-linkģʽ���\\r\n");				
									break;
							
								default:break;
							}

						    userHandle();
							gizwitsHandle((dataPoint_t *)&currentDataPoint);
							
							if(wifi_gizwit == 1 && Lock == 1)break;//�����ӳɹ����˳�����
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
		
//		if( cmd==6 && homework_flag==1)Uart4_Send(music01,6);����homework����
//		else if(cmd == 5);
		
		if( cmd==4 && posture_flag==1){Uart4_Send(music03,6);
//		printf("cmd==4 && posture_flag==1");
			}
//		else if(cmd == 3)Uart4_Send(music04,6);
		//------------------------------------------------------//���ƶ�����д�뻷�λ�����
		if((link_time > 900 && link_time < 1200))DHT11_Read_Data(&temperature,&humidity);	
		//---------------------------------------------------------//
		if(auto_flag == 1)
		{
		//	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"���Զ�����");
			//printf("-------------------auto_value-----------------\r\n");
			if((link_time%10)<=4){GY30_value(&auto_value);}//printf("-------------------auto_value:%d-----------------\r\n",auto_value);

			if(auto_value != auto_value_last)//��ֹ�˷ѹ�����Դ
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
	Gui_DrawFont_GBK16(x,y,BLACK,fc,(u8 *)"�¶�");
	Gui_DrawFont_GBK16(x+16*2+2,y,BLACK,fc,(u8 *)(pt));
	Gui_DrawFont_GBK16(x+16*3+2,y,BLACK,fc,(u8 *)"��");
	
	Gui_DrawFont_GBK16(x,y+18,BLACK,fc,(u8 *)"ʪ��");
	Gui_DrawFont_GBK16(x+16*2+2,y+18,BLACK,fc,(u8 *)(ph));
	Gui_DrawFont_GBK16(x+16*3+2,y+18,BLACK,fc,(u8 *)"%");
}

