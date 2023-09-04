#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__
#include "main.h"


#define Motor_advance()   		GPIO_ResetBits(GPIOA,GPIO_PIN_4);\
                              GPIO_SetBits(GPIOA,GPIO_PIN_2);  

#define Motor_back()  	    	GPIO_SetBits(GPIOA,GPIO_PIN_4);\
                              GPIO_ResetBits(GPIOA,GPIO_PIN_2);
															
#define Motor_brake()  	    	GPIO_ResetBits(GPIOA,GPIO_PIN_4);\
                              GPIO_ResetBits(GPIOA,GPIO_PIN_2);

extern uint8_t blink_Flag;
extern uint8_t Setting_index;
extern unsigned long time_delay;
void UserSystemInit(void);
void GPIO_Configuration(void);

void Pro_10ms(void);
void Pro_50ms(void);
void Pro_250ms(void);
void Pro_250ms(void);
void Pro_500ms(void);
void Pro_1s(void);


#endif /* __SYSTEM_INIT_H__ */