/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
/** @addtogroup TIM_PWM_Output
 * @{
 */


/**
 * @brief  Main program
 */
int main(void)
{
    NVIC_SetPriority(SysTick_IRQn, 0x0);
    UserSystemInit();
	  DumpClock("After reset");   
    key_flag.setting_index = 1;	 //���ó�ʼ���Ϊ1
    TEST_BMP();
  	Init_MainPage();         //�������ʼ��
	  
	  menu.People_num = 4;
    while (1)
    {
		 //����ɨ�账��
		 SmartConfigKey();
		 Key_Pro();
//		Test_Color();            //ˢ������
//		Test_Rectangular();      //���λ��Ʋ���
//		Test_Circle();           //Բ�λ��Ʋ���
//		Test_Triangle();         //�����λ��Ʋ���
//		TEST_English();          //Ӣ����ʾ����
//		TEST_Number_Character(); //���ֺͷ�����ʾ����
//		TEST_Chinese();          //������ʾ����
//		TEST_BMP();              //BMP��ɫͼƬ��ʾ����
//		TEST_Menu1();            //�˵�1��ʾ����
//		TEST_Menu2();            //�˵�2��ʾ����
     
			if(Flag_50ms)                  Pro_50ms();
			if(Flag_250ms)                 Pro_250ms();
			if(Flag_500ms)                 Pro_500ms();
			if(Flag_1s)                    Pro_1s();
    }
}



#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */
