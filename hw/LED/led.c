#include "led.h"  
#include "delay.h"
#include "string.h"
#include "stdlib.h"

extern void led_out_gpio(uint8_t arg_int, int led_n);
extern uint8_t led_in_gpio(int led_n);

void led_set_level(pLED_Class pthis,const int led_n,const led_bit led_level);
void led_set_level_arr(pLED_Class pthis,const led_bits led_sta);

pLED_Class createLedClass(void){
	pLED_Class led_c = (pLED_Class)malloc(sizeof(LED_Class));
	
	if(led_c == NULL){				
		return NULL;
	}
	led_c ->led_amount = 0;
	led_c ->led_curent_level = (led_bits)0;   
	led_c ->set_level = led_set_level;   		
	led_c ->set_level_arr = led_set_level_arr; 	
	led_c ->set_level_arr(led_c,(led_bits)0x00);
	
	return led_c;
}

pLED_Class createLedClassWtihArgs(int led_amount){
	pLED_Class led_c = createLedClass();
	if(led_c == NULL){				
		return NULL;
	}
	led_c ->led_amount = led_amount;
}

void led_set_level(pLED_Class pthis,const int led_n,const led_bit led_level){	//pLED_Class pthis传递类指针
	led_out_gpio((uint8_t)led_level,led_n);										
	//
	pthis ->led_curent_level &= ~(0x1 << led_n);								
	pthis ->led_curent_level |= (led_level << led_n);							
}

void led_set_level_arr(pLED_Class pthis, const led_bits led_sta){				
	for(int i=0;i < pthis -> led_amount;++i){                                 
		led_out_gpio((uint8_t)(led_sta >> i)&1,i);
	}
	pthis -> led_curent_level = led_sta;
}


