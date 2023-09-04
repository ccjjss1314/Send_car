#ifndef __KEY_H_
#define __KEY_H_
#include "main.h"

#define KeySmartConfigDown 0  //0- �͵�ƽ��Ϊ�ǰ���  1-�ߵ�ƽ��Ϊ���ɿ�

#define SmartConfigKeyPinIn PBin(5)  //���İ�������



typedef struct
{
	uint8_t key_ok;                         //1��ok����ǰ����״̬
	uint8_t setting_index;                 //1-6,��ǰ���λ��
	uint8_t power_on;                      //1:����
	
}Key_flag;

extern Key_flag key_flag;
extern int KeySmartConfig[7];//�������� ���±�� �ɿ���� ���±�ǿ���  �ɿ���ǿ��� ����ʱ��(Ms) �ɿ�ʱ��(Ms)
void SmartConfigKey(void);
void Key_Pro(void);
void Value_setting(void);

#endif
