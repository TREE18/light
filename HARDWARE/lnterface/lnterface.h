#ifndef _Lnterface_H
#define _Lnterface_H
#include "sys.h"

#define Superior_Choice      Upper        //上级选择
#define TheLeft_Choice       Left         //左级选择
#define RightLevel_Choice    Right        //右级选择
#define Subordinate_Choice   Lower        //下级选择
#define Determine_Choice     Determine    //确定选择
#define Return_Choice        Return       //返回选择

#define EvenBy      1  //连按
#define SinfleClick 0  //单按


void DayAndDayDisplay    (void);          //年月份
void WhenTheDisplay      (void);          //时分
void ElectricityDisplay  (void);          //电量
void BluetoothDisplay    (void);          //蓝牙
void SignalDisplay       (void);          //信号
void WifiDisplay         (void);          //WIFI
void Status_Bar          (void);          //状态栏
void FlashlightDisplay   (void);          //手电筒
void lnterface           (void);          //人机界面
void Main_Menu           (void);          //主菜单
void Menu_2              (void);          //二级菜单
void Menu_3              (void);          //三级菜单

void Display(int y1,int y2,int y3);
#endif
