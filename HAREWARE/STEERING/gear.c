#include "gear.h"
#include "sys.h"


void Gear_Angle(int angle)
{
	int time2ch1cmp;
	angle = angle + 90;                      //��(-90) - 90��������
	time2ch1cmp = 1000 + angle * 4000 / 180; //��1000 - 5000����
	TIM_SetCompare2(TIM2,time2ch1cmp); 
}

/********************************************************************************************************
Function Name:���PWM��ʼ��
Author       :zq
Date         :2018.7.25
Description  :Timer2ͨ��2��ʼ����PWMģʽ
Inputs       :������TOPֵ,Ԥ��Ƶ (ARR,PSC)
Outputs      :
Notes        :�����ΪPA1
Revision     :v1.0
********************************************************************************************************/
void TIM2_PWM_Init(u16 period, u16 prescaler)  //������TOPֵ,Ԥ��Ƶ (ARR,PSC)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ�ܶ�ʱ��2ʱ��
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA PA1
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//��ʼ��TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2ʱ��ʹ��
	TIM_TimeBaseInitTypeStruct.TIM_Period = period;
	TIM_TimeBaseInitTypeStruct.TIM_Prescaler = prescaler;
	TIM_TimeBaseInitTypeStruct.TIM_CounterMode = TIM_CounterMode_Up; //���м���
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeStruct); //TIM2��ʼ��
	
	//��ʼ��TIM2 Channel2 PWM2
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //CNT>CCR��Ч
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_Low;  //������Ե͵�ƽ
	TIM_OC2Init(TIM2,&TIM_OCInitTypeStruct);
	
	//ʹ��TIM2 Channel2Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_Cmd(TIM2,ENABLE);
}

void Gear_Init(void)
{
	TIM2_PWM_Init(39999,35); //ʹ�ö�ʱ��2��ͨ��3,PB10
	TIM_SetCompare2(TIM2,3000);//��ʼ��ʱ��ת�Ƕ�Ϊ0
//	TIM7_Init(199,7199);
}
