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
	atk_8266_send_cmd("AT+CWMODE=2","OK",50);		//����WIFI APģʽ
	//atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(50);         //��ʱ3S�ȴ������ɹ�

	//���ÿ�����WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWSAP_DEF=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);  //�������߲���:ssid,���룬ͨ�������ܷ�ʽ
	printf("111");
	atk_8266_send_cmd(p,"OK",200);
	myfree(p);
	printf("222");
}



