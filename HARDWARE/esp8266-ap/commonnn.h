#ifndef __COMMONNN_H
#define __COMMONNN_H

#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "malloc.h"
#include "string.h" 	 	 	 	 	 
#include "usart2.h"

u8* atk_8266_check_cmd(u8 *str);
u8 atk_8266_send_data(u8 *data,u8 *ack,u16 waittime);
u8 atk_8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);

extern const u8* wifiap_ssid;		//WIFI AP SSID
//extern const u8* wifiap_encryption;	//WIFI AP º”√‹∑Ω Ω
extern const u8* wifiap_password; 	//WIFI AP √‹¬Î
#endif

