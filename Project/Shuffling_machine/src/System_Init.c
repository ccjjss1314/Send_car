#include "System_Init.h"
unsigned long time_delay = 0;
uint8_t blink_Flag = 0;



/*******************************************************************************
**�������ƣ�void RCC_Configuration(void)
**����������ϵͳͨ��ʱ�ӳ�ʼ��
**��ڲ�����
**�������
*******************************************************************************/
void RCC_Configuration(void)
{
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD| RCC_APB2_PERIPH_AFIO, ENABLE);
	  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
	  RCC_ConfigPclk1(RCC_HCLK_DIV4);   // PCLK1 = HCLK/4  ( for TIM6)
	  RCC_ConfigPclk2(RCC_HCLK_DIV2);   //(for SPI)
}

/*******************************************************************************
**�������ƣ�void GPIO_Configuration(void)
**����������ϵͳͨ��IO�ڳ�ʼ��
**��ڲ�����
**�������
*******************************************************************************/
void GPIO_Configuration(void)
{
		GPIO_InitType GPIO_InitStructure;
	
	 GPIO_InitStructure.Pin        = GPIO_PIN_2|GPIO_PIN_4;
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	  //PD8: RST��λ�ź�
	  GPIO_InitStructure.Pin        = GPIO_PIN_8;
	  GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
	 
	
	//����
	 GPIO_InitStructure.Pin        = GPIO_PIN_0;
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	 GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
	 GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
	
	 GPIO_InitStructure.Pin        = GPIO_PIN_5 | GPIO_PIN_8;
	 GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	
}






/*******************************************************************************
**�������ƣ�Pro_100ms
**����������100���봦���� 

*********************************************************************************/
void Pro_50ms(void)
{
	static uint8_t cnt_50ms;
	Flag_50ms=0;
	
	
	Updata_Mainpage();
	
	if(++cnt_50ms>4)
	{
		cnt_50ms=0;
		Flag_250ms = 1;
	}
}






/*******************************************************************************
**�������ƣ�Pro_100ms
**����������100���봦���� 

*********************************************************************************/
void Pro_250ms(void)
{
	static uint8_t cnt_250ms;
	Flag_250ms=0;
	
	
	blink_Flag = ~blink_Flag;
//  Set_current_position(Setting_index);
	

	
	if(++cnt_250ms>1)
	{
		cnt_250ms=0;
		Flag_500ms = 1;
	}
}


/*******************************************************************************
**�������ƣ�Pro_500ms
**����������500���봦���� 

*********************************************************************************/		
void Pro_500ms(void)
{
	static uint8_t cnt_500ms;	
  Flag_500ms=0;
	
	

	
	
		if(++cnt_500ms>1)
	  {
	    cnt_500ms=0;
		  Flag_1s = 1;
	  }
}


/*******************************************************************************
**�������ƣ�Pro_1s
**����������1�봦���� 

*********************************************************************************/		

void Pro_1s(void)
{
	static uint8_t cnt_1s;
	Flag_1s=0;
	

}



/*******************************************************************************
**�������ƣ�void SystemInit(void)
**����������ϵͳ��ʼ��
**��ڲ�����
**�������
*******************************************************************************/
void UserSystemInit(void)
{	
	 RCC_Configuration();
	 GPIO_Configuration(); 
	 log_init();
   Timer6_Init(); 
   OLED_Init();	
}


