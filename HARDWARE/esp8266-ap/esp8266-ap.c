#include "esp8266-ap.h"
#include "malloc.h"
#include "stdlib.h"
#include "led.h"
#include "string.h"
#include "commonnn.h"
#include "malloc.h"
#include "led.h"

void open_ap()
{
	
	u8 *p;
	p=mymalloc(64);
	
	printf("000");
	atk_8266_send_cmd("AT+CWMODE=2","OK",50);		//设置WIFI AP模式
	//atk_8266_send_cmd("AT+RST","OK",20);		//DHCP服务器关闭(仅AP模式有效) 
	delay_ms(50);         //延时3S等待重启成功

	//设置开启的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+CWSAP_DEF=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);  //设置无线参数:ssid,密码，通道，加密方式
	printf("111");
	atk_8266_send_cmd(p,"OK",200);
	myfree(p);
	printf("222");
}



