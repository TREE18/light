#include "myconf.h"

u8 keyFun=0;        //װ�ز˵�����
void (*keyFunPt)(); //ָ�뺯��
//-----------------------------------------------------------//
u8 keyFlag=0;				//���ؼ�ֵ
//-----------------------------------------------------------//
char time_c=0,time_s=0,flag=0,homework_flag=0,posture_flag=0,night_flag=0,cmd=0;
char other1_flag = 0,other2_flag = 1;
char otherpos1 = 0,otherpos2 = 0;
//-----------------------------------------------------------//
char Led_OnOff_Change_flag=0,valueLed_T_value_last=0,valueLed_S_value_last=0,night_red_last=0,valueLed_T_tem_last=0,
	 valueLed_posture_last=0,valueLed_homework_last,Posture_first1_last = 80,Posture_first2_last = 80,Posture_first3_last = 80;//�ƶ��´���־λ
char go_gui_flag=0,RGBorNORMAL=0;//ȥ�����������־
bool R_flag=0,G_flag=0,B_flag=0,auto_flag=0,distance_flag=0,showtime_flag=0;
unsigned char R_G_B[1][3]={0},Change_T_stronge[1][3]={{161,255,72}};
//-----------------------------------------------------------//
int WIFI_Sign=33,Electricity_Sign=4,Flashlight_Sign=1;
u8 temperature=0,humidity=0;
u16 auto_value=0,auto_value_last=0;

extern bool scree_close;

char tem = 0;
void Fun_light(void)
{
	char k=0,tem2=1;// tem ��¼ɫ��ֵ   tem2 ���ڵȼ�
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                       ��ǿ ɫ��                    -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");
	
	Lcd_Clear(GRAY0); //���� 
	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	
	valueLed_T_value_last = currentDataPoint.valueLed_T;
	valueLed_S_value_last = currentDataPoint.valueLed_S;
	valueLed_T_tem_last = currentDataPoint.valueLed_T_consequent;
	while(1)
	{
	
		if(go_gui_flag && go_gui_flag != 1)break;//app������gui
	/**------------------------------------------------------------------------**///��������
		keyFlag = KEY_Scan();	
		if(keyFlag == KEY2_PRES||keyFlag == WKUP_PRES)break;
		if((keyFlag == KEY0_PRES)||(valueLed_T_value_last!=currentDataPoint.valueLed_T)||(valueLed_T_tem_last != currentDataPoint.valueLed_T_consequent)
			||(R_flag == 1||G_flag == 1||B_flag == 1))
		{	
			printf("keyFlag == KEY0_PRES");
			Gui_DrawFont_GBK24(100,100,BLACK,RED,(u8*)"ɫ��");
			Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
			
			if(keyFlag == KEY0_PRES)//������ɫ
			{
				tem = k;//��¼ɫ��,�����Ȼ��õ�
				SendOneFrame_sample(&s6100[k++][0]);//k�ڴ˴���������4  //0 1 2 3 �պ�4��
				if(k == 4)k = 0;
			}
			
			if(valueLed_T_value_last!=currentDataPoint.valueLed_T)//�ļ�����
			{
				tem=currentDataPoint.valueLed_T;//ȡֵ��0-4�� 5����
				SendOneFrame_sample(&s6100[tem-1][0]);
				RGBorNORMAL = 0;
				valueLed_T_value_last=currentDataPoint.valueLed_T;//reflash currentDataPoint.valueLed_T
			}
			/**------------------------------------------------------------------------**///�������RGB
			if(R_flag == 1||G_flag == 1||B_flag == 1)//����RGB
			{
				R_flag=B_flag=G_flag=0;//reflash
				R_G_B[0][0]=currentDataPoint.valueG_value;
				R_G_B[0][1]=currentDataPoint.valueR_value;
				R_G_B[0][2]=currentDataPoint.valueB_value;
				SendOneFrame_sample(&R_G_B[0][0]);
				
				RGBorNORMAL=1;
			}	
			/**------------------------------------------------------------------------**///44������ɫ��
			if(valueLed_T_tem_last != currentDataPoint.valueLed_T_consequent)
			{
				SendOneFrame_sample_grade(&Change_T[0][0],currentDataPoint.valueLed_T_consequent);
				RGBorNORMAL=2;
				valueLed_T_tem_last = currentDataPoint.valueLed_T_consequent;//reflash
			}
		}
        /**------------------------------------------------------------------------**///���ڹ�ǿ
		if(keyFlag == KEY1_PRES || valueLed_S_value_last!=currentDataPoint.valueLed_S)
		{
			Gui_DrawFont_GBK24(10,100,BLACK,RED,(u8*)"����");
			Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
			
			if(valueLed_S_value_last!=currentDataPoint.valueLed_S)//Ŀǰ�ڹ�ǿǰ���»�ɫ��  �ỻ�ָ�ȫ��led��
			{
				if(currentDataPoint.valueLed_S==0)SendOneFrame_sample(&zero[0][0]);
				else if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem-1][0],&zero[0][0],currentDataPoint.valueLed_S);
				else if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],currentDataPoint.valueLed_S);
				else if(RGBorNORMAL == 2)SendOneFrame_stronge(&Change_T_stronge[0][0],&zero[0][0],currentDataPoint.valueLed_S);
				valueLed_S_value_last = currentDataPoint.valueLed_S; //reflash
			}
				
			if(keyFlag == KEY1_PRES)
			{
				if(RGBorNORMAL == 0)SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],tem2++); //[tem][0]
				else if(RGBorNORMAL == 1)SendOneFrame_stronge(&R_G_B[0][0],&zero[0][0],tem2++);
				else SendOneFrame_stronge(&Change_T[0][0],&zero[0][0],tem2++);
				
				if(tem2 == 5)tem2 = 0;//�������ĵȼ�//ԭ��Ϊ4 ����Ϊ5Ϊ���˸�ȫ��
			}																											
		}
		/**------------------------------------------------------------------------**///������������
		if(auto_flag == 1)
		{
			
			Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"���Զ�������");
			
			#if 0
			//printf("-------------------auto_value-----------------\r\n");
			if((link_time%10)==0){GY30_value(&auto_value);printf("-------------------auto_value:%d-----------------\r\n",auto_value);}
			if(auto_value != auto_value_last)//��ֹ�˷ѹ�����Դ
			{
				printf("-------------------auto_value:%d-----------------\r\n",auto_value);
				if(auto_value<500)
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
				 auto_value_last=auto_value;//reflash
			}
			#endif
		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}

//**************************************************************************************************************//
void Fun_homework(void)
{	
	Lcd_Clear(GRAY0); //���� 
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                        ��ͥ��ҵ                    -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");

	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"����ҵ�ػ�");
	Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  ��������");
	Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ��");
	Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ����");
	Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ��");
	
	if(homework_flag==1)Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"����ҵ�ػ� ��");
	if(posture_flag==1)Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  �������� ��");
	if(night_flag==1)Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ�� ��");
	if(other1_flag==1)Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ���� ��");
	if(other2_flag==1)Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ�� ��");

	while(1)
	{
		if(go_gui_flag && go_gui_flag != 2)break;

		keyFlag = KEY_Scan();
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES || valueLed_homework_last!=currentDataPoint.valueHomework_OnOff)
		{	
			homework_flag++;
			
			if(homework_flag == 2 || homework_flag == 0)
			{
//				zigbee_send_cmd("homework_off","0",0);
				printf("-----------------homework_off--------------\r\n");
				homework_flag=0;
				Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"����ҵ�ػ�   ");
			}
			
			if(homework_flag == 1)
			{
				//open_ap();//����ȥ����ע��
//				zigbee_send_cmd("homework_on","0",0);
				printf("-----------------homework_on--------------\r\n");
				Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"����ҵ�ػ� ��");	
			}
			
			valueLed_homework_last=currentDataPoint.valueHomework_OnOff;//reflash
		}
		//-----------------------------------------------------------------------//	�ı����
//		if(distance_flag == 1)	
//		{
//			distance_flag=0;//reflash
//			zigbee_send_number("dist:",currentDataPoint.valuehomework_distance,"0",0);
//		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}
//**********************************************************************************************************************//

void Fun_posture(void)
{
	Lcd_Clear(GRAY0); //���� 
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                         ����                       -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");
	
	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ�");
	Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"����������");
	Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ��");
	Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ����");
	Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ��");
	
	if(homework_flag==1)Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ� ��");
	if(posture_flag==1)Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"���������� ��");
	if(night_flag==1)Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ�� ��");
	if(other1_flag==1)Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ���� ��");
	if(other2_flag==1)Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ�� ��");

	while(1)
	{
		if(go_gui_flag && go_gui_flag != 3)break;

		keyFlag = KEY_Scan();
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES || keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES || valueLed_posture_last!=currentDataPoint.valuePosture_OnOff)
		{
			posture_flag++;
			
			if(posture_flag==2 || posture_flag==0)
			{	
				zigbee_send_cmd("posture_off","0",0);
				posture_flag=0;
				Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"����������    " );
			}
			
			if(posture_flag == 1)
			{	
				if(!zigbee_send_cmd("posture_on","posture_OK",0))
				printf("-----------------------pos_on-------------------\n");
				Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"���������� ��"  );			
			}
			
			
			valueLed_posture_last = currentDataPoint.valuePosture_OnOff;//reflash
		}
		
		if(posture_flag == 1)
		{
			if(Posture_first1_last != currentDataPoint.valuePosture_first1)
			{
				zigbee_send_number("pos1:",currentDataPoint.valuePosture_first1,"0",0);
				Posture_first1_last = currentDataPoint.valuePosture_first1; //reflash
			}
		
			if(Posture_first2_last != currentDataPoint.valuePosture_first2)
			{
				zigbee_send_number("pos2:",currentDataPoint.valuePosture_first2,"0",0);
				Posture_first2_last = currentDataPoint.valuePosture_first2; //reflash
			}
			
			if(Posture_first3_last != currentDataPoint.valuePosture_first3)
			{
				zigbee_send_number("pos3:",currentDataPoint.valuePosture_first3,"0",0);
				Posture_first3_last = currentDataPoint.valuePosture_first3; //reflash
			}
		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}

//****************************************************************************************************//
void Fun_night(void)
{
	Lcd_Clear(GRAY0); //���� 
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                       ҹ��ģʽ                     -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");

	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ�");
	Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  ��������");
	Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"����Ӧҹ��");
	Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ����");
	Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ��");
	
	if(homework_flag==1)Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ� ��");
	if(posture_flag==1)Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  �������� ��");
	if(night_flag==1)Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"����Ӧҹ�� ��");
	if(other1_flag==1)Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ���� ��");
	if(other2_flag==1)Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ�� ��");

	printf("night");
	while(1)
	{
		if(go_gui_flag && go_gui_flag != 4){irLastTimer2 = gizGetTimerCount();break;}

		keyFlag = KEY_Scan();
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES || night_red_last!=currentDataPoint.valueRed_OnOff)
		{
			night_flag++;
			if(night_flag==2 || night_flag==0)
			{
				zigbee_send_cmd("night_off","0",0);
				night_flag=0;
				printf("------------------night_off---------------\r\n");
				Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"����Ӧҹ��    ");
			}
			
			if(night_flag==1) 
			{
				zigbee_send_cmd("night_on","0",0);
				red_Init();
				printf("------------------night_on---------------\r\n");
				Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"����Ӧҹ�� ��");
			}
			
	//		night_red_last = currentDataPoint.valueRed_OnOff;
			printf("nig_on");
			
			night_red_last=currentDataPoint.valueRed_OnOff;//reflash
		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}

//****************************************************************************************************//
void other1(void)
{

	Lcd_Clear(GRAY0); //���� 
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                       other1                       -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");

	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ�");
	Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  ��������");
	Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ��");
	Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"����Ϣ����");
	Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ��");

	if(homework_flag==1)Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ� ��");
	if(posture_flag==1)Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  �������� ��");
	if(night_flag==1)Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ�� ��");
	if(other1_flag==1)Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"����Ϣ���� ��");
	if(other2_flag==1)Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"  ����ʱ�� ��");
						
	
	while(1)
	{
		if(go_gui_flag){irLastTimer2 = gizGetTimerCount();break;}

		keyFlag = KEY_Scan();
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES || keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES || (otherpos1 != currentDataPoint.valueswitch1))
		{
				other1_flag++;
				if((otherpos1 != currentDataPoint.valueswitch1)){other1_flag = otherpos1 = currentDataPoint.valueswitch1;}
			
				if(other1_flag==2 || other1_flag==0 )
				{
					other1_flag=0;
					printf("------------------other1---------------\r\n");
					Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"����Ϣ����    ");
					if(keyFlag==WKUP_PRES)currentDataPoint.valueswitch1 = 0;//ͬ��
				}
				if(other1_flag==1 || currentDataPoint.valueswitch1 == 0x01) 
				{
					Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"����Ϣ���� ��");
					if(keyFlag==WKUP_PRES)currentDataPoint.valueswitch1 = 1;//ͬ��
				}
				
				
		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}


void other2(void)
{
	Lcd_Clear(GRAY0); //���� 
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                       other2                       -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");

	Gui_DrawFont_GBK24(10,100,BLACK,GRAY0,(u8*)"����");
	Gui_DrawFont_GBK24(100,100,BLACK,GRAY0,(u8*)"ɫ��");
	Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ�");
	Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  ��������");
	Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ��");
	Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ����");
	Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"������ʱ��");

	if(homework_flag==1)Gui_DrawFont_GBK16(20,lcd_num,BLACK,GRAY0,(u8*)"  ��ҵ�ػ� ��");
	if(posture_flag==1)Gui_DrawFont_GBK16(20,lcd_num*3,BLACK,GRAY0,(u8*)"  �������� ��");
	if(night_flag==1)Gui_DrawFont_GBK16(20,lcd_num*5,BLACK,GRAY0,(u8*)"  ��Ӧҹ�� ��");
	if(other1_flag==1)Gui_DrawFont_GBK16(20,lcd_num*7,BLACK,GRAY0,(u8*)"  ��Ϣ���� ��");
	if(other2_flag==1)Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"������ʱ�� ��");
					
	
	while(1)
	{
		if(go_gui_flag){irLastTimer2 = gizGetTimerCount();break;}
		keyFlag = KEY_Scan();
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES || keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES || (otherpos2 != currentDataPoint.valueswitch2))
		{
				other2_flag++;
				if((otherpos2 != currentDataPoint.valueswitch2)){
					otherpos2 = currentDataPoint.valueswitch2;
					if(otherpos2 == 0)other2_flag = 1;
					else other2_flag = 0;
					}
				
				if(other2_flag==2 || other2_flag==0)
				{
					other2_flag=0;
					
					printf("------------------other2---------------\r\n");
					Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"������ʱ��    ");
					if(keyFlag==WKUP_PRES){currentDataPoint.valueswitch2 = 1;scree_close = 1;}
				}
				if(other2_flag==1) 
				{
					Gui_DrawFont_GBK16(20,lcd_num*9,BLACK,GRAY0,(u8*)"������ʱ�� ��");
					if(keyFlag==WKUP_PRES){currentDataPoint.valueswitch2 = 0;scree_close = 0;}
				}
	
		}
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}
//*****************************************************************************************************************//
void time_show()
{
	Lcd_Clear(GRAY1);
						printf("------------------------------------------------------\r\n");
						printf("-                                                    -\r\n");
						printf("-                      ����ʱ��                      -\r\n");
						printf("-                                                    -\r\n");
						printf("------------------------------------------------------\r\n");
	while(1)
	{
		if(go_gui_flag && go_gui_flag != 5){showtime_flag = 0;irLastTimer2 = gizGetTimerCount();break;}
		
		if(showtime_flag == 1)Show_Time(0,20);	
		if(DHT11_init_flag == 1)Show_TH(10,70,GRAY1);
			
		keyFlag = KEY_Scan();
		if(keyFlag == KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES||keyFlag==WKUP_PRES){showtime_flag = 0;break;} //���а������¾�����
		
		//------------------------------------------------------//
		Communi_Interaction();
		//------------------------------------------------------//	
	}
}


/******************************************************************************************************************/
	/*�˵���4������10������*/
	/*��ǰ���¡��ϡ����롢����*/
// ��ǰ��������
// ɫ�°�����Ҫ��ת������ 0
// ��ǿ������Ҫ��ת������ 1
// ģʽ������Ҫ��ת������ 2
// ȷ�ϰ�����Ҫ��ת������ wkup
myGUIIndexTypeDef const keyTab[GUI_NUM]={
	{0,0,0,1,0,(*Fun_light)	},   //�˵���ʾ
	{1,0,0,2,1,(*Fun_homework)}, 
	{2,0,0,3,2,(*Fun_posture)},  
	{3,0,0,5,3,(*Fun_night)},  
	{4,0,0,0,0,(*time_show)},
	{5,0,0,6,5,(*other1)},
	{6,0,0,1,6,(*other2)},
};


/*

* �������ܣ��������
* �����������
* �����������
* ����ֵ  ����
* ����    ��

*/
void displayOperation(void)
{
	if(go_gui_flag)
	{
		    switch(go_gui_flag)//��ʼֵkeyFun=0; 
			{
				case 1	:	keyFunPt = &Fun_light;                  break; 
				case 2		:	keyFunPt = &Fun_homework;           break;
				case 3	:	keyFunPt = &Fun_posture;		        break; 
				case 4		:	keyFunPt = &Fun_night;	            break; 
				case 5  :   keyFunPt = &time_show;	                break; 
				case 6      :	keyFunPt = &other1;					break;
				case 7  :   keyFunPt = &other2;						break;
				default:break;
			}
			go_gui_flag = 0;//reflash
	}
	else{	switch(keyFlag)//��ʼֵkeyFun=0; 
			{
				case KEY0_PRES	:	keyFun = keyTab[keyFun].downIndex;	keyFlag=0;	break;   //ɫ��
				case KEY1_PRES		:	keyFun = keyTab[keyFun].upIndex;		keyFlag=0;	break;//��ǿ
				case KEY2_PRES	:	keyFun = keyTab[keyFun].enterIndex;	keyFlag=0;	break; //ģʽ
				case WKUP_PRES		:	keyFun = keyTab[keyFun].escIndex;		keyFlag=0;	break; //ȷ��
				
				default:break;
			}
			keyFunPt = keyTab[keyFun].function;
		}
	
		(*keyFunPt)();                     //ִ�е�ǰ��������
	
}




