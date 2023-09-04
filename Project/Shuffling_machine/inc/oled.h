#ifndef __OLED_H__
#define __OLED_H__
#include "main.h"

#define BufferSize 32
//#define I2C1_REMAP
#define I2C1_MASTER_ADDR   0x30
#define I2C1_SLAVE_ADDR    0x10

//--------------OLED参数定义---------------------
#define PAGE_SIZE    8
#define XLevelL		0x00
#define XLevelH		0x10
#define YLevel       0xB0

#define	Brightness	 0xFF 

#define WIDTH 	     128
#define HEIGHT 	     64	

//-------------写命令和数据定义-------------------
#define OLED_CMD     0	//写命令
#define OLED_DATA    1	//写数据 

//复位信号
#define OLED_RST_Clr()  GPIO_ResetBits(GPIOD,GPIO_PIN_8)
#define OLED_RST_Set()  GPIO_SetBits(GPIOD,GPIO_PIN_8)
//数据/命令选择信号
#define OLED_DC_Clr()  GPIO_ResetBits(GPIOB,GPIO_PIN_14)
#define OLED_DC_Set()  GPIO_SetBits(GPIOB,GPIO_PIN_14)
//片选信号
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_PIN_12)
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_PIN_12)


typedef struct
{
	uint8_t ge;
	uint8_t shi;
	uint8_t bai;
}Num_div;


typedef struct {
	uint8_t  People_num;                          //1-8人
	uint8_t  Mode;                                //0:特殊 1:普通
	Num_div Tickets_num_perperson;
	Num_div Send_continuously_num;
	Num_div Remain_num;                          
	uint8_t  Direction;                           //0:顺时针 1:逆时针
}Mode_menu_setting;

typedef struct {                                //1：正在设置
	uint8_t  People_num_setting;
	uint8_t  Mode_setting;
	uint8_t  Tickets_num_perperson_setting;
	uint8_t  Send_continuously_num_setting;
	uint8_t  Remain_num_setting;
	uint8_t  Direction_setting;
}Setting_condition;

extern Setting_condition Setting;
extern Mode_menu_setting menu;
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);
void Init_MainPage(void);
void Test_Color(void);
void Test_Rectangular(void);
void Test_Circle(void);
void Test_Triangle(void);
void TEST_English(void);
void TEST_Number_Character(void);
void TEST_Chinese(void);
void TEST_BMP(void);
void TEST_Menu1(void);
void TEST_Menu2(void);
void OLED_SPI2_GPIO_Init(void);
void OLED_Clear(unsigned dat);
void OLED_Init(void);
void OLED_Display(void);
void OLED_Fade_Display(void);
void Setting_current_position(uint8_t position);
void Updata_Mainpage(void);

#endif /* __OLED_H__ */