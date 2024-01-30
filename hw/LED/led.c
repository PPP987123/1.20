#include "led.h"  
#include "delay.h"
#include "string.h"
#include "stdlib.h"

extern void led_out_gpio(uint8_t arg_int, int led_n);
extern uint8_t led_in_gpio(int led_n);

void led_set_level(pLED_Class pthis,const int led_n,const led_bit led_level);
void led_set_level_arr(pLED_Class pthis,const led_bits led_sta);

/*********************
无参构造
*********************/
pLED_Class createLedClass(void){
	pLED_Class led_c = (pLED_Class)malloc(sizeof(LED_Class));//malloc分配内存空间
	
	if(led_c == NULL){				//防止出现野指针
		return NULL;
	}
	led_c ->led_amount = 0;
	led_c ->led_curent_level = (led_bits)0;   
	led_c ->set_level = led_set_level;   		//设置单个LED状态
	led_c ->set_level_arr = led_set_level_arr; 	//设置多个LED状态
	led_c ->set_level_arr(led_c,(led_bits)0x00);
	
	return led_c;
}
/*********************
有参构造
*********************/
pLED_Class createLedClassWtihArgs(int led_amount){
	pLED_Class led_c = createLedClass();
	if(led_c == NULL){				//防止出现野指针
		return NULL;
	}
	led_c ->led_amount = led_amount;
}

void led_set_level(pLED_Class pthis,const int led_n,const led_bit led_level){	//pLED_Class pthis传递类指针
	led_out_gpio((uint8_t)led_level,led_n);										//led_n某一位的LED，led_level电平
	//
	pthis ->led_curent_level &= ~(0x1 << led_n);								//将第n位LED清0
	pthis ->led_curent_level |= (led_level << led_n);							//将led_level左移n位后的值 或 led_curent_level
}

void led_set_level_arr(pLED_Class pthis, const led_bits led_sta){				//多位写
	for(int i=0;i < pthis -> led_amount;++i){                                   //使用循环修改LED每次闪烁的状态（位操作）
		led_out_gpio((uint8_t)(led_sta >> i)&1,i);
	}
	pthis -> led_curent_level = led_sta;
}


