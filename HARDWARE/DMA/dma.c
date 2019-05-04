#include "dma.h"

DMA_InitTypeDef DMA_InitStructure;

uint8_t buffer0[1]={0x30};
uint8_t buffer1[1]={0xf3};
u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void MYDMA_Config(u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
  DMA_DeInit(DMA1_Channel5);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ

	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4000380C;  //DMA�������ַ//0x4000380C ͨ��5 tx
	DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)buffer0;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode =  DMA_Mode_Normal;//DMA_Mode_Circular;//DMA_Mode_Normal;  //����������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	 
	 if(DMA_GetITStatus(DMA1_IT_TC5)!= RESET)
	 {
              
		 DMA_ClearITPendingBit(DMA1_IT_TC5);
        
	 }
        
	 DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
        
	 SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

        /* Enable DMA1 Channel5 SPI1_TX */
        DMA_Cmd(DMA1_Channel5, DISABLE);
} 
//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��      
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
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






















