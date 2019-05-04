#include "dma.h"

DMA_InitTypeDef DMA_InitStructure;

uint8_t buffer0[1]={0x30};
uint8_t buffer1[1]={0xf3};
u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 	    
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量 
void MYDMA_Config(u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
  DMA_DeInit(DMA1_Channel5);   //将DMA的通道1寄存器重设为缺省值

	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4000380C;  //DMA外设基地址//0x4000380C 通道5 tx
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)buffer0;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode =  DMA_Mode_Normal;//DMA_Mode_Circular;//DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	 
	 if(DMA_GetITStatus(DMA1_IT_TC5)!= RESET)
	 {
              
		 DMA_ClearITPendingBit(DMA1_IT_TC5);
        
	 }
        
	 DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
        
	 SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

        /* Enable DMA1 Channel5 SPI1_TX */
        DMA_Cmd(DMA1_Channel5, DISABLE);
} 
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}	  

 
void SPI2_DMA_Write_0(uint16_t len) {
        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
       //DMA1_Channel4->CMAR  = (uint32_t)SPI2_Rx_Buf;
        DMA1_Channel5->CMAR  = (uint32_t)buffer0;
        DMA1_Channel4->CNDTR = len;
        DMA1_Channel5->CNDTR = len;
        DMA_Cmd(DMA1_Channel4, ENABLE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
        SPI_Cmd(SPI2, ENABLE);
}

void SPI2_DMA_Write_1(uint16_t len) {
        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
        SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
       //DMA1_Channel4->CMAR  = (uint32_t)SPI2_Rx_Buf;
        DMA1_Channel5->CMAR  = (uint32_t)buffer0;
        DMA1_Channel4->CNDTR = len;
        DMA1_Channel5->CNDTR = len;
        DMA_Cmd(DMA1_Channel4, ENABLE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
        SPI_Cmd(SPI2, ENABLE);
}






















