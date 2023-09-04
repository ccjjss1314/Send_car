#include "oled.h"
#include "bmp.h"
static unsigned char OLED_buffer[1024] = {0};

Mode_menu_setting menu;
Setting_condition Setting;



uint8_t SPI_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                            0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                            0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};





/****************************************************************************************************
//=========================================电源接线================================================//
//   VCC         接       DC 5V/3.3V      //OLED屏电源正
//   GND         接          GND          //OLED屏电源地
//=======================================液晶屏数据线接线==========================================//
//   D1          接          PB15        //OLED屏SPI写信号
//=======================================液晶屏控制线接线==========================================//
//   CS          接          PB12       //OLED屏片选控制信号
//   RES         接          PD8        //OLED屏复位控制信号
//   DC          接          PB14        //OLED屏数据/命令选择控制信号-MISO
//   D0          接          PB13        //OLED屏SPI时钟信号
****************************************************************************************************/	

/*******************************************************************************
**函数名称：void OLED_SPI_GPIO_Init(void)
**功能描述：
**入口参数：
**输出：无
*******************************************************************************/
void OLED_SPI2_GPIO_Init(void)
{
		RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);   //SPI-DMA  
		RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE); 

		GPIO_InitType GPIO_InitStructure;
    SPI_InitType SPI_InitStructure;
    DMA_InitType DMA_InitStructure;
	  
	  //PB12:NSS       PB13:CLK        PB15:MOSI          
//	  GPIO_InitStructure.Pin        = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
//    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
////	  DMA_DeInit(DMA1_CH5);
////    DMA_InitStructure.PeriphAddr     = (uint32_t)&SPI2->DAT;
////    DMA_InitStructure.MemAddr        = (uint32_t)OLED_buffer;
////    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;           //外设作为目的地
////    DMA_InitStructure.BufSize        = BufferSize;
////    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
////    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
////    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
////    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
////    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;            //循环发送
////    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
////    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
////    DMA_Init(DMA1_CH5, &DMA_InitStructure);
		
//		SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
//    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
//    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
//    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;                 //SPI_CPOL_High=模式3，时钟空闲为高 SPI_CPOL_Low=模式0，时钟空闲为低
//    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_FIRST_EDGE;           //第一个跳变沿采样，及上升沿采样
//    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
//    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;              //36/4 = 9MHz
//    SPI_InitStructure.FirstBit      = SPI_FB_MSB;                      //从MSB高位开始发送
//    SPI_InitStructure.CRCPoly       = 7;
//    SPI_Init(SPI2, &SPI_InitStructure);
		
//		SPI_SetNssLevel(SPI2,SPI_NSS_HIGH);
		/* Enable SPI_MASTER NSS output for master mode */
////    SPI_SSOutputEnable(SPI2, ENABLE);
////		SPI_I2S_EnableDma(SPI2,SPI_I2S_DMA_TX,ENABLE);
//		SPI_Enable(SPI2, ENABLE);
		
////		DMA_EnableChannel(DMA1_CH5, ENABLE);
		    /* Wait for DMA1 channel5 transfer complete */
////    while (!DMA_GetFlagStatus(DMA1_FLAG_TC5, DMA1));	

    GPIO_InitStructure.Pin        = GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_13 | GPIO_PIN_15;  //PB14:数据/命令选择
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOB,GPIO_PIN_12);
}





/*******************************************************************************
**函数名称：void OLED_GPIO_Init(void)
**功能描述：
**入口参数：
**输出：无
*******************************************************************************/
void OLED_GPIO_Init(void)
{
  	GPIO_InitType GPIO_InitStructure;
	  I2C_InitType I2C1_InitStructure;
	  NVIC_InitType NVIC_InitStructure;
	
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
#ifdef I2C1_REMAP
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_I2C1, ENABLE);
#endif
    /* PB6 -- SCL; PB7-- SDA*/
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    I2C_DeInit(I2C1);
    I2C1_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C1_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C1_InitStructure.OwnAddr1    = I2C1_MASTER_ADDR;
    I2C1_InitStructure.AckEnable   = I2C_ACKEN;
    I2C1_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C1_InitStructure.ClkSpeed    = 100000; // 100000 100K
    I2C_Init(I2C1, &I2C1_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;   //event中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;   //error中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
    // int enable
    I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    I2C_Enable(I2C1, ENABLE);
}

//OLED 复位
void OLED_Reset(void)
{
	OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
}





/*****************************************************************************
 * @name       :void SPI_WriteByte(u8 Data)
 * @date       :2018-08-27 
 * @function   :Write a byte of data using STM32's Software SPI
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/
void SPI_WriteByte(u8 Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
	  if(Data&0x80)	
		{
			GPIO_SetBits(GPIOB,GPIO_PIN_15);
    }
		else
		{
			GPIO_ResetBits(GPIOB,GPIO_PIN_15); //写数据0
	  }
    GPIO_ResetBits(GPIOB,GPIO_PIN_13);    //将时钟拉低拉高     
    GPIO_SetBits(GPIOB,GPIO_PIN_13);     //发送1bit数据
    Data<<=1; 
	}
}







/*******************************************************************************
**函数名称：void OLED_WR_Byte(unsigned dat,unsigned cmd)
**功能描述：
**入口参数：
**输出：无
*******************************************************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		OLED_DC_Set();
	}
	else
	{
		OLED_DC_Clr();
	}
	OLED_CS_Clr();
	SPI_WriteByte(dat);
//	SPI_I2S_TransmitData(SPI2,dat);
//  while (SPI_I2S_GetStatus(SPI2, SPI_I2S_TE_FLAG) == RESET);    //Wait for SPIy Tx buffer empty
	OLED_CS_Set();
}


/*******************************************************************************
**函数名称：void OLED_GPIO_Init(void)
**功能描述：
**入口参数：
**输出：无
*******************************************************************************/
void OLED_Init(void)
{
  OLED_SPI2_GPIO_Init();
  delay_ms(200);
	OLED_Reset();
	/**************初始化SSD1306*****************/	
	OLED_WR_Byte(0xAE,OLED_CMD); /*display off*/
	OLED_WR_Byte(0x00,OLED_CMD); /*set lower column address*/
	OLED_WR_Byte(0x10,OLED_CMD); /*set higher column address*/
	OLED_WR_Byte(0x40,OLED_CMD); /*set display start line*/ 
	OLED_WR_Byte(0xB0,OLED_CMD); /*set page address*/
	OLED_WR_Byte(0x81,OLED_CMD); /*contract control*/ 
	OLED_WR_Byte(0xFF,OLED_CMD); /*128*/
	OLED_WR_Byte(0xA1,OLED_CMD); /*set segment remap*/ 
	OLED_WR_Byte(0xA6,OLED_CMD); /*normal / reverse*/
	OLED_WR_Byte(0xA8,OLED_CMD); /*multiplex ratio*/ 
	OLED_WR_Byte(0x3F,OLED_CMD); /*duty = 1/64*/
	OLED_WR_Byte(0xC8,OLED_CMD); /*Com scan direction*/
	OLED_WR_Byte(0xD3,OLED_CMD); /*set display offset*/ 
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xD5,OLED_CMD); /*set osc division*/ 
	OLED_WR_Byte(0x80,OLED_CMD);
	OLED_WR_Byte(0xD9,OLED_CMD); /*set pre-charge period*/ 
	OLED_WR_Byte(0XF1,OLED_CMD);
	OLED_WR_Byte(0xDA,OLED_CMD); /*set COM pins*/ 
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD); /*set vcomh*/ 
	OLED_WR_Byte(0x30,OLED_CMD);
	OLED_WR_Byte(0x8D,OLED_CMD); /*set charge pump disable*/ 
	OLED_WR_Byte(0x14,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/

///**************初始化SSD1315BZ*****************/	
//	OLED_WR_Byte(0xAE,OLED_CMD); /*display off*/
//	OLED_WR_Byte(0xD5,OLED_CMD); /*set osc division / SET DISPLAY CLOCK*/ 
//	OLED_WR_Byte(0x80,OLED_CMD); /*105HZ*/
//  OLED_WR_Byte(0xA8,OLED_CMD); /*multiplex ratio*/ 
//	OLED_WR_Byte(0x3F,OLED_CMD); /*duty = 1/64 / Default => 0~0x3F (1/64 Duty)*/
//	OLED_WR_Byte(0xD3,OLED_CMD); /*set display offset*/ 
//	OLED_WR_Byte(0x00,OLED_CMD); /*set lower column address / 00H Reset,  set common start*/
//	OLED_WR_Byte(0x40,OLED_CMD); /*set display start line*/
//	OLED_WR_Byte(0x8D,OLED_CMD); /*set charge pump disable / Set Charge Pump*/ 
//	OLED_WR_Byte(0x14,OLED_CMD); /*Endable Charge Pump*/ 
//	OLED_WR_Byte(0xA1,OLED_CMD); //Set Segment Re-Map Default / 0xA0 (0x00) => column Address 0 mapped to 127 / 0xA1 (0x01) => Column Address 127 mapped to 0
//	//	Write_command(0xAD);  // Set Charge Pump
//  //	Write_command(0x30);  // Endable Charge Pump						              
//	OLED_WR_Byte(0xC8,OLED_CMD); /*Set COM Output Scan Direction / 0xC0	(0x00) => normal mode (RESET) Scan from COM0 to COM[N-1];Where N is the Multiplex ratio./ 
//	                                                               0xC8	(0xC8) => remapped mode. Scan from COM[N-1] to COM0;;Where N is the Multiplex ratio.*/
//	OLED_WR_Byte(0xDA,OLED_CMD); /*Set COM Hardware Configuration*/ 
//	OLED_WR_Byte(0x12,OLED_CMD);/*Alternative COM Pin---See IC Spec page 34 / (0x02)=> A4=0;Sequential COM pin configuration;A5=0;Disable COM Left/Right remap */
//	OLED_WR_Byte(0x81,OLED_CMD); /*Set Contrast Control*/ 
//	OLED_WR_Byte(0xCF,OLED_CMD);
//	OLED_WR_Byte(0xD9,OLED_CMD); /*set pre-charge period*/ 
//	OLED_WR_Byte(0XF1,OLED_CMD);
//	OLED_WR_Byte(0xDB,OLED_CMD); /*set vcomh / Set Deselect Vcomh level*/
//	OLED_WR_Byte(0x40,OLED_CMD);
//	OLED_WR_Byte(0xA4,OLED_CMD);//Entire Display ON
//	OLED_WR_Byte(0xA6,OLED_CMD); /*Set Normal Display*/
//	OLED_WR_Byte(0xAF,OLED_CMD); /*Display ON*/
}





/*******************************************************************
 * @name       :void OLED_Display(void)
 * @date       :2018-08-27
 * @function   :Display in OLED screen
 * @parameters :None
 * @retvalue   :None
********************************************************************/  
void OLED_Display(void)
{
	u8 i,n;		    
	for(i=0;i<PAGE_SIZE;i++)  
	{  
		OLED_WR_Byte (YLevel+i,OLED_CMD);     //设置页地址（0~7）
		OLED_WR_Byte (XLevelL,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (XLevelH,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<WIDTH;n++)
		{
			OLED_WR_Byte(OLED_buffer[i*WIDTH+n],OLED_DATA); 
		}
	}   //更新显示
}

void OLED_Fade_Display(void)
{
	u8 i,n;		    
	for(i=0;i<PAGE_SIZE;i++)  
	{  
		OLED_WR_Byte (YLevel+i,OLED_CMD);     //设置页地址（0~7）
		OLED_WR_Byte (XLevelL,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (XLevelH,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<WIDTH;n++)
		{
			OLED_WR_Byte(OLED_buffer[i*WIDTH+n],OLED_DATA); 
		}
		delay_ms(200);           //test
	}   //更新显示
}


/*******************************************************************
 * @name       :void OLED_Clear(unsigned dat)  
 * @date       :2018-08-27
 * @function   :clear OLED screen
 * @parameters :dat:0-Display full black
                    1-Display full white
 * @retvalue   :None
********************************************************************/ 
void OLED_Clear(unsigned dat)  
{  
	if(dat)
	{
		memset(OLED_buffer,0xff,sizeof(OLED_buffer));
	}
	else
	{
		memset(OLED_buffer,0,sizeof(OLED_buffer));
	}
	OLED_Display();
}





/*******************************************************************
 * @name       :void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color)
 * @date       :2018-08-27
 * @function   :set the value of pixel to RAM
 * @parameters :x:the x coordinates of pixel
                y:the y coordinates of pixel
								color:the color value of the point
								      1-white
											0-black
 * @retvalue   :None
********************************************************************/ 
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color)
{
	if(color)
	{
		OLED_buffer[(y/PAGE_SIZE)*WIDTH+x]|= (1<<(y%PAGE_SIZE))&0xff;
	}
	else
	{
		OLED_buffer[(y/PAGE_SIZE)*WIDTH+x]&= ~((1<<(y%PAGE_SIZE))&0xff);
	}
}		 


/*****************************************************************************
 * @name       :void TEST_MainPage(void)
 * @date       :2018-08-27 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Init_MainPage(void)
{	
	OLED_Clear(0);             //1:全白 0:全黑
	GUI_DrawLine(0, 0, WIDTH-1, 0,1);
	GUI_DrawLine(0, 0,0, HEIGHT-1,1);
	GUI_DrawLine(0, HEIGHT-1,WIDTH-1, HEIGHT-1,1);
	GUI_DrawLine(WIDTH-1, HEIGHT-1,WIDTH-1,0,1);
	/*****************第一列********************/
	switch(menu.People_num)
	{
		case 1:GUI_ShowCHinese(2,3,16,"一",1);break;
		case 2:GUI_ShowCHinese(2,3,16,"二",1);break;
		case 3:GUI_ShowCHinese(2,3,16,"三",1);break;
		case 4:GUI_ShowCHinese(2,3,16,"四",1);break;
		case 5:GUI_ShowCHinese(2,3,16,"五",1);break;
		case 6:GUI_ShowCHinese(2,3,16,"六",1);break;
		case 7:GUI_ShowCHinese(2,3,16,"七",1);break;
		case 8:GUI_ShowCHinese(2,3,16,"八",1);break;
		default:break;
	}
	GUI_ShowCHinese(2+16,3,16,"人",1);
  GUI_ShowNum(2,23,menu.Tickets_num_perperson.bai,1,16,1);                    //张/人     
	GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,1);                    //张/人
	GUI_ShowNum(2+16,23,menu.Tickets_num_perperson.ge,1,16,1);                    //张/人
	GUI_ShowCHinese(2+24,23,16,"张",1);
	
	GUI_ShowNum(2,42,menu.Remain_num.bai,1,16,1);                        //底牌张数
	GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,1);                    //底牌张数
	GUI_ShowNum(2+16,42,menu.Remain_num.ge,1,16,1);                    //底牌张数
	GUI_ShowCHinese(2+24,42,16,"张",1);
	/*****************第二列********************/
	GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num.bai,1,16,1);                         //连发张数
		GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,1);                    //连发张数
		GUI_ShowNum(WIDTH-2-24+16,23,menu.Send_continuously_num.ge,1,16,1);                      //连发张数
  GUI_ShowCHinese(WIDTH-2-24-32,23,16,"连发",1);
	
	if(menu.Direction)
		GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"逆",1);
	else
		GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"顺",1);
	GUI_ShowCHinese(WIDTH-2-24-32+16,23+3+16,16,"时针",1);
	if(menu.Mode)
		GUI_ShowCHinese(WIDTH-2-24-32,3,16,"普通",1);
	else
		GUI_ShowCHinese(WIDTH-2-24-32,3,16,"特殊",1);
}


/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-27 
 * @function   :Color fill test(white,black)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	 GUI_Fill(0,0,WIDTH-1,HEIGHT-1,0);
	 GUI_ShowString(10,10,"BLACK",16,1);
	 delay_ms(1000);	
	 GUI_Fill(0,0,WIDTH-1,HEIGHT-1,1);
	 delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Rectangular(void))
 * @date       :2018-08-27
 * @function   :Rectangular display and fill test
								Display black,white rectangular boxes in turn,1000 
								milliseconds later,Fill the rectangle in black,white in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Rectangular(void)
{
	GUI_Fill(0,0,WIDTH/2-1,HEIGHT-1,0);
	GUI_Fill(WIDTH/2,0,WIDTH-1,HEIGHT-1,1);
	GUI_DrawRectangle(5, 5, WIDTH/2-1-5, HEIGHT-1-5,1);
	GUI_DrawRectangle(WIDTH/2-1+5, 5, WIDTH-1-5, HEIGHT-1-5,0);
	delay_ms(1000);
	GUI_FillRectangle(5, 5, WIDTH/2-1-5, HEIGHT-1-5,1);
	GUI_FillRectangle(WIDTH/2-1+5, 5, WIDTH-1-5, HEIGHT-1-5,0);
	delay_ms(1500);
}


/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-27 
 * @function   :circular display and fill test
								Display black,white circular boxes in turn,1000 
								milliseconds later,Fill the circular in black,white in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	GUI_Fill(0,0,WIDTH/2-1,HEIGHT-1,0);
	GUI_Fill(WIDTH/2,0,WIDTH-1,HEIGHT-1,1);
	GUI_DrawCircle(WIDTH/2/2-1, HEIGHT/2-1, 1, 27);
	GUI_DrawCircle(WIDTH/2+WIDTH/2/2-1, HEIGHT/2-1, 0, 27);
	delay_ms(1000);
	GUI_FillCircle(WIDTH/2/2-1, HEIGHT/2-1, 1, 27);
	GUI_FillCircle(WIDTH/2+WIDTH/2/2-1, HEIGHT/2-1, 0, 27);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-27 
 * @function   :triangle display and fill test
								Display black,white triangle boxes in turn,1000 
								milliseconds later,Fill the triangle in black,white in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	GUI_Fill(0,0,WIDTH/2-1,HEIGHT-1,0);
	GUI_Fill(WIDTH/2,0,WIDTH-1,HEIGHT-1,1);
	GUI_DrawTriangel(5,HEIGHT-1-5,WIDTH/2/2-1,5,WIDTH/2-1-5,HEIGHT-1-5,1);
	GUI_DrawTriangel(WIDTH/2-1+5,HEIGHT-1-5,WIDTH/2+WIDTH/2/2-1,5,WIDTH-1-5,HEIGHT-1-5,0);
	delay_ms(1000);
	GUI_FillTriangel(5,HEIGHT-1-5,WIDTH/2/2-1,5,WIDTH/2-1-5,HEIGHT-1-5,1);
	GUI_FillTriangel(WIDTH/2-1+5,HEIGHT-1-5,WIDTH/2+WIDTH/2/2-1,5,WIDTH-1-5,HEIGHT-1-5,0);
	delay_ms(1500);
}


/*****************************************************************************
 * @name       :void TEST_English(void)
 * @date       :2018-08-27 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_English(void)
{
	GUI_ShowString(0,5,"6x8:abcdefghijklmnopqrstuvwxyz",8,1);
	GUI_ShowString(0,25,"8x16:abcdefghijklmnopqrstuvwxyz",16,1);
	delay_ms(1000);
	GUI_ShowString(0,5,"6x8:ABCDEFGHIJKLMNOPQRSTUVWXYZ",8,1);
	GUI_ShowString(0,25,"8x16:ABCDEFGHIJKLMNOPQRSTUVWXYZ",16,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_Number_Character(void) 
 * @date       :2018-08-27 
 * @function   :number and character display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_Number_Character(void) 
{
	GUI_Fill(0,0,WIDTH-1,HEIGHT/2-1,0);
	GUI_ShowString(0,0,"6x8:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",8,1);
	GUI_ShowNum(30,16,1234567890,10,8,1);
	delay_ms(1000);
//	OLED_Clear(0); 
  GUI_ShowString(0,0,"8x16:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",16,1);
	GUI_ShowNum(40,32,1234567890,10,16,1);
}

/*****************************************************************************
 * @name       :void TEST_Chinese(void)
 * @date       :2018-08-27
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_Chinese(void)
{	
	GUI_ShowString(45,0,"16x16",8,1);
	GUI_ShowCHinese(16,20,16,"全动电子技术",1);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowString(45,0,"24x24",8,1);
	GUI_ShowCHinese(16,20,24,"全动电子",1);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowString(45,0,"32x32",8,1);
	GUI_ShowCHinese(0,20,32,"全动电子",1);	
  delay_ms(1000);
	OLED_Clear(0);
}

/*****************************************************************************
 * @name       :void TEST_BMP(void)
 * @date       :2018-08-27 
 * @function   :BMP monochromatic picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_BMP(void)
{
	OLED_Clear(0);
	GUI_DrawBMP_fadeout(32,0,60,64, BMP2, 1);//VOGE图片
	delay_ms(1000);
}

/*****************************************************************************
 * @name       :void TEST_Menu1(void)
 * @date       :2018-08-27 
 * @function   :Chinese selection menu display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_Menu1(void)
{ 
	GUI_Fill(0,0,WIDTH-1,15,1);
	GUI_ShowCHinese(32,0,16,"系统设置",0);
	GUI_DrawCircle(10, 24, 1,6);
	GUI_DrawCircle(10, 24, 1,3);
	GUI_DrawCircle(10, 40, 1,6);
	GUI_DrawCircle(10, 40, 1,3);
	GUI_DrawCircle(10, 56, 1,6);
	GUI_DrawCircle(10, 56, 1,3);
	GUI_ShowString(20,16,"A.",16,1);
	GUI_ShowCHinese(36,16,16,"音量设置",1);
	GUI_ShowString(20,32,"B.",16,1);
	GUI_ShowCHinese(36,32,16,"颜色设置",1);
	GUI_ShowString(20,48,"C.",16,1);
	GUI_ShowCHinese(36,48,16,"网络设置",1);
	GUI_DrawRectangle(0, 0,WIDTH-1,HEIGHT-1,1);
	GUI_DrawLine(WIDTH-1-10, 15, WIDTH-1-10, HEIGHT-1,1);
	GUI_FillTriangel(WIDTH-1-9,20,WIDTH-1-5,16,WIDTH-1-1,20,1);
	GUI_FillTriangel(WIDTH-1-9,HEIGHT-1-5,WIDTH-1-5,HEIGHT-1-1,WIDTH-1-1,HEIGHT-1-5,1);
	GUI_FillCircle(10, 24, 1,3);
	GUI_Fill(20,16,99,31,1);
	GUI_ShowString(20,16,"A.",16,0);
	GUI_ShowCHinese(36,16,16,"音量设置",0);
	GUI_Fill(WIDTH-1-9,23,WIDTH-1-1,28,1);
	delay_ms(1500);
	GUI_FillCircle(10, 24, 0,3);
	GUI_DrawCircle(10, 24, 1,3);
	GUI_Fill(20,16,99,31,0);
	GUI_ShowString(20,16,"A.",16,1);
	GUI_ShowCHinese(36,16,16,"音量设置",1);
	GUI_Fill(WIDTH-1-9,23,WIDTH-1-1,28,0);
	GUI_FillCircle(10, 40, 1,3);
	GUI_Fill(20,32,99,47,1);
	GUI_ShowString(20,32,"B.",16,0);
	GUI_ShowCHinese(36,32,16,"颜色设置",0);
	GUI_Fill(WIDTH-1-9,37,WIDTH-1-1,42,1);
	delay_ms(1500);
	GUI_FillCircle(10, 40, 0,3);
	GUI_DrawCircle(10, 40, 1,3);
	GUI_Fill(20,32,99,47,0);
	GUI_ShowString(20,32,"B.",16,1);
	GUI_ShowCHinese(36,32,16,"颜色设置",1);
	GUI_Fill(WIDTH-1-9,37,WIDTH-1-1,42,0);
	GUI_FillCircle(10, 56, 1,3);
	GUI_Fill(20,48,99,63,1);
	GUI_ShowString(20,48,"C.",16,0);
	GUI_ShowCHinese(36,48,16,"网络设置",0);
	GUI_Fill(WIDTH-1-9,HEIGHT-1-13,WIDTH-1-1,HEIGHT-1-8,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_Menu2(void)
 * @date       :2018-08-27 
 * @function   :English weather interface display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TEST_Menu2(void)
{
	u8 i;
//	srand(123456);
//	GUI_DrawLine(0, 10, WIDTH-1, 10,1);
//	GUI_DrawLine(WIDTH/2-1,11,WIDTH/2-1,HEIGHT-1,1);
//	GUI_DrawLine(WIDTH/2-1,10+(HEIGHT-10)/2-1,WIDTH-1,10+(HEIGHT-10)/2-1,1);
//	GUI_ShowString(0,1,"2023-08-04",8,1);
//	GUI_ShowString(78,1,"Wensday",8,1);
//	GUI_ShowString(14,HEIGHT-1-10,"Cloudy",8,1);
//	GUI_ShowString(WIDTH/2-1+2,13,"TEMP",8,1);
//	GUI_DrawCircle(WIDTH-1-19, 25, 1,2);
//	GUI_ShowString(WIDTH-1-14,20,"C",16,1);
//	GUI_ShowString(WIDTH/2-1+9,20,"32.5",16,1);
//	GUI_ShowString(WIDTH/2-1+2,39,"PM2.5",8,1);
//	GUI_ShowString(WIDTH/2-1+5,46,"90ug/m3",16,1);
//	GUI_DrawBMP(6,16,51,32, BMP5, 1);
//	for(i=0;i<15;i++)
//	{
//		GUI_ShowNum(WIDTH/2-1+9,20,rand()%4,1,16,1);
//		GUI_ShowNum(WIDTH/2-1+9+8,20,rand()%10,1,16,1);
//		GUI_ShowNum(WIDTH/2-1+9+8+16,20,rand()%10,1,16,1);
//		GUI_ShowNum(WIDTH/2-1+5,46,rand()%10,1,16,1);
//		GUI_ShowNum(WIDTH/2-1+5+8,46,rand()%10,1,16,1);
//    delay_ms(500);	
//	}
}


/*******************************************************************************
**函数名称：void Updata_Mainpage(void)
**功能描述：主界面信息更新
**入口参数：
**输出：无
*******************************************************************************/

void Updata_Mainpage(void)
{
	if(key_flag.setting_index==1)                            //光标指向人数设置
	{
		if(key_flag.key_ok==0)                        //设置状态
		{
			switch(menu.People_num)
		  {
				case 1:GUI_ShowCHinese(2,3,16,"一人",blink_Flag);break;
				case 2:GUI_ShowCHinese(2,3,16,"二人",blink_Flag);break;
				case 3:GUI_ShowCHinese(2,3,16,"三人",blink_Flag);break;
				case 4:GUI_ShowCHinese(2,3,16,"四人",blink_Flag);break;
				case 5:GUI_ShowCHinese(2,3,16,"五人",blink_Flag);break;
				case 6:GUI_ShowCHinese(2,3,16,"六人",blink_Flag);break;
				case 7:GUI_ShowCHinese(2,3,16,"七人",blink_Flag);break;
				case 8:GUI_ShowCHinese(2,3,16,"八人",blink_Flag);break;
				default:break;
		  }
		}
		else if(key_flag.key_ok==1)                   //非设置状态
		{
			switch(menu.People_num)
		  {
				case 1:GUI_ShowCHinese(2,3,16,"一人",0);break;
				case 2:GUI_ShowCHinese(2,3,16,"二人",0);break;
				case 3:GUI_ShowCHinese(2,3,16,"三人",0);break;
				case 4:GUI_ShowCHinese(2,3,16,"四人",0);break;
				case 5:GUI_ShowCHinese(2,3,16,"五人",0);break;
				case 6:GUI_ShowCHinese(2,3,16,"六人",0);break;
				case 7:GUI_ShowCHinese(2,3,16,"七人",0);break;
				case 8:GUI_ShowCHinese(2,3,16,"八人",0);break;
				default:break;
		  }
		}
	}
	else if(key_flag.setting_index==2)//张/人 设置
	{
		switch(key_flag.key_ok)
		{
//			case 0:break;
			case 1:
				GUI_ShowNum(2,23,menu.Tickets_num_perperson.bai,1,16,0);                     //张/人     
	      GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,0);                    //张/人
	      GUI_ShowNum(2+16,23,menu.Tickets_num_perperson.ge,1,16,0);                    //张/人
	      GUI_ShowCHinese(2+24,23,16,"张",0);
				break;
			case 2:
				GUI_ShowNum(2+16,23,menu.Tickets_num_perperson.ge,1,16,blink_Flag);       //张/人,个位数字设置
			  GUI_ShowNum(2,23,menu.Tickets_num_perperson.bai,1,16,1);                     //张/人     
	      GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,1);                    //张/人
			  GUI_ShowCHinese(2+24,23,16,"张",1);
				break;
			case 3:
				GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,blink_Flag);       //张/人,十位数字设置
			  GUI_ShowNum(2+16,23,menu.Tickets_num_perperson.ge,1,16,1);                    //张/人
				break;
			case 4:
				GUI_ShowNum(2,23,menu.Tickets_num_perperson.bai,1,16,blink_Flag);       //张/人,百位数字设置
			  GUI_ShowNum(2+8,23,menu.Tickets_num_perperson.shi,1,16,1);                    //张/人
				break;
			default:break;
		}
	}
	else if(key_flag.setting_index==4)//模式设置
	{
		if(key_flag.key_ok==0)                        //设置状态
		{
			if(menu.Mode)
			GUI_ShowCHinese(WIDTH-2-24-32,3,16,"普通",blink_Flag);
		  else
			GUI_ShowCHinese(WIDTH-2-24-32,3,16,"特殊",blink_Flag);
		}
		else if(key_flag.key_ok==1)
		{
			if(menu.Mode)
			GUI_ShowCHinese(WIDTH-2-24-32,3,16,"普通",0);
		  else
			GUI_ShowCHinese(WIDTH-2-24-32,3,16,"特殊",0);
		}
	}
	else if(key_flag.setting_index==5)//连发张数设置
	{
		switch(key_flag.key_ok)
		{
			case 1:
				GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num.bai,1,16,0);                         //连发张数
		    GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,0);                    //连发张数
		    GUI_ShowNum(WIDTH-2-24+16,23,menu.Send_continuously_num.ge,1,16,0);                      //连发张数
        GUI_ShowCHinese(WIDTH-2-24-32,23,16,"连发",0);
				break;
			case 2:
				GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num.bai,1,16,1);                         //连发张数
		    GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,1);                    //连发张数
		    GUI_ShowNum(WIDTH-2-24+16,23,menu.Send_continuously_num.ge,1,16,blink_Flag);                      //连发张数
			  GUI_ShowCHinese(WIDTH-2-24-32,23,16,"连发",1);
				break;
			case 3:
				GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,blink_Flag);                    //连发张数
		    GUI_ShowNum(WIDTH-2-24+16,23,menu.Send_continuously_num.ge,1,16,1);                      //连发张数
				break;
			case 4:
				GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num.bai,1,16,blink_Flag);                         //连发张数
		    GUI_ShowNum(WIDTH-2-24+8,23,menu.Send_continuously_num.shi,1,16,1);                    //连发张数
				break;
			default:break;
		}
	}
	else if(key_flag.setting_index==6)//方向设置
	{
		if(key_flag.key_ok==0)                        //设置状态
		{
			if(menu.Direction)
		  GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"逆",blink_Flag);
	    else
		  GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"顺",blink_Flag);
	    GUI_ShowCHinese(WIDTH-2-24-32+16,23+3+16,16,"时针",blink_Flag);
		}
		else if(key_flag.key_ok==1)
		{
			if(menu.Direction)
		  GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"逆",0);
	    else
			GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"顺",0);
			GUI_ShowCHinese(WIDTH-2-24-32+16,23+3+16,16,"时针",0);
		}
	}	
  else if(key_flag.setting_index==3)                                 //底牌张数
	{
		switch(key_flag.key_ok)
		{
			case 1:
				GUI_ShowNum(2,42,menu.Remain_num.bai,1,16,0);                        //底牌张数
				GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,0);                    //底牌张数
				GUI_ShowNum(2+16,42,menu.Remain_num.ge,1,16,0);                    //底牌张数
				GUI_ShowCHinese(2+24,42,16,"张",0);
				break;
			case 2:
				GUI_ShowNum(2+16,42,menu.Remain_num.ge,1,16,blink_Flag);        //个位数字设置
			  GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,1);         //十位数字设置
		   	GUI_ShowNum(2,42,menu.Remain_num.bai,1,16,1);            //百位数字设置
			  GUI_ShowCHinese(2+24,42,16,"张",1);
				break;
			case 3:
				GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,blink_Flag);         //十位数字设置
			  GUI_ShowNum(2+16,42,menu.Remain_num.ge,1,16,1);        //个位数字设置
				break;
			case 4:
				GUI_ShowNum(2,42,menu.Remain_num.bai,1,16,blink_Flag);            //百位数字设置
			  GUI_ShowNum(2+8,42,menu.Remain_num.shi,1,16,1);
				break;
			default:break;
		}
	}
}



///*******************************************************************************
//**函数名称：void Set_current_position(void)
//**功能描述：系统初始化
//**入口参数：
//**输出：无
//*******************************************************************************/
//void Setting_current_position(uint8_t position)
//{
//	switch(position)
//	{
//		case 0:GUI_ShowCHinese(2,3,16,"四人",blink_Flag);break;
//		case 1: 
//			GUI_ShowNum(2,23,menu.Tickets_num_perperson,3,16,0);                    //张/人
//	    GUI_ShowCHinese(2+24,23,16,"张",0);
//			break;
//		case 2: 
//			GUI_ShowNum(2,42,menu.Remain_num,3,16,0);                    //底牌张数
//	    GUI_ShowCHinese(2+24,42,16,"张",0);
//			break;
//		case 3: GUI_ShowCHinese(WIDTH-2-24-32,3,16,"普通",blink_Flag);break;
//		case 4: 
//			GUI_ShowNum(WIDTH-2-24,23,menu.Send_continuously_num,3,16,0);                    //连发张数
//      GUI_ShowCHinese(WIDTH-2-24-32,23,16,"连发",0);
//			break;
//		case 5: 
//			GUI_ShowCHinese(WIDTH-2-24-32,23+3+16,16,"逆时针",blink_Flag);
//			break;
//		default:break;
//	}
//}









///*******************************************************************************
//**函数名称：uint8_t I2C1_Master_BufferWrite(I2C_Module* I2Cx, uint8_t* pBuffer, uint32_t NumByteToWrite, uint8_t SlaveAddress)
//**功能描述：I2C1写数据
//**入口参数：
//**输出：无
//*******************************************************************************/
//uint8_t I2C1_Master_BufferWrite(I2C_Module* I2Cx, uint8_t* pBuffer, uint32_t NumByteToWrite, uint8_t SlaveAddress)
//{
//    if(NumByteToWrite==0)
//        return 1;
//    /* 1.开始*/
//     I2C_GenerateStart(I2Cx, ENABLE);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG));

//    /* 2.设备地址·/写 */
//		I2C_SendAddr7bit(I2Cx,SlaveAddress,I2C_DIRECTION_SEND);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_TXMODE_FLAG));

//    /* 3.连续写数据 */
//    while(NumByteToWrite--)
//    {
//      I2C_SendData(I2Cx, *pBuffer);
//      while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_SENDED));
//      pBuffer++;
//    }

//    /* 4.停止 */
//    I2C_GenerateStop(I2Cx, ENABLE);
//    while ((I2Cx->CTRL1&0x200) == 0x200);
//    return 0;
//}



///*******************************************************************************
//**函数名称：uint8_t I2C1_Master_BufferRead(I2C_Module* I2Cx, uint8_t* pBuffer, uint32_t NumByteToRead, uint8_t SlaveAddress)
//**功能描述：I2C1写数据
//**入口参数：
//**输出：无
//*******************************************************************************/
//uint8_t I2C1_Master_BufferRead(I2C_Module* I2Cx, uint8_t* pBuffer, uint32_t NumByteToRead, uint8_t SlaveAddress)
//{
//    if(NumByteToRead==0)
//        return 1;

//    while(I2C_GetFlag(I2Cx, I2C_FLAG_BUSY));  
//    I2C_ConfigAck(I2Cx, ENABLE);
//    /* 1.开始*/
//    I2C_GenerateStart(I2Cx, ENABLE);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG));
//    /* 2.设备地址·/写 */
//		I2C_SendAddr7bit(I2Cx,SlaveAddress,I2C_DIRECTION_SEND);
//    while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_TXMODE_FLAG));

//    /* 3.开始*/
//    I2C_GenerateStart(I2Cx, ENABLE);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG));
//    /* 4.设备地址·/读 */
//		I2C_SendAddr7bit(I2Cx,SlaveAddress,I2C_DIRECTION_RECV);
//    while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_RXMODE_FLAG));

//    /* 5.连续写数据 */
//    while (NumByteToRead)
//    {
//        if(NumByteToRead==1)
//        {
//           I2C_ConfigAck(I2Cx, DISABLE);
//           I2C_GenerateStop(I2Cx, ENABLE);//6.停止，非应答
//        }

//        while(!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_DATA_RECVD_FLAG));  /* EV7 */
//        *pBuffer++ = I2C_RecvData(I2Cx);
//        NumByteToRead--;
//    }

//    I2C_ConfigAck(I2Cx, ENABLE);
//    return 0;
//}   







