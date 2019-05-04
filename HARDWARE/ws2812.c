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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
// GPIO_SetBits(GPIOB,GPIO_Pin_0);						 //PB.5 输出高
}

//-------------------------------------------------------------------------------
//子程序名称:IO_Init(void)
//功能：端口初始化
//-------------------------------------------------------------------------------
void IO_Init(void)
{
	
}

//-------------------------------------------------------------------------------
//子程序名称:ResetDateFlow(void)
//功能：复位，为下一次发送做准备，
//说明：将DI置位为0后，延时约65us
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
//子程序名称:SendOnePix(unsigned char *ptr)
//功能：发送一个像素点的24bit数据
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的连续的三个Byte的数据发送
//说明：在主函数中直接调用此函数时，在整个帧发送开始前需要先执行 ResetDataFlow()
//		数据是按归零码的方式发送，速率为800KBPS
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
			if(temp&0x80)		 //从高位开始发送
			{
				DMA1_Spi2_TX(TX_buffer_1,1);
			}
			else				//发送“0”码
			{
				DMA1_Spi2_TX(TX_buffer_0,1);
			}	
			temp=(temp<<1);		 //左移位
		}
	}
}

void SendOnePix_tem(unsigned char *ptr,u8 tem)//用于44级调节色温
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
			if(temp&0x80)		 //从高位开始发送
			{
				DMA1_Spi2_TX(TX_buffer_1,1);
			}
			else				//发送“0”码
			{
				DMA1_Spi2_TX(TX_buffer_0,1);
			}	
			temp=(temp<<1);		 //左移位
		}
	}
}
//-------------------------------------------------------------------------------
//子程序名称:SendOneFrame(unsigned char *ptr)
//功能：发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整个数组的数据发送
//-------------------------------------------------------------------------------
void SendOneFrame(unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=0;k<SNUM;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //发送帧复位信号
}

void SendOneFrame_sample(unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=0;k<SNUM;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //发送帧复位信号
}

void SendOneFrame_sample_grade(unsigned char *ptr,u8 tem)//用于44级色温调节
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号
	printf("//////////%d//////////\r\n",ptr[0]);
	printf("//////////%d//////////\r\n",ptr[1]);
	printf("//////////%d//////////\r\n",ptr[2]);
	
	

	for(k=0;k<SNUM;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix_tem(&ptr[0],tem);
	}

	ResetDataFlow();				 //发送帧复位信号
}

void SendOneFrame_stronge(unsigned char *ptr,unsigned char *zero,int grand)
{
	unsigned char k,R;
	

	ResetDataFlow();				 //发送帧复位信号

	for(k=1,R=1;k<=SNUM;k++,R++)				 //发送一帧数据，SNUM是板子LED的个数
	{	
		if(5 == R)R = 1;
		if((1 == grand)&&((k%3) == 0))SendOnePix(&zero[0]);
		else if((2 == grand)&&((k%2) == 0))SendOnePix(&zero[0]);
		else if((3 == grand)&&((R%2) == 0||(R%3) == 0))SendOnePix(&zero[0]);
		else if(4 == grand)SendOnePix(&zero[0]);
		else SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //发送帧复位信号
}


//-------------------------------------------------------------------------------
//子程序名称:SendSameColor(unsigned char *ptr,unsigned char cnt)
//功能：相同颜色的点发送cnt次
//参数：接收的参数是一个指针，指向像素点颜色数组，cnt传递发送个数
//-------------------------------------------------------------------------------
void SendSameColor(unsigned char *ptr,unsigned char cnt)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=0;k<cnt;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //发送帧复位信号
}
//-------------------------------------------------------------------------------
//子程序名称:SendOneFrameFrom(unsigned char i,unsigned char *ptr)
//功能：从指定的像素点开始发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整帧数据发送
//		i:把数组的第0个像素数据发送到第i个像素点（第0个像素是板上标号为01的像素）
//说明：即原本对应第一个像素的数据会发送到第i个像素点（LED）上
//-------------------------------------------------------------------------------
void SendOneFrameFrom(unsigned char i,unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

   	for(k=(SNUM-i);k<SNUM;k++)		 //发送一帧数据
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<(SNUM-i);k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //发送帧复位信号
}

//-------------------------------------------------------------------------------
//子程序名称:SendOneFrameSince(unsigned char i,unsigned char *ptr)
//功能：从第i个像素点的数据开始发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整帧数据发送
//		i:把数组的第i个像素数据发送到第1个像素点
//说明：即原本对应第i像素的数据会发送到第1个像素点（LED）上，第i+1个像素点的数据
//		发送到第2个像素上
//-------------------------------------------------------------------------------
void SendOneFrameSince(unsigned char i,unsigned char *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=i;k<SNUM;k++)				 //发送一帧数据
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<i;k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}
	ResetDataFlow();				 //发送帧复位信号
}
/**********************************THE END**********************************/ 

 

