#include "System_Init.h"
unsigned long time_delay = 0;
uint8_t blink_Flag = 0;



/*******************************************************************************
**函数名称：void RCC_Configuration(void)
**功能描述：系统通用时钟初始化
**入口参数：
**输出：无
*******************************************************************************/
void RCC_Configuration(void)
{
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD| RCC_APB2_PERIPH_AFIO, ENABLE);
	  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
	  RCC_ConfigPclk1(RCC_HCLK_DIV4);   // PCLK1 = HCLK/4  ( for TIM6)
	  RCC_ConfigPclk2(RCC_HCLK_DIV2);   //(for SPI)
}

/*******************************************************************************
**函数名称：void GPIO_Configuration(void)
**功能描述：系统通用IO口初始化
**入口参数：
**输出：无
*******************************************************************************/
void GPIO_Configuration(void)
{
		GPIO_InitType GPIO_InitStructure;
	
	 GPIO_InitStructure.Pin        = GPIO_PIN_2|GPIO_PIN_4;
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	  //PD8: RST复位信号
	  GPIO_InitStructure.Pin        = GPIO_PIN_8;
	  GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
	 
	
	//按键
	 GPIO_InitStructure.Pin        = GPIO_PIN_0;
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	 GPIO_InitStructure.GPIO_Speed = GPIO_INPUT;
	 GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
	
	 GPIO_InitStructure.Pin        = GPIO_PIN_5 | GPIO_PIN_8;
	 GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	
}






/*******************************************************************************
**函数名称：Pro_100ms
**功能描述：100毫秒处理函数 

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
**函数名称：Pro_100ms
**功能描述：100毫秒处理函数 

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
**函数名称：Pro_500ms
**功能描述：500毫秒处理函数 

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
**函数名称：Pro_1s
**功能描述：1秒处理函数 

*********************************************************************************/		

void Pro_1s(void)
{
	static uint8_t cnt_1s;
	Flag_1s=0;
	

}



/*******************************************************************************
**函数名称：void SystemInit(void)
**功能描述：系统初始化
**入口参数：
**输出：无
*******************************************************************************/
void UserSystemInit(void)
{	
	 RCC_Configuration();
	 GPIO_Configuration(); 
	 log_init();
   Timer6_Init(); 
   OLED_Init();	
}


