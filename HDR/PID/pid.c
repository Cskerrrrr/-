#include "pid.h"

float Med_Angle = 2.7;			//��е��ֵ
float Vertical_Kp = 3,		  //ֱ����Kp
	    Vertical_Kd =0.03;		//ֱ����Kd

float Velocity_Kp = -1.2,		//�ٶȻ�Kp
	    Velocity_Ki = 0.02;	 	//�ٶȻ�Kd

float location_Kp = 10,
	    location_Ki = 0.01;	

float Turn_Kp = 3, 
	    Turn_Kd = 0.03;

int Vertical_out,Velocity_out_Left,Velocity_out_Right,Turn_out;		//���

extern float Med_Angle;		//��е��ֵ
extern int Encoder_Left,Encoder_Right;
extern float Target_Speed;						//�����ٶ�
extern u8 EN_RIGHT,EN_LEFT;
//u16 speed = 1600;//225-1600


int location_PI(int location);
int measure;
int motor1, motor2;
int Vertical_PD(float measure, float Gyro);
int Velocity_PI(int Speed_measure);
int Turn(int gyro_Z);


void EXTI9_5_IRQHandler(void)
{
	int PWM_out_Left,PWM_out_Right;

	if(EXTI_GetITStatus(EXTI_Line5)!=0)
	{			
		EXTI_ClearITPendingBit(EXTI_Line5);
		if(PBin(5) == 0)
		{     
		  mpu_dmp_get_data(&Pitch, &Roll, &Yaw);				//�Ƕ�
		  MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);			//���ٶ�			
		  if(Pitch>40)
			{
				EN_RIGHT = 0;
				EN_LEFT = 0;
				TIM_SetCompare1(TIM2,1945);
			}
			else if(Pitch<-40)
			{
				EN_RIGHT = 0;
				EN_LEFT = 0;
				TIM_SetCompare1(TIM2,1750);
			}
			else if (Pitch<10||Pitch>-10)
			{
				EN_RIGHT = 1;
				EN_LEFT = 1;
				TIM_SetCompare1(TIM2,1850);
			}
			Encoder_Left = motor1;						//�ɼ��������ٶ�
			Encoder_Right = motor2;
			Vertical_out = Vertical_PD(Pitch, gyroy);				//ֱ��������
			Velocity_out_Left = Velocity_PI(Encoder_Left);				//�ٶȻ�����
			Velocity_out_Right = Velocity_PI(Encoder_Right);				//�ٶȻ�����
			Turn_out = Turn(gyroz);		
			PWM_out_Left = Vertical_out + Velocity_out_Left;				//PWM���
			PWM_out_Right = Vertical_out + Velocity_out_Right;				//PWM���
			motor1 = PWM_out_Left + Turn_out;
			motor2 = PWM_out_Right - Turn_out;
			Limit(&motor1, &motor2);							//PWM�޷�
			SETPWM(motor1,motor2);								//����PWM�����
			LED0 =! LED0;
		}
	}
}



//ֱ����PD

int Vertical_PD(float measure, float Gyro)
{
	int PWM_out;
	
	PWM_out = Vertical_Kp*(measure + Med_Angle) + Vertical_Kd*Gyro;
	return PWM_out;
}

//�ٶȻ�PI
int Velocity_PI(int Speed_measure)
{
	static int Encoder_err, Encoder_err_low, Encoder_err_low_last, Encoder_sum, Movement;
	static int PWM_out;
    if(USART_ReceiveData(USART1) == 'R')
	{
		Target_Speed = -35;
	}
	else if(USART_ReceiveData(USART1) == 'B')
	{
		Target_Speed = 35;
	}
	else
    {
		Target_Speed = 0;
	}
	Encoder_err = Target_Speed - Speed_measure;
	Encoder_err_low = 0.28 * Encoder_err + 0.72 * Encoder_err_low_last;
	Encoder_err_low_last = Encoder_err_low;
	Encoder_sum += Encoder_err_low;
	Encoder_sum = Encoder_sum + Movement;
	if(Encoder_sum > 100) Encoder_sum = 100;
	if(Encoder_sum < -100) Encoder_sum = -100;

	
	PWM_out = Velocity_Kp*Encoder_err  + Velocity_Ki*Encoder_sum;
	
		
	return PWM_out;
}

int location_PI(int location)
{
	static int Encoder_err, Encoder_err_low, Encoder_err_low_last, Encoder_sum, Movement;
	static int PWM_out;

	Encoder_err = 0 - location;
	Encoder_err_low = 0.28 * Encoder_err + 0.72 * Encoder_err_low_last;
	Encoder_err_low_last = Encoder_err_low;
	Encoder_sum += Encoder_err_low;
	Encoder_sum = Encoder_sum + Movement;
	if(Encoder_sum > 100) Encoder_sum = 100;
	if(Encoder_sum < -100) Encoder_sum = -100;

	
	PWM_out = location_Kp*Encoder_err  + location_Ki*Encoder_sum;
	
		
	return PWM_out;
}


//ת��
int Turn(int gyro_Z)
{
	int PWM_out;
	static float Turn_Target;
	float Kp = Turn_Kp,Kd = Turn_Kd;			

	Kd = Turn_Kd;
	if(USART_ReceiveData(USART1) == 'z')
	{
		Turn_Target = -10;
	}
	else if(USART_ReceiveData(USART1) == 'y')
	{
		Turn_Target = 10;
	}
	else
    {
		Turn_Target = 0;
	}
	PWM_out = Turn_Target*Kp + gyro_Z*Kd; 
	
	return PWM_out;
}


