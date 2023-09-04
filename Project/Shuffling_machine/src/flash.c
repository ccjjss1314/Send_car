#include "flash.h"






/**
* @brief  指定地址读取一个字
* @param  faddr  读取的地址
* @param  none
* @param  none
* @retval 读取的字
* @example 
* @waing  
**/
u32 STMFLASH_ReadWord(u32 faddr)
{
//	printf("RE=%x:%d ",faddr,*(vu32*)faddr);
	return *(vu32*)faddr; 
} 


/*******************************************************************************
**函数名称：void N32_Flash_ReadPage(buff,sector,count)
**功能描述： 
**
*********************************************************************************/
int N32_Flash_ReadPage(unsigned char *pBuffer,u32 ReadAddr,unsigned int NumToRead)
{
		u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
	return 1;
}

