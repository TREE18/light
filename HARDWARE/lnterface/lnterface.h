#ifndef _Lnterface_H
#define _Lnterface_H
#include "sys.h"

#define Superior_Choice      Upper        //�ϼ�ѡ��
#define TheLeft_Choice       Left         //��ѡ��
#define RightLevel_Choice    Right        //�Ҽ�ѡ��
#define Subordinate_Choice   Lower        //�¼�ѡ��
#define Determine_Choice     Determine    //ȷ��ѡ��
#define Return_Choice        Return       //����ѡ��

#define EvenBy      1  //����
#define SinfleClick 0  //����


void DayAndDayDisplay    (void);          //���·�
void WhenTheDisplay      (void);          //ʱ��
void ElectricityDisplay  (void);          //����
void BluetoothDisplay    (void);          //����
void SignalDisplay       (void);          //�ź�
void WifiDisplay         (void);          //WIFI
void Status_Bar          (void);          //״̬��
void FlashlightDisplay   (void);          //�ֵ�Ͳ
void lnterface           (void);          //�˻�����
void Main_Menu           (void);          //���˵�
void Menu_2              (void);          //�����˵�
void Menu_3              (void);          //�����˵�

void Display(int y1,int y2,int y3);
#endif
