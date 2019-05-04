#include "lnterface.h"


//显示年月日相关信息
void DayAndDayDisplay(void)                  //年月日
{
	OLED_ShowNum(51,5,year,4,12);              //年
  OLED_ShowNum(2*16,6,month,4,12);           //月
	OLED_P6x8Str(3.7*16,7,"/");
	OLED_ShowNum(4*16,6,day,2,12);             //日
}


//显示时分相关形信息
void WhenTheDisplay(void)                    //时分
{
	  OLED_P16x32Ch(1.2*18,2,1);
		OLED_P16x32Ch(2.2*18,2,9);
		OLED_P16x32Ch(3.2*18,2,10);
		OLED_P16x32Ch(4*18,2,3);
		OLED_P16x32Ch(5*18,2,4);
}



//显示电池电量相关信息
void ElectricityDisplay()                    //电量
{
   OLED_P16x16Ch(111,0,Electricity_Sign);
}	




//显示蓝牙相关信息
void BluetoothDisplay()                      //蓝牙
{
	if(Bluetooth_Sign)
	OLED_P16x16Ch(16,0,5);
}



//显示信号相关信息
void SignalDisplay(void)                     //信号
{
  OLED_P16x16Ch(0,0,38);
}



//显示WIFI相关信息
void WifiDisplay()                           //WIFI//33.34.35.36  
{
  OLED_P16x16Ch(32,0,WIFI_Sign);
}


//显示手电筒相关信息
void FlashlightDisplay()                     //手电筒
{
	if(Flashlight_Sign)
  OLED_P16x16Ch(90,0,40);
}


//显示状态栏信息
void Status_Bar(void)                         //状态栏
{
    SignalDisplay();                          //信号    //38
	  BluetoothDisplay();                       //蓝牙    //5
	  WifiDisplay();                            //WIFI    //33.34.35.36
	  FlashlightDisplay();                      //手电筒  //40
	  ElectricityDisplay();                     //电量
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
	/*OLED_P16x16Ch(1*16,y,45);                 //照
	OLED_P16x16Ch(2*16,y,46);                   //明
	OLED_P16x16Ch(3*16,y,47);                   //灯
	
	OLED_P16x16Ch(1*16,y+2,65);                 //蓝
	OLED_P16x16Ch(2*16,y+2,66);                 //牙
	
	OLED_P8x16Str(1*16,y+4,"WIFI");             //WIFI
	
	OLED_P16x16Ch(1*16,4,67);                   //温
	OLED_P16x16Ch(2*16,4,68);                   //度
	
	OLED_P16x16Ch(1*16,4,52);                   //时
	OLED_P16x16Ch(2*16,4,53);                   //钟
	
	OLED_P16x16Ch(1*16,4,54);                   //电
	OLED_P16x16Ch(2*16,4,55);                   //压
	
	OLED_P16x16Ch(1*16,4,54);                   //电
	OLED_P16x16Ch(2*16,4,56);                   //流
	
	OLED_P16x16Ch(1*16,2,69);                   //当
	OLED_P16x16Ch(2*16,2,70);                   //前
  OLED_P16x16Ch(3*16,2,71);                   //状 
	OLED_P16x16Ch(4*16,2,72);                   //态
	OLED_P16x16Ch(1*16,4,73);                   //亮
	OLED_P16x16Ch(2*16,4,74);                   //度
  OLED_P16x16Ch(3*16,4,50);                   //设
	OLED_P16x16Ch(4*16,4,51);                   //置
	if(Flashlight_Sign)OLED_P16x16Ch(6*16,2,48);    
	else  OLED_P16x16Ch(6*16,2,49);  */  
}

//  IIC协议    OLED屏 人机界面
void lnterface(void)                          //人机界面
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


//主菜单
void Main_Menu(void)
{
  WhenTheDisplay();                             //显示时分秒
	DayAndDayDisplay();                         //显示年月日
	OLED_P16x16Ch(0*16,6,11);                   //显示 //菜
	OLED_P16x16Ch(1*16,6,12);                   //显示 //单
	OLED_P16x16Ch(6*16,6,13);                   //显示 //退	
	OLED_P16x16Ch(7*16,6,14);                   //显示 //出
	if(KEY_Scan(Key_Selectio)==Determine_Choice)//判断是否按下确定按键
	{                            
		Page_Sgin=2;                              //页面选择置2
		OLED_P128x48Ch(0,2,0);                    //清除内容栏
	}
}

void Menu_2(void)
{ 
	if(Choice==2||Choice==4||Choice==6)	
	{

		OLED_P16x16Ch(0*16,Choice,44);              //选择
		Display(2,0,0);
		
		
		switch(KEY_Scan(Key_Selectio))	
		{		
			case Superior_Choice:                     //上翻
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice-=2;
				   break;
			case Subordinate_Choice:                  //下翻
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice+=2;
				   break;
			case Determine_Choice:                    //确定
				   OLED_P128x48Ch(0,2,0);               //清除内容栏
			     Page_Sgin=3;Choice=2;
				   break;
			case Return_Choice:                       //返回
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
		OLED_P16x16Ch(0*16,Choice,44);              //选择
		Display(2,0,0);
		
		switch(KEY_Scan(Key_Selectio))	
		{		
			case Superior_Choice:                     //上翻
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice-=2;
				   break;
			case Subordinate_Choice:                  //下翻
				   OLED_P16x16Ch(0*16,Choice,37);
				   Choice+=2;
				   break;
			case Determine_Choice:                    //确定
				   OLED_P128x48Ch(0,2,0);               //清除内容栏
			     Page_Sgin=3;Choice=2;
				   break;
			case Return_Choice:                       //返回
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
	

	
	
	
	




