#ifndef __CONTROL_H
#define __CONTROL_H

#define EN_Left  PCout(0)
#define EN_Right PCout(2)

#define Dir_Left  PAout(7)
#define Dir_Right PCout(3)


void EN_GPIO_Init(void);
void Stp_GPIO_Init(void);
void Dir_GPIO_Init(void);
void SETPWM(int motor_left, int motor_right);
void Limit(int *motoA,int *motoB);



#endif


