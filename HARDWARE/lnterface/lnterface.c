#include "lnterface.h"


//��ʾ�����������Ϣ
void DayAndDayDisplay(void)                  //������
{
	OLED_ShowNum(51,5,year,4,12);              //��
  OLED_ShowNum(2*16,6,month,4,12);           //��
	OLED_P6x8Str(3.7*16,7,"/");
	OLED_ShowNum(4*16,6,day,2,12);             //��
}


//��ʾʱ���������Ϣ
void WhenTheDisplay(void)                    //ʱ��
{
	  OLED_P16x32Ch(1.2*18,2,1);
		OLED_P16x32Ch(2.2*18,2,9);
		OLED_P16x32Ch(3.2*18,2,10);
		OLED_P16x32Ch(4*18,2,3);
		OLED_P16x32Ch(5*18,2,4);
}



//��ʾ��ص��������Ϣ
void ElectricityDisplay()                    //����
{
   OLED_P16x16Ch(111,0,Electricity_Sign);
}	




//��ʾ���������Ϣ
void BluetoothDisplay()                      //����
{
	if(Bluetooth_Sign)
	OLED_P16x16Ch(16,0,5);
}



//��ʾ�ź������Ϣ
void SignalDisplay(void)                     //�ź�
{
  OLED_P16x16Ch(0,0,38);
}



//��ʾWIFI�����Ϣ
void WifiDisplay()                           //WIFI//33.34.35.36  
{
  OLED_P16x16Ch(32,0,WIFI_Sign);
}


//��ʾ�ֵ�Ͳ�����Ϣ
void FlashlightDisplay()                     //�ֵ�Ͳ
{
	if(Flashlight_Sign)
  OLED_P16x16Ch(90,0,40);
}


//��ʾ״̬����Ϣ
void Status_Bar(void)                         //״̬��
{
    SignalDisplay();                          //�ź�    //38
	  BluetoothDisplay();                       //����    //5
	  WifiDisplay();                            //WIFI    //33.34.35.36
	  FlashlightDisplay();                      //�ֵ�Ͳ  //40
	  ElectricityDisplay();                     //����
}


void Display(int y1,int y2,int y3)
{
	static int conut=0;
  switch(Page_Sgin)	
	{
	   case 2:
			      switch(y1)
						{
							
						   case 1:
											OLED_P8x16Str(1*16,2,"00");
											OLED_P8x16Str(1*16,4,"01"); 
											OLED_P8x16Str(1*16,6,"02");   
               break;
							 case 2:
											OLED_P8x16Str(1*16,2,"01");   
											OLED_P8x16Str(1*16,4,"02");        
											OLED_P8x16Str(1*16,6,"03");  
               break;
							 case 3:
											OLED_P8x16Str(1*16,2,"02");   
											OLED_P8x16Str(1*16,4,"03");        
											OLED_P8x16Str(1*16,6,"04");  
               break;
							 
							 default : break;
						}
			 
		break;	  
			 
		 
		 default : break;
	}
	     
	/*OLED_P8x16Str(1*16,y,"03");        
	OLED_P8x16Str(1*16,y,"04");        
	OLED_P8x16Str(1*16,y,"05");        
	OLED_P8x16Str(1*16,y,"06");        	
	/*OLED_P16x16Ch(1*16,y,45);                 //��
	OLED_P16x16Ch(2*16,y,46);                   //��
	OLED_P16x16Ch(3*16,y,47);                   //��
	
	OLED_P16x16Ch(1*16,y+2,65);                 //��
	OLED_P16x16Ch(2*16,y+2,66);                 //��
	
	OLED_P8x16Str(1*16,y+4,"WIFI");             //WIFI
	
	OLED_P16x16Ch(1*16,4,67);                   //��
	OLED_P16x16Ch(2*16,4,68);                   //��
	
	OLED_P16x16Ch(1*16,4,52);                   //ʱ
	OLED_P16x16Ch(2*16,4,53);                   //��
	
	OLED_P16x16Ch(1*16,4,54);                   //��
	OLED_P16x16Ch(2*16,4,55);                   //ѹ
	
	OLED_P16x16Ch(1*16,4,54);                   //��
	OLED_P16x16Ch(2*16,4,56);                   //��
	
	OLED_P16x16Ch(1*16,2,69);                   //��
	OLED_P16x16Ch(2*16,2,70);                   //ǰ
  OLED_P16x16Ch(3*16,2,71);                   //״ 
	OLED_P16x16Ch(4*16,2,72);                   //̬
	OLED_P16x16Ch(1*16,4,73);                   //��
	OLED_P16x16Ch(2*16,4,74);                   //��
  OLED_P16x16Ch(3*16,4,50);                   //��
	OLED_P16x16Ch(4*16,4,51);                   //��
	if(Flashlight_Sign)OLED_P16x16Ch(6*16,2,48);    
	else  OLED_P16x16Ch(6*16,2,49);  */  
}

//  IICЭ��    OLED�� �˻�����
void lnterface(void)                          //�˻�����
{
	
	Status_Bar();                              
	switch(Page_Sgin)	
	{		
		case 0:
			     Main_Menu(); break;
		case 2:
			     Menu_2(); break;
		case 3:
			     Menu_3();break;
		
		
		default : break;
	}
	
}


//���˵�
void Main_Menu(void)
{
  WhenTheDisplay();                             //��ʾʱ����
	DayAndDayDisplay();                         //��ʾ������
	OLED_P16x16Ch(0*16,6,11);                   //��ʾ //��
	OLED_P16x16Ch(1*16,6,12);                   //��ʾ //��
	OLED_P16x16Ch(6*16,6,13);                   //��ʾ //��	
	OLED_P16x16Ch(7*16,6,14);                   //��ʾ //��
	if(KEY_Scan(Key_Selectio)==Determine_Choice)//�ж��Ƿ���ȷ������
	{                            
		Page_Sgin=2;                              //ҳ��ѡ����2
		OLED_P128x48Ch(0,2,0);                    //���������
	}
}

void Menu_2(void)
{ 
	if(Choice==2||Choice==4||Choice==6)	
	{

		OLED_P16x16Ch(0*16,Choice,44);              //ѡ��
		Display(2,0,0);
		
		
		switch(KEY_Scan(Key_Selectio))	
		{		
			case Superior_Choice:                     //�Ϸ�
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice-=2;
				   break;
			case Subordinate_Choice:                  //�·�
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice+=2;
				   break;
			case Determine_Choice:                    //ȷ��
				   OLED_P128x48Ch(0,2,0);               //���������
			     Page_Sgin=3;Choice=2;
				   break;
			case Return_Choice:                       //����
				   OLED_P128x48Ch(0,2,0);
				   Page_Sgin=0;    
			     break;
			default : 
				   break;
		}
		
	}	
	else if(Choice>6)Choice=2;
	else if(Choice<2)Choice=6;
	
	OLED_ShowNum(6*16,6,Choice/2,1,12);
	OLED_P6x8Str(6.5*16,7,"/");
	OLED_P6x8Str(7*16,7,"10");	  
}
void Menu_3(void)
{
	if(Choice==2||Choice==4||Choice==6)	
	{
		OLED_P16x16Ch(0*16,Choice,44);              //ѡ��
		Display(2,0,0);
		
		switch(KEY_Scan(Key_Selectio))	
		{		
			case Superior_Choice:                     //�Ϸ�
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice-=2;
				   break;
			case Subordinate_Choice:                  //�·�
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice+=2;
				   break;
			case Determine_Choice:                    //ȷ��
				   OLED_P128x48Ch(0,2,0);               //���������
			     Page_Sgin=3;Choice=2;
				   break;
			case Return_Choice:                       //����
				   OLED_P128x48Ch(0,2,0);
				   Page_Sgin=2;Choice=2;  
			     break;
			default : 
				   break;
		}
		
	}	
	else if(Choice>6)Choice=2;
	else if(Choice<2)Choice=6;
	
	OLED_ShowNum(6*16,6,Choice/2,1,12);
	OLED_P6x8Str(6.5*16,7,"/");
	OLED_P6x8Str(7*16,7,"10");	  
}
	

	
	
	
	




