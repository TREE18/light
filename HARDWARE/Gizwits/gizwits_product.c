/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "usart3.h"
#include "led.h"
#include "usart.h"
#include "dht11.h" 
#include "myGUI.h"

extern gizwitsProtocol_t gizwitsProtocol;//net time 
extern u16 link_time,auto_value;//在此用作温度上传的计时
extern u8 temperature,humidity;
static uint32_t timerMsCount;
extern char wifi_gizwit,DHT11_init_flag,night_flag,homework_flag,posture_flag;
extern char Led_OnOff_Change_flag;//云端数据点标志位
extern char go_gui_flag;
extern bool R_flag,G_flag,B_flag,auto_flag,distance_flag,showtime_flag;
extern char otherpos1,otherpos2;
bool scree_close = 0;//关闭屏保
bool WIFI_ROUTER = 0,PTIME_FLAG = 0;		
uint32_t irLastTimer1 = 0,irLastTimer2 = 0;
uint32_t timearrge = 0,alarm_time = 0;//ntp时间
/** Current datapoint */
dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_Led_OnOff_Change:
        currentDataPoint.valueLed_OnOff_Change = dataPointPtr->valueLed_OnOff_Change;
        GIZWITS_LOG("Evt: EVENT_Led_OnOff_Change %d \n", currentDataPoint.valueLed_OnOff_Change);
        if(0x01 == currentDataPoint.valueLed_OnOff_Change)
        {
          //user handle
		Led_OnOff_Change_flag=1;
        }
        else
        {
          //user handle    
			Led_OnOff_Change_flag=0;
        }
        break;
      case EVENT_Red_OnOff:
        currentDataPoint.valueRed_OnOff = dataPointPtr->valueRed_OnOff;
        GIZWITS_LOG("Evt: EVENT_Red_OnOff %d \n", currentDataPoint.valueRed_OnOff);
		go_gui_flag=4;
        if(0x01 == currentDataPoint.valueRed_OnOff)
        {
          //user handle
			night_flag=0;
        }
        else
        {
          //user handle    
			night_flag=1; 
        }
        break;
      case EVENT_RGB_OnOff:
        currentDataPoint.valueRGB_OnOff = dataPointPtr->valueRGB_OnOff;
        GIZWITS_LOG("Evt: EVENT_RGB_OnOff %d \n", currentDataPoint.valueRGB_OnOff);
        if(0x01 == currentDataPoint.valueRGB_OnOff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_LedT_C_OnOff:
        currentDataPoint.valueLedT_C_OnOff = dataPointPtr->valueLedT_C_OnOff;
        GIZWITS_LOG("Evt: EVENT_LedT_C_OnOff %d \n", currentDataPoint.valueLedT_C_OnOff);
        if(0x01 == currentDataPoint.valueLedT_C_OnOff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Posture_OnOff:
        currentDataPoint.valuePosture_OnOff = dataPointPtr->valuePosture_OnOff;
        GIZWITS_LOG("Evt: EVENT_Posture_OnOff %d \n", currentDataPoint.valuePosture_OnOff);
		go_gui_flag=3;
        if(0x01 == currentDataPoint.valuePosture_OnOff)
        {
          //user handle
			posture_flag=0;
        }
        else
        {
          //user handle    
			posture_flag=1;	
        }
        break;
      case EVENT_Time_OnOff:
        currentDataPoint.valueTime_OnOff = dataPointPtr->valueTime_OnOff;
        GIZWITS_LOG("Evt: EVENT_Time_OnOff %d \n", currentDataPoint.valueTime_OnOff);
        if(0x01 == currentDataPoint.valueTime_OnOff)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Homework_OnOff:
        currentDataPoint.valueHomework_OnOff = dataPointPtr->valueHomework_OnOff;
        GIZWITS_LOG("Evt: EVENT_Homework_OnOff %d \n", currentDataPoint.valueHomework_OnOff);
			go_gui_flag=2;
        if(0x01 == currentDataPoint.valueHomework_OnOff)
        {
          //user handle
			homework_flag=0;
        }
        else
        {
          //user handle    
			homework_flag=1;
        }
        break;
      case EVENT_Led_auto_OnOff:
        currentDataPoint.valueLed_auto_OnOff = dataPointPtr->valueLed_auto_OnOff;
        GIZWITS_LOG("Evt: EVENT_Led_auto_OnOff %d \n", currentDataPoint.valueLed_auto_OnOff);
		go_gui_flag=1;
        if(0x01 == currentDataPoint.valueLed_auto_OnOff)
        {
          //user handle
		  auto_flag=1;
        }
        else
        {
          //user handle    
		  auto_flag=0;
        }
        break;
      case EVENT_switch1:
        currentDataPoint.valueswitch1 = dataPointPtr->valueswitch1;
        GIZWITS_LOG("Evt: EVENT_switch1 %d \n", currentDataPoint.valueswitch1);
	  	go_gui_flag = 6;
        if(0x01 == currentDataPoint.valueswitch1)
        {
          //user handle
			//init the alarm time 	
			timearrge = mktime(gizwitsProtocol.TimeNTP.year,gizwitsProtocol.TimeNTP.month,gizwitsProtocol.TimeNTP.day,gizwitsProtocol.TimeNTP.hour,gizwitsProtocol.TimeNTP.minute,gizwitsProtocol.TimeNTP.second);
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch2:
        currentDataPoint.valueswitch2 = dataPointPtr->valueswitch2;
        GIZWITS_LOG("Evt: EVENT_switch2 %d \n", currentDataPoint.valueswitch2);
	  	go_gui_flag = 7;
        if(0x01 == currentDataPoint.valueswitch2)
        {
          //user handle
			scree_close = 1;
        }
        else
        {
          //user handle 
			scree_close = 0;			
        }
        break;
      case EVENT_switch3:
        currentDataPoint.valueswitch3 = dataPointPtr->valueswitch3;
        GIZWITS_LOG("Evt: EVENT_switch3 %d \n", currentDataPoint.valueswitch3);
        if(0x01 == currentDataPoint.valueswitch3)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch4:
        currentDataPoint.valueswitch4 = dataPointPtr->valueswitch4;
        GIZWITS_LOG("Evt: EVENT_switch4 %d \n", currentDataPoint.valueswitch4);
        if(0x01 == currentDataPoint.valueswitch4)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_switch5:
        currentDataPoint.valueswitch5 = dataPointPtr->valueswitch5;
        GIZWITS_LOG("Evt: EVENT_switch5 %d \n", currentDataPoint.valueswitch5);
        if(0x01 == currentDataPoint.valueswitch5)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;

      case EVENT_enum:
        currentDataPoint.valueenum = dataPointPtr->valueenum;
        GIZWITS_LOG("Evt: EVENT_enum %d\n", currentDataPoint.valueenum);
        switch(currentDataPoint.valueenum)
        {
          case enum_VALUE0:
            //user handle
            break;
          case enum_VALUE1:
            //user handle
            break;
          case enum_VALUE2:
            //user handle
            break;
          default:
            break;
        }
        break;

      case EVENT_Led_T:
        currentDataPoint.valueLed_T = dataPointPtr->valueLed_T;
        GIZWITS_LOG("Evt:EVENT_Led_T %d\n",currentDataPoint.valueLed_T);
        //user handle
		go_gui_flag=1;
        break;
      case EVENT_Led_S:
        currentDataPoint.valueLed_S = dataPointPtr->valueLed_S;
        GIZWITS_LOG("Evt:EVENT_Led_S %d\n",currentDataPoint.valueLed_S);
        //user handle
		go_gui_flag=1;
        break;
      case EVENT_R_value:
        currentDataPoint.valueR_value = dataPointPtr->valueR_value;
        GIZWITS_LOG("Evt:EVENT_R_value %d\n",currentDataPoint.valueR_value);
        //user handle
	  go_gui_flag=1;
		R_flag=1;
        break;
      case EVENT_G_value:
        currentDataPoint.valueG_value = dataPointPtr->valueG_value;
        GIZWITS_LOG("Evt:EVENT_G_value %d\n",currentDataPoint.valueG_value);
        //user handle
	  go_gui_flag=1;
	    G_flag=1;
        break;
      case EVENT_B_value:
        currentDataPoint.valueB_value = dataPointPtr->valueB_value;
        GIZWITS_LOG("Evt:EVENT_B_value %d\n",currentDataPoint.valueB_value);
        //user handle
	  go_gui_flag=1;
	    B_flag=1;
        break;
      case EVENT_Led_T_consequent:
        currentDataPoint.valueLed_T_consequent = dataPointPtr->valueLed_T_consequent;
        GIZWITS_LOG("Evt:EVENT_Led_T_consequent %d\n",currentDataPoint.valueLed_T_consequent);
        //user handle
		go_gui_flag=1;
        break;
      case EVENT_Posture_first1:
        currentDataPoint.valuePosture_first1 = dataPointPtr->valuePosture_first1;
        GIZWITS_LOG("Evt:EVENT_Posture_first1 %d\n",currentDataPoint.valuePosture_first1);
        //user handle
		go_gui_flag=3;
        break;
      case EVENT_Posture_first2:
        currentDataPoint.valuePosture_first2 = dataPointPtr->valuePosture_first2;
        GIZWITS_LOG("Evt:EVENT_Posture_first2 %d\n",currentDataPoint.valuePosture_first2);
        //user handle
			go_gui_flag=3;
        break;
      case EVENT_Posture_first3:
        currentDataPoint.valuePosture_first3 = dataPointPtr->valuePosture_first3;
        GIZWITS_LOG("Evt:EVENT_Posture_first3 %d\n",currentDataPoint.valuePosture_first3);
        //user handle
		go_gui_flag=3;
        break;
      case EVENT_Time_hour:
        currentDataPoint.valueTime_hour = dataPointPtr->valueTime_hour;
        GIZWITS_LOG("Evt:EVENT_Time_hour %d\n",currentDataPoint.valueTime_hour);
        //user handle
        break;
      case EVENT_Time_min:
        currentDataPoint.valueTime_min = dataPointPtr->valueTime_min;
        GIZWITS_LOG("Evt:EVENT_Time_min %d\n",currentDataPoint.valueTime_min);
        //user handle
        break;
      case EVENT_homework_distance:
        currentDataPoint.valuehomework_distance = dataPointPtr->valuehomework_distance;
        GIZWITS_LOG("Evt:EVENT_homework_distance %d\n",currentDataPoint.valuehomework_distance);
        //user handle
		go_gui_flag=2;
	  distance_flag=1;
        break;
      case EVENT_data1:
        currentDataPoint.valuedata1 = dataPointPtr->valuedata1;
        GIZWITS_LOG("Evt:EVENT_data1 %d\n",currentDataPoint.valuedata1);
        //user handle

        break;
      case EVENT_data2:
        currentDataPoint.valuedata2 = dataPointPtr->valuedata2;
        GIZWITS_LOG("Evt:EVENT_data2 %d\n",currentDataPoint.valuedata2);
        //user handle

        break;
      case EVENT_data3:
        currentDataPoint.valuedata3 = dataPointPtr->valuedata3;
        GIZWITS_LOG("Evt:EVENT_data3 %d\n",currentDataPoint.valuedata3);
        //user handle
        break;
      case EVENT_data4:
        currentDataPoint.valuedata4 = dataPointPtr->valuedata4;
        GIZWITS_LOG("Evt:EVENT_data4 %d\n",currentDataPoint.valuedata4);
        //user handle
        break;
      case EVENT_data5:
        currentDataPoint.valuedata5 = dataPointPtr->valuedata5;
        GIZWITS_LOG("Evt:EVENT_data5 %d\n",currentDataPoint.valuedata5);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:WIFI_ROUTER = 1;
 
        break;
      case WIFI_DISCON_ROUTER:WIFI_ROUTER = 0;
 
        break;
      case WIFI_CON_M2M:wifi_gizwit=1;
 
        break;
      case WIFI_DISCON_M2M:wifi_gizwit=0;//取消网络时钟
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
		if(ptime->year != 1970)PTIME_FLAG = 1;
		else PTIME_FLAG = 0;
		break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valuetemperature = ;//Add Sensor Data Collection
    currentDataPoint.valueHumidity = ;//Add Sensor Data Collection
    currentDataPoint.valueLed_auto_value = ;//Add Sensor Data Collection
    currentDataPoint.valueread1 = ;//Add Sensor Data Collection
    currentDataPoint.valueread2 = ;//Add Sensor Data Collection
    currentDataPoint.valueread3 = ;//Add Sensor Data Collection
    currentDataPoint.valueread4 = ;//Add Sensor Data Collection
    currentDataPoint.valueread5 = ;//Add Sensor Data Collection
    */
    

		if((gizGetTimerCount()-irLastTimer1 ) > 3000) ///以下代码每n秒执行一次
		{

			gizwitsGetNTP();//get net time 
			
			if(DHT11_init_flag==1)
			{
				currentDataPoint.valuetemperature= temperature;//Add Sensor Data Collection
				currentDataPoint.valueHumidity = humidity;//Add Sensor Data Collection
			}
			if(auto_flag==1)
			{
				currentDataPoint.valueLed_auto_value = auto_value;
			}
			
			
			irLastTimer1 = gizGetTimerCount();//reflash
		}
	
		if((WIFI_ROUTER == 1 || wifi_gizwit == 1 || PTIME_FLAG == 1))//联机标志
		{
			if(!scree_close)
			{
				if((showtime_flag == 0)&&((gizGetTimerCount()- irLastTimer2 )> currentDataPoint.valuedata2*1000))
				{
					go_gui_flag=5;//进入time_show
					showtime_flag=1;	//reflash  
					irLastTimer2 = gizGetTimerCount();//reflash
			
				}
				else if(showtime_flag == 1 && ((gizGetTimerCount()- irLastTimer2 )> 10*1000))
				{	
					irLastTimer2 = gizGetTimerCount();
				}
			}
			
			if(currentDataPoint.valueswitch1 == 0x01 && currentDataPoint.valuedata1 != 0)
			{
				if(((currentDataPoint.valuedata1)*60) < (mktime(gizwitsProtocol.TimeNTP.year,gizwitsProtocol.TimeNTP.month,gizwitsProtocol.TimeNTP.day,gizwitsProtocol.TimeNTP.hour,gizwitsProtocol.TimeNTP.minute,gizwitsProtocol.TimeNTP.second) \
					- timearrge)) 
				{	
					Uart4_Send(music02,6);
					printf("Please pay attention to rest.\r\n");
					timearrge = mktime(gizwitsProtocol.TimeNTP.year,gizwitsProtocol.TimeNTP.month,gizwitsProtocol.TimeNTP.day,gizwitsProtocol.TimeNTP.hour,gizwitsProtocol.TimeNTP.minute,gizwitsProtocol.TimeNTP.second);
					printf("Please pay:%u\r\n",timearrge);
				}
			}
		}
}

uint32_t mktime (uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec)
{
		if (0 >= (int) (mon -= 2)) 
		{    /* 1..12 -> 11,12,1..10 */
			 mon += 12;      /* Puts Feb last since it has leap day */
			 year -= 1;
		}

   return ((((uint32_t) (year/4 - year/100 + year/400 + 367*mon/12 + day) + year*365 - 719499)*24 + hour)*60 + min )*60 + sec; /* finally seconds */
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    currentDataPoint.valuedata2 = 30;
	currentDataPoint.valuedata1 = 45;
	currentDataPoint.valuePosture_first1 = 80;
    currentDataPoint.valuePosture_first2 = 80;
    currentDataPoint.valuePosture_first3 = 80;
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueLed_OnOff_Change = ;
      currentDataPoint.valueRed_OnOff = ;
      currentDataPoint.valueRGB_OnOff = ;
      currentDataPoint.valueLedT_C_OnOff = ;
      currentDataPoint.valuePosture_OnOff = ;
      currentDataPoint.valueTime_OnOff = ;
      currentDataPoint.valueHomework_OnOff = ;
      currentDataPoint.valueLed_auto_OnOff = ;
      currentDataPoint.valueswitch1 = ;
      currentDataPoint.valueswitch2 = ;
      currentDataPoint.valueswitch3 = ;
      currentDataPoint.valueswitch4 = ;
      currentDataPoint.valueswitch5 = ;
      currentDataPoint.valueenum = ;
      currentDataPoint.valueLed_T = ;
      currentDataPoint.valueLed_S = ;
      currentDataPoint.valueR_value = ;
      currentDataPoint.valueG_value = ;
      currentDataPoint.valueB_value = ;
      currentDataPoint.valueLed_T_consequent = ;
      currentDataPoint.valuePosture_first1 = ;
      currentDataPoint.valuePosture_first2 = ;
      currentDataPoint.valuePosture_first3 = ;
      currentDataPoint.valueTime_hour = ;
      currentDataPoint.valueTime_min = ;
      currentDataPoint.valuehomework_distance = ;
      currentDataPoint.valuedata1 = ;
      currentDataPoint.valuedata2 = ;
      currentDataPoint.valuedata3 = ;
      currentDataPoint.valuedata4 = ;
      currentDataPoint.valuedata5 = ;
      currentDataPoint.valuetemperature = ;
      currentDataPoint.valueHumidity = ;
      currentDataPoint.valueLed_auto_value = ;
      currentDataPoint.valueread1 = ;
      currentDataPoint.valueread2 = ;
      currentDataPoint.valueread3 = ;
      currentDataPoint.valueread4 = ;
      currentDataPoint.valueread5 = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
	__set_FAULTMASK(1);//关闭所有中断   //
	NVIC_SystemReset();//复位           //
}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
			USART_SendData(USART1,buf[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		
        if(i >=2 && buf[i] == 0xFF)
        {
		USART_SendData(USART1,0x55);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
          //Serial port to achieve the function, the 0x55 sent to the module
          //USART_SendData(UART, 0x55);//STM32 test demo
        }
    }


    
    return len;
}


