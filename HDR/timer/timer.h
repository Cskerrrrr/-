#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#define Stp_Left  PBout(6)
#define Stp_Right PBout(7)

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
#endif
