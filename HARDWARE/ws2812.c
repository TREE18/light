#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ws2812.h"
#include "spi2.h"
#include  "usart.h"
//#include "gizwits_product.h"
//extern dataPoint_t currentDataPoint;
extern unsigned char Change_T_stronge[1][3];
u8 TX_buffer_0[1]={0x30};//0
u8 TX_buffer_1[1]={0xf0};//1
u8 TX_buffer_res[1]={0x00};//1
u8 RX_buffer[1]={0x33};

void PB0_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
// GPIO_SetBits(GPIOB,GPIO_Pin_0);						 //PB.5 �����
}

//-------------------------------------------------------------------------------
//�ӳ�������:IO_Init(void)
//���ܣ��˿ڳ�ʼ��
//-------------------------------------------------------------------------------
void IO_Init(void)
{
	
}

//-------------------------------------------------------------------------------
//�ӳ�������:ResetDateFlow(void)
//���ܣ���λ��Ϊ��һ�η�����׼����
//˵������DI��λΪ0����ʱԼ65us
//-------------------------------------------------------------------------------
void ResetDataFlow(void)
{
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);

	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);

	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);
	DMA1_Spi2_TX(TX_buffer_res,1);

}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOnePix(unsigned char *ptr)
//���ܣ�����һ�����ص��24bit����
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ������������Byte�����ݷ���
//˵��������������ֱ�ӵ��ô˺���ʱ��������֡���Ϳ�ʼǰ��Ҫ��ִ�� ResetDataFlow()
//		�����ǰ�������ķ�ʽ���ͣ�����Ϊ800KBPS
//-------------------------------------------------------------------------------
void SendOnePix(unsigned char *ptr)
{
	unsigned char i,j;
	unsigned char temp;

	for(j=0;j<3;j++)
	{
		temp=ptr[j];
		for(i=0;i<8;i++)
		{
			if(temp&0x80)		 //�Ӹ�λ��ʼ����
			{
				DMA1_Spi2_TX(TX_buffer_1,1);
			}
			else				//���͡�0����
			{
				DMA1_Spi2_TX(TX_buffer_0,1);
			}	
			temp=(temp<<1);		 //����λ
		}
	}
}

void SendOnePix_tem(unsigned char *ptr,u8 tem)//����44������ɫ��
{
	unsigned char i,j;
	unsigned char temp;

	for(j=0;j<3;j++)
	{
		if(0 == j)Change_T_stronge[0][0]=temp=ptr[j]+2*tem;
		if(1 == j)Change_T_stronge[0][1]=temp=ptr[j];
		if(2 == j)Change_T_stronge[0][2]=temp=ptr[j]+4*tem;
		for(i=0;i<8;i++)
		{
			if(temp&0x80)		 //�Ӹ�λ��ʼ����
			{
				DMA1_Spi2_TX(TX_buffer_1,1);
			}
			else				//���͡�0����
			{
				DMA1_Spi2_TX(TX_buffer_0,1);
			}	
			temp=(temp<<1);		 //����λ
		}
	}
}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrame(unsigned char *ptr)
//���ܣ�����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ��������������ݷ���
//-------------------------------------------------------------------------------
void SendOneFrame(unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=0;k<SNUM;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

void SendOneFrame_sample(unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=0;k<SNUM;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

void SendOneFrame_sample_grade(unsigned char *ptr,u8 tem)//����44��ɫ�µ���
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�
	printf("//////////%d//////////\r\n",ptr[0]);
	printf("//////////%d//////////\r\n",ptr[1]);
	printf("//////////%d//////////\r\n",ptr[2]);
	
	

	for(k=0;k<SNUM;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix_tem(&ptr[0],tem);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

void SendOneFrame_stronge(unsigned char *ptr,unsigned char *zero,int grand)
{
	unsigned char k,R;
	

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=1,R=1;k<=SNUM;k++,R++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{	
		if(5 == R)R = 1;
		if((1 == grand)&&((k%3) == 0))SendOnePix(&zero[0]);
		else if((2 == grand)&&((k%2) == 0))SendOnePix(&zero[0]);
		else if((3 == grand)&&((R%2) == 0||(R%3) == 0))SendOnePix(&zero[0]);
		else if(4 == grand)SendOnePix(&zero[0]);
		else SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}


//-------------------------------------------------------------------------------
//�ӳ�������:SendSameColor(unsigned char *ptr,unsigned char cnt)
//���ܣ���ͬ��ɫ�ĵ㷢��cnt��
//���������յĲ�����һ��ָ�룬ָ�����ص���ɫ���飬cnt���ݷ��͸���
//-------------------------------------------------------------------------------
void SendSameColor(unsigned char *ptr,unsigned char cnt)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=0;k<cnt;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrameFrom(unsigned char i,unsigned char *ptr)
//���ܣ���ָ�������ص㿪ʼ����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ����֡���ݷ���
//		i:������ĵ�0���������ݷ��͵���i�����ص㣨��0�������ǰ��ϱ��Ϊ01�����أ�
//˵������ԭ����Ӧ��һ�����ص����ݻᷢ�͵���i�����ص㣨LED����
//-------------------------------------------------------------------------------
void SendOneFrameFrom(unsigned char i,unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

   	for(k=(SNUM-i);k<SNUM;k++)		 //����һ֡����
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<(SNUM-i);k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrameSince(unsigned char i,unsigned char *ptr)
//���ܣ��ӵ�i�����ص�����ݿ�ʼ����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ����֡���ݷ���
//		i:������ĵ�i���������ݷ��͵���1�����ص�
//˵������ԭ����Ӧ��i���ص����ݻᷢ�͵���1�����ص㣨LED���ϣ���i+1�����ص������
//		���͵���2��������
//-------------------------------------------------------------------------------
void SendOneFrameSince(unsigned char i,unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=i;k<SNUM;k++)				 //����һ֡����
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<i;k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}
	ResetDataFlow();				 //����֡��λ�ź�
}
/**********************************THE END**********************************/ 

 

