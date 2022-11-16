#include "sys.h"

float Target_Speed = 0;						//�����ٶ�
short gyrox,gyroy,gyroz;					//���ٶ�
float Pitch,Roll,Yaw;						//�Ƕ�
int Encoder_Left,Encoder_Right;				//�������ٶ�




int main()
{
		vu8 key;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//w4����ռ,4����Ӧ��
		delay_init();
		KEY_Init();
		NVIC_Config();
		SystemInit();
	    Usart_init(38400);
//	    USART2_Init(38400);
	    LED_Init();
	    EN_GPIO_Init();
	    Stp_GPIO_Init();     
	    Dir_GPIO_Init();
//	    TIM6_Int_Init(1999,719);
        PWM_Init(1999,719);
	    TIM3_Int_Init(9,35);
		TIM4_Int_Init(9,35);
		MPU_Init();
		mpu_dmp_init();
		MPU6050_EXTI_Init();
		LCD_Init();	   //Һ������ʼ��
		LCD_Clear(BLACK); //����
		POINT_COLOR=WHITE; 
		while(1)
		{
				key = KEY_Scan(0);
				LCD_ShowNum(50,10,Pitch,4,16);
				LCD_ShowNum(50,40,Roll,4,16);
				LCD_ShowNum(50,70,Yaw,4,16);
		}
}





