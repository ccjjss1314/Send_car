#include "flash.h"






/**
* @brief  ָ����ַ��ȡһ����
* @param  faddr  ��ȡ�ĵ�ַ
* @param  none
* @param  none
* @retval ��ȡ����
* @example 
* @waing  
**/
u32 STMFLASH_ReadWord(u32 faddr)
{
//	printf("RE=%x:%d ",faddr,*(vu32*)faddr);
	return *(vu32*)faddr; 
} 


/*******************************************************************************
**�������ƣ�void N32_Flash_ReadPage(buff,sector,count)
**���������� 
**
*********************************************************************************/
int N32_Flash_ReadPage(unsigned char *pBuffer,u32 ReadAddr,unsigned int NumToRead)
{
		u32 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
		ReadAddr+=4;//ƫ��4���ֽ�.	
	}
	return 1;
}

