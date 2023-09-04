#include "timer.h"
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t CCR1_Val       = 2000;
uint16_t CCR2_Val       = 249;
//uint16_t Period         = 3000;
uint16_t PrescalerValue = 11;






/*******************************************************************************
**函数名称：void Timer6_Init(void)
**功能描述：
**入口参数：
**输出：无
*******************************************************************************/
void Timer6_Init(void)
{
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
	
	  NVIC_InitType NVIC_InitStructure;
	  TIM_TimeBaseInitType TIM_TimeBaseStructure;
	
    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 35999;                 //1ms
    TIM_TimeBaseStructure.Prescaler = 1;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);
		
    TIM_ConfigPrescaler(TIM6, 1, TIM_PSC_RELOAD_MODE_IMMEDIATE);
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);
    TIM_Enable(TIM6, ENABLE);
	

	  NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************
**函数名称：void Timer8_Init(void)
**功能描述：PWM输出
**入口参数：
**输出：无
*******************************************************************************/
void Timer8_Init(void)
{
	 RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8,ENABLE);
	
	 GPIO_InitType GPIO_InitStructure;
	 TIM_TimeBaseInitType TIM_TimeBaseStructure;
   OCInitType TIM_OCInitStructure;

	 GPIO_InitStructure.Pin        = GPIO_PIN_6;
	 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

	 GPIO_InitStructure.Pin = GPIO_PIN_7;
	 GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
    /* Time base configuration */
    TIM_TimeBaseStructure.Period    = 5999;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM8, &TIM_TimeBaseStructure);

    /* PWM2 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
		TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = CCR1_Val;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
		TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
		TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
		
    TIM_InitOc1(TIM8, &TIM_OCInitStructure);
		TIM_ConfigOc1Preload(TIM8, TIM_OC_PRE_LOAD_ENABLE);                 //启用CCR1寄存器的影子寄存器（直到产生更新事件才更改设置）
//		TIM_ConfigArPreload(TIM8, ENABLE);
		
		//死区设置
    TIM_BDTRInitStructure.OssrState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OssiState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LockLevel       = TIM_LOCK_LEVEL_1;
    TIM_BDTRInitStructure.DeadTime        = 11;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
		
		TIM_ConfigBkdt(TIM8, &TIM_BDTRInitStructure);
		
		TIM_Enable(TIM8, ENABLE);
		/* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM8, ENABLE);                              //开启互补输出时使能





//			TIM3->AR = Period;                          //设置PWM频率
//			  CCR1_Val += 10;
//			  TIM_SetCmp1(TIM8,CCR1_Val);                //设置PWM占空比
//			  systick_delay_ms(1000);





//    TIM_ConfigOc1Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel2 */
//    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
//    TIM_OCInitStructure.Pulse       = CCR2_Val;

//    TIM_InitOc2(TIM3, &TIM_OCInitStructure);

//    TIM_ConfigOc2Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);
	

//    TIM_ConfigArPreload(TIM3, ENABLE);
    /* TIM3 enable counter */
//    TIM_Enable(TIM3, ENABLE);

}