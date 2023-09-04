/**
  ******************************************************************************
  * @file    key.c
  * @author  fengwu yang
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   按键检测模板
  ******************************************************************************
  一,使用说明:检测引脚(PB5)
		1,把以下程序放在1ms定时器中断中
			if(KeySmartConfig[1])
				KeySmartConfig[5]++;
			else
				KeySmartConfig[5]=0;

			if(KeySmartConfig[2])
				KeySmartConfig[6]++;
			else
				KeySmartConfig[6]=0;
		
		2,主循环调用使用
			while(1)
			{
				SmartConfigKey();
				
				//例1:检测到按键按下执行某段代码
				if(KeySmartConfig[3] == 1)
				{
					KeySmartConfig[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
					//执行的代码
				}

				//例2:检测到按键按下,然后根据按下时间执行某段代码
				if(KeySmartConfig[3] == 1)
				{
					if(KeySmartConfig[5]>=3000)//按下时间大于3S
					{
						KeySmartConfig[3] = 0;//清零以后,只有按键松开再按下的时候才会进入
						//执行的代码
					}
				}
				
				//例3:检测到按键松开执行某段代码
				if(KeySmartConfig[4] == 1)
				{
					KeySmartConfig[4] = 0;//清零以后,只有按键按下然后松开的时候才会进入
					//执行的代码
				}
				
				//例4:检测到按键松开,然后根据松开时间执行某段代码
				if(KeySmartConfig[4] == 1)
				{
					if(KeySmartConfig[6]>=3000)//松开时间大于3S
					{
						KeySmartConfig[4] = 0;//清零以后,只有按键按下再松开的时候才会进入
						//执行的代码
					}
				}
			}
  ******************************************************************************
  */
#include "key.h"

int KeySmartConfig[7]={0};//消抖变量 按下标记 松开标记 按下标记拷贝  松开标记拷贝 按下时间(Ms) 松开时间(Ms)
Key_flag key_flag;
/**
* @brief  按键处理
* @param  
* @param  None
* @param  None
* @retval None
* @example 
**/
void SmartConfigKey(void)
{
	if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0)||!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5)||!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_8))
//  if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0)||!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5)||!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_7)||!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_8))
	{
		if(KeySmartConfig[1] == 0)
		{
			KeySmartConfig[0]++;
			if(KeySmartConfig[0]>=500)//按下以后进入
			{
				KeySmartConfig[0] = 0;//Cnt
				KeySmartConfig[2] = 0;//UP
				KeySmartConfig[1] = 1;//Down
				KeySmartConfig[3] = 1;//DownCopy
				KeySmartConfig[4] = 0;//UpCopy
			}
		}
	}
	else
	{
		KeySmartConfig[0]++;
		if(KeySmartConfig[0]>2000)
		{
			KeySmartConfig[0]=0;
			if(KeySmartConfig[1]==1)//按下后松开后进入
			{
				KeySmartConfig[2] = 1;//UP
				KeySmartConfig[1] = 0;//Down
				KeySmartConfig[3] = 0;//DownCopy
				KeySmartConfig[4] = 1;//UpCopy
			}
		}
	}
}



/*******************************************************************************
**函数名称：void Previous_setting_resume(uint8_t setting_index)
**功能描述：恢复上一个设置显示
**入口参数：
**输出：无
*******************************************************************************/
void Previous_setting_resume(uint8_t setting_index)
{
	switch(setting_index)
	{
		case 1:
			switch(menu.People_num)
		  {
				case 1:GUI_ShowCHinese(2,3,16,"一人",1);break;
				case 2:GUI_ShowCHinese(2,3,16,"二人",1);break;
				case 3:GUI_ShowCHinese(2,3,16,"三人",1);break;
				case 4:GUI_ShowCHinese(2,3,16,"四人",1);break;
				case 5:GUI_ShowCHinese(2,3,16,"五人",1);break;
				case 6:GUI_ShowCHinese(2,3,16,"六人",1);break;
				case 7:GUI_ShowCHinese(2,3,16,"七人",1);break;
				case 8:GUI_ShowCHinese(2,3,16,"八人",1);break;
				default:break;
		  }
			break;
		case 2:
			GUI_ShowNum(2,23,menu.Tickets_num_perperson.bai,1,16,1);                    //张/人     
	    GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,1);                    //张/人
	    GUI_ShowNum(2+16,23,menu.Tickets_num_perperson.ge,1,16,1);                    //张/人
	    GUI_ShowCHinese(2+24,23,16,"张",1);
			break;
		case 3:
			GUI_ShowNum(2,42,menu.Remain_num.bai,1,16,1);                        //底牌张数
			GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,1);                    //底牌张数
			GUI_ShowNum(2+16,42,menu.Remain_num.ge,1,16,1);                    //底牌张数
			GUI_ShowCHinese(2+24,42,16,"张",1);
			break;
		case 4:
			if(menu.Mode)
				GUI_ShowCHinese(WIDTH-2-24-32,3,16,"普通",1);
			else
				GUI_ShowCHinese(WIDTH-2-24-32,3,16,"特殊",1);
			break;
		case 5:
			GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num.bai,1,16,1);                         //连发张数
			GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,1);                    //连发张数
			GUI_ShowNum(WIDTH-2-24+16,23,menu.Send_continuously_num.ge,1,16,1);                      //连发张数
			GUI_ShowCHinese(WIDTH-2-24-32,23,16,"连发",1);
			break;
		case 6:
			if(menu.Direction)
		  GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"逆",1);
	    else
			GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"顺",1);
			GUI_ShowCHinese(WIDTH-2-24-32+16,23+3+16,16,"时针",1);
			break;
		default:break;
	}
}


/*******************************************************************************
**函数名称：void Value_setting(void)
**功能描述：对应设置参数更改
**入口参数：
**输出：无
*******************************************************************************/
void Value_setting(void)
{
	static uint8_t flag;
	switch(key_flag.setting_index)
	{
		case 1:
			if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0))       //如果为上选择键
			{
			 if(++menu.People_num>8)
				menu.People_num = 1;
			}
			else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5))
			{
			 if(--menu.People_num<1)
				menu.People_num = 8;
			}
	    break;
		case 2:
			if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0))     //上选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Tickets_num_perperson.ge++;
					if(menu.Tickets_num_perperson.ge>9)
						menu.Tickets_num_perperson.ge = 0;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Tickets_num_perperson.shi++;
					if(menu.Tickets_num_perperson.shi>9)
						menu.Tickets_num_perperson.shi = 0;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Tickets_num_perperson.bai++;
					if(menu.Tickets_num_perperson.bai>9)
						menu.Tickets_num_perperson.bai = 0;
				} 
			}
			else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5))     //下选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Tickets_num_perperson.ge--;
					if(flag)
					{
						menu.Tickets_num_perperson.ge = 9;
						flag = 0;
					}
					if(menu.Tickets_num_perperson.ge==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Tickets_num_perperson.shi--;
					if(flag)
					{
						menu.Tickets_num_perperson.shi = 9;
						flag = 0;
					}
					if(menu.Tickets_num_perperson.shi==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Tickets_num_perperson.bai--;
					if(flag)
					{
						menu.Tickets_num_perperson.bai = 9;
						flag = 0;
					}
					if(menu.Tickets_num_perperson.bai==0)
						flag = 1;
				} 
			}
		break;
		case 3:
			if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0))     //上选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Remain_num.ge++;
					if(menu.Remain_num.ge>9)
						menu.Remain_num.ge = 0;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Remain_num.shi++;
					if(menu.Remain_num.shi>9)
						menu.Remain_num.shi = 0;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Remain_num.bai++;
					if(menu.Remain_num.bai>9)
						menu.Remain_num.bai = 0;
				} 
			}
			else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5))     //下选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Remain_num.ge--;
					if(flag)
					{
						menu.Remain_num.ge = 9;
						flag = 0;
					}
					if(menu.Remain_num.ge==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Remain_num.shi--;
					if(flag)
					{
						menu.Remain_num.shi = 9;
						flag = 0;
					}
					if(menu.Remain_num.shi==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Remain_num.bai--;
					if(flag)
					{
						menu.Remain_num.bai = 9;
						flag = 0;
					}
					if(menu.Remain_num.bai==0)
						flag = 1;
				} 
			}
			break;
		case 4:
			if(menu.Mode)
				menu.Mode = 0;
			else
				menu.Mode =1;
			break;
		case 5:
			if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0))     //上选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Send_continuously_num.ge++;
					if(menu.Send_continuously_num.ge>9)
						menu.Send_continuously_num.ge = 0;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Send_continuously_num.shi++;
					if(menu.Send_continuously_num.shi>9)
						menu.Send_continuously_num.shi = 0;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Send_continuously_num.bai++;
					if(menu.Send_continuously_num.bai>9)
						menu.Send_continuously_num.bai = 0;
				} 
			}
			else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5))     //下选择犍
			{
				if(key_flag.key_ok == 2)
				{
					menu.Send_continuously_num.ge--;
					if(flag)
					{
						menu.Send_continuously_num.ge = 9;
						flag = 0;
					}
					if(menu.Send_continuously_num.ge==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 3)
				{
					menu.Send_continuously_num.shi--;
					if(flag)
					{
						menu.Send_continuously_num.shi = 9;
						flag = 0;
					}
					if(menu.Send_continuously_num.shi==0)
						flag = 1;
				} 
				else if(key_flag.key_ok == 4)
				{
					menu.Send_continuously_num.bai--;
					if(flag)
					{
						menu.Send_continuously_num.bai = 9;
						flag = 0;
					}
					if(menu.Send_continuously_num.bai==0)
						flag = 1;
				} 
			}
			break;
		case 6:
			if(menu.Direction)
				menu.Direction = 0;
			else
				menu.Direction =1;
			break;
		default:break;
	}
}


void Key_Pro(void)
{
	if(KeySmartConfig[3] == 1)     //按键按下就执行
	{
		KeySmartConfig[3] = 0;
		
    if(!GPIO_ReadInputDataBit(GPIOD,GPIO_PIN_0))      //上选择健
		{
			if(key_flag.key_ok==1)
			{
			  Previous_setting_resume(key_flag.setting_index);         //恢复上一次设置光标位置
			  if(--key_flag.setting_index < 1)
			  key_flag.setting_index = 6;	
			}
			else if(key_flag.key_ok==0 || key_flag.key_ok==2 || key_flag.key_ok==3 || key_flag.key_ok==4)
				Value_setting();               //设置参数值
		}
		else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_5))                 //下选择犍
		{
			Previous_setting_resume(key_flag.setting_index);         
			if(key_flag.key_ok==1)
			{
			 if(++key_flag.setting_index > 6)
			  key_flag.setting_index = 1;	
			}
			else if(key_flag.key_ok==0 || key_flag.key_ok==2 || key_flag.key_ok==3 || key_flag.key_ok==4)
				Value_setting();               //设置参数值
		}
		else if(!GPIO_ReadInputDataBit(GPIOB,GPIO_PIN_8))                   //OK犍
		{
			if(key_flag.setting_index==2 || key_flag.setting_index==3 || key_flag.setting_index==5)
			{
				if(++key_flag.key_ok>4)           //1-4:四种状态
					key_flag.key_ok = 1;
			}
			else
			{
				if(key_flag.key_ok==1)
					key_flag.key_ok = 0;
				else if(!key_flag.key_ok)
					key_flag.key_ok =1;
			}
		}
	}
}