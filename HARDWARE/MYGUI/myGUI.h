#ifndef _MYGUI_H_
#define _MYGUI_H_
#include "sys.h"
#include "myconf.h"
#include "gizwits_protocol.h"

#define  GUI_NUM 30
//#define  Light_Gui 1
//#define  Homework_Gui 2
//#define  Posture_Gui 3
//#define  Night_Gui 4

extern u8 music01[6],music02[6],music03[6],music04[6];
extern u8 keyFlag;
extern unsigned char s6100[4][3],Change_T[1][3];
extern unsigned char s2500[1][3];
extern unsigned char zero[1][3];
extern char red_flag;
extern gizwitsProtocol_t gizwitsProtocol;//为了获取网络时间
extern dataPoint_t currentDataPoint;  

extern char wifi_gizwit , KEY_VALUE;
extern u16 link_time;
extern uint32_t irLastTimer2 ;

typedef struct{
	
	u8 curIndex;				// 当前界面索引
	u8 downIndex;				// 向下按键需要跳转的索引
	u8 upIndex;					// 向上按键需要跳转的索引
	u8 enterIndex;			// 确认按键需要跳转的索引
	u8 escIndex;				// 返回按键需要跳转的索引
	void (*function)(); // 当前索引执行函数的入口地址
		
}myGUIIndexTypeDef;

void Fun_menuDisplay(void);
void Fun_homework(void);
void displayOperation(void);
//void WifiDisplay         (void);          //WIFI
//void ElectricityDisplay  (void);          //电量
//void FlashlightDisplay   (void);                   //手电筒
#endif











