#ifndef _CONFIG_H
#define _CONFIG_H

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "ws2812.h"
#include "spi2.h"
#include "usart2.h"
#include "oled.h"
#include "myGUI.h"
#include "esp8266-ap.h"
#include "exti.h"
#include "usart3.h"
#include "usart4.h"
#include "gizwits_product.h"
#include "common.h"
#include "timer.h"
#include "dht11.h"
#include "bh1750.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "gizwits_protocol.h"

//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;	   
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define lcd_num 8
//#define JTAG_SWD_ENABLE    0X00	

extern u16 link_time;
extern char DHT11_init_flag;
extern u8 temperature, humidity;
extern char homework_flag, posture_flag, night_flag, cmd;
extern char go_gui_flag;
extern uint32_t irLastTimer2 ;


void All_Init(void);
void JTAG_Set(u8 mode);
void Gizwits_Init_1MS(void);
void Gizwit_Boot(void);
void Gizwit_boot_Menu(void);
void Communi_Interaction(void);
void Show_Time(u16 x,u16 y);
void Show_TH(char x, char y, u16 fc);
#endif

