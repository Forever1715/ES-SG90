#include "gear.h"
#include "sys.h"


void Gear_Angle(int angle)
{
	int time2ch1cmp;
	angle = angle + 90;                      //将(-90) - 90的域量化
	time2ch1cmp = 1000 + angle * 4000 / 180; //到1000 - 5000的域
	TIM_SetCompare2(TIM2,time2ch1cmp); 
}

/********************************************************************************************************
Function Name:舵机PWM初始化
Author       :zq
Date         :2018.7.25
Description  :Timer2通道2初始化，PWM模式
Inputs       :计数器TOP值,预分频 (ARR,PSC)
Outputs      :
Notes        :输出口为PA1
Revision     :v1.0
********************************************************************************************************/
void TIM2_PWM_Init(u16 period, u16 prescaler)  //计数器TOP值,预分频 (ARR,PSC)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器2时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA PA1
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//初始化TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2时钟使能
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //上行计数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeStruct); //TIM2初始化
	
	//初始化TIM2 Channel2 PWM2
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //CNT>CCR有效
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_Low;  //输出极性低电平
	TIM_OC2Init(TIM2,&TIM_OCInitTypeStruct);
	
	//使能TIM2 Channel2预装载寄存器
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_Cmd(TIM2,ENABLE);
}

void Gear_Init(void)
{
	TIM2_PWM_Init(39999,35); //使用定时器2的通道3,PB10
	TIM_SetCompare2(TIM2,3000);//初始化时旋转角度为0
//	TIM7_Init(199,7199);
}
