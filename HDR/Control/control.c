#include "control.h"
#include "sys.h"


void EN_GPIO_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStruct;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_2;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
//		  GPIO_SetBits(GPIOC,GPIO_Pin_0);
//	    GPIO_SetBits(GPIOC,GPIO_Pin_2);
}

void Dir_GPIO_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStruct;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
			
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
	
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
			GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void Stp_GPIO_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStruct;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
	    GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	    GPIO_ResetBits(GPIOB,GPIO_Pin_7);
}


//оч╥Ы
void Limit(int *motoA,int *motoB)
{
	if(*motoA>400)*motoA=400;
	if(*motoA<-400)*motoA=-400;
	
	if(*motoB>400)*motoB=400;
	if(*motoB<-400)*motoB=-400;
}



int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);                                                           
	return q;
}

u16 Pluse_Period_Left;
u16 Pluse_Period_Right;

void SETPWM(int motor_left, int motor_right)
{
	
	if(motor_left>0)	   Pluse_Period_Left = 7199/GFP_abs(motor_left),Dir_Left = 1; //hou
//	if(motor_left>0)     EN_Left = 0;
	if(motor_left<0)     Pluse_Period_Left = 7199/GFP_abs(motor_left),Dir_Left = 0; //qian
	
	if(motor_right>0)		 Pluse_Period_Right = 7199/GFP_abs(motor_right),Dir_Right = 1;	//hou
//  if(motor_right>0)    EN_Right = 0;
	if(motor_right<0)    Pluse_Period_Right = 7199/GFP_abs(motor_right),Dir_Right = 0;//qian

}




