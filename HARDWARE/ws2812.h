

#ifndef _WS2812_H_
#define _WS2812_H_
#include "sys.h"

/*******************************ͨ�Žӿ�����***********************************/

//sbit DI = P5^5;						    //���ݶ˿�

/*----------------------------���鴮����������--------------------------------*/  
#define SNUM 32
/*--------------------------------��������------------------------------------*/   
void IO_Init(void);						//IO�˿ڳ�ʼ��
void SendOnePix(unsigned char *ptr);	//����һ��LED��24bit����
void SendOnePix_tem(unsigned char *ptr,u8 tem);
void ResetDataFlow(void);				//оƬ��λ���壬Ϊ������һ֡��׼��
void SendOneFrame(unsigned char *ptr);	//����һ֡����
void SendSameColor(unsigned char *ptr,unsigned char cnt);  //��ͬ��ɫ�������ɴ�
void SendOneFrameFrom(unsigned char i,unsigned char *ptr);//�ӵ�i�����ؿ�ʼ����
														  //һ֡����
void SendOneFrameSince(unsigned char i,unsigned char *ptr);//�ӵ�i�����ص������
														   //��ʼ����
void PB0_Init(void);

void SendOneFrame_stronge(unsigned char *ptr,unsigned char *zero,int grand);
void SendOneFrame_sample(unsigned char *ptr);
void SendOneFrame_sample_grade(unsigned char *ptr,u8 tem);
#endif

//-------------------------THE END------------------------*/   
