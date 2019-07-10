#include "tm4c123gh6pm.h"
#include "PWM.h"
#include <stdint.h>

void PWM_Init(void){
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
	SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_64; // PWM Clock = 1.25 MHz
	PWM1_3_CTL_R = 0x00000000;
	PWM1_3_GENA_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_3_LOAD_R = 1250 - 1; // 1KHz
	PWM1_3_CMPA_R = 1248; // 0% Duty Cycle
	PWM1_3_CTL_R = PWM_0_CTL_ENABLE;	
	GPIO_PORTF_AFSEL_R |= GPIO_PF2_M;
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFF0FF) | (GPIO_PCTL_PF2_M1PWM6);
	GPIO_PORTF_DIR_R |= GPIO_PF2_M;
	GPIO_PORTF_DEN_R |= GPIO_PF2_M;
	PWM1_ENABLE_R = PWM_ENABLE_PWM6EN; // M1PWM6 (PF2)
}