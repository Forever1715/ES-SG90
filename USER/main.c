/********************************************************************************************************
**                                 Copyright (c)          cxg project document
**                                                 All Rights Reserved
**
**                                 Email:   barry1997@126.com           QQ:1176072871
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103ZET6 (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name:
**  Module Date:
**  Module Auth:
**  Description:
**  Version    : V1.0
**  Notes      :
**-------------------------------------------------------------------------------------------------------
**  Version    :
**  Modified By:
**  Date       :
**  Content    :
**  Notes      :
********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "sys.h"
#include "delay.h"
#include "gear.h"

/********************************************************************************************************
Function Name:主函数
Author       :zq
Date         :2018.7.11
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :v1.0
********************************************************************************************************/
int main(void)
{	 
	delay_init();	    	 //延时函数初始化	  
	//===========================================调试=======================================//
	//舵机
	Gear_Init();
	Gear_Init();
	Gear_Angle(0);//舵机调试完成0927
	while(1)
	{
		delay_ms(1000);
		Gear_Angle(-90);
		delay_ms(1000);
		Gear_Angle(-45);
		delay_ms(1000);
		Gear_Angle(0);
		delay_ms(1000);
		Gear_Angle(45);
		delay_ms(1000);
		Gear_Angle(90);
	}
}
//===========================================  End Of File  ===========================================//

