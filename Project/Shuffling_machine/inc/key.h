#ifndef __KEY_H_
#define __KEY_H_
#include "main.h"

#define KeySmartConfigDown 0  //0- 低电平认为是按下  1-高电平认为是松开

#define SmartConfigKeyPinIn PBin(5)  //检测的按键引脚



typedef struct
{
	uint8_t key_ok;                         //1：ok，当前设置状态
	uint8_t setting_index;                 //1-6,当前光标位置
	uint8_t power_on;                      //1:开机
	
}Key_flag;

extern Key_flag key_flag;
extern int KeySmartConfig[7];//消抖变量 按下标记 松开标记 按下标记拷贝  松开标记拷贝 按下时间(Ms) 松开时间(Ms)
void SmartConfigKey(void);
void Key_Pro(void);
void Value_setting(void);

#endif
