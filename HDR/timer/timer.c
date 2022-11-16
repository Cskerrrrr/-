#include "timer.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

extern int motor1, motor2;


void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	//使能时钟
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

    //设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    //设置定时器基本参数
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStructure );
    
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		TIM_ARRPreloadConfig(TIM3,ENABLE);
    //使能定时器
    TIM_Cmd( TIM3, ENABLE );
				 
}



void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	//使能时钟
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );

    //设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    //设置定时器基本参数
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStructure );
    
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
		TIM_ARRPreloadConfig(TIM4,ENABLE);
    //使能定时器
    TIM_Cmd( TIM4, ENABLE );
				 
}

void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	//使能时钟
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM6, ENABLE );

    //设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    //设置定时器基本参数
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM6, &TIM_TimeBaseInitStructure );
    
		TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    //使能定时器
    TIM_Cmd( TIM6, ENABLE );
				 
}

u16 Pluse_High_Left=10; //脉冲高电平中断次数      1->10us
extern u16 Pluse_Period_Left;//脉冲周期中断次数 （转速）
//脉冲中断服务函数------------------------------------------------------------
u32 TimeCount_Left=0;//进中断计数
u8 EN_LEFT= 1;

void TIM3_IRQHandler(void)//10us
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)//溢出中断
	{		
		EN_Left = 1;
		if( EN_LEFT == 1)
		{			
			TimeCount_Left++;
			if(TimeCount_Left<Pluse_High_Left)//脉冲高电平
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_6);
			}
			else if(TimeCount_Left>Pluse_High_Left)
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			}
			if(TimeCount_Left>Pluse_Period_Left)//周期控制（转速控制）
			{
				TimeCount_Left=0;
			}
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}


//全局变量-------------------------------------------------------------------
u16 Pluse_High_Right=10; //脉冲高电平中断次数      1->10us
extern u16 Pluse_Period_Right;//脉冲周期中断次数 （转速）
//脉冲中断服务函数------------------------------------------------------------
u32 TimeCount_Right=0;//进中断计数
u8 EN_RIGHT = 1;

void TIM4_IRQHandler(void)//10us
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//溢出中断
	{		
		EN_Right = 1;
		if( EN_RIGHT == 1)
		{			
			TimeCount_Right++;
			if(TimeCount_Right<Pluse_High_Right)//脉冲高电平
			{
			  GPIO_SetBits(GPIOB,GPIO_Pin_7);
			}
			else if(TimeCount_Right>Pluse_High_Right)
			{
			  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			}
			if(TimeCount_Right>Pluse_Period_Right)//周期控制（转速控制）
			{
				TimeCount_Right=0;
			}
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}


void TIM6_IRQHandler(void)//10us
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)//溢出中断
	{		
       
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
}
