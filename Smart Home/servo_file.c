#include "SERVO.h"
#include "tm4c123gh6pm.h"

void PWM_init(uint16_t VALUE){
	volatile unsigned long delay;
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_USEPWMDIV);
	SYSCTL_RCGC0_R |= 0X00100000;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_DEN_R |= 0X40;
	GPIO_PORTB_AFSEL_R |= 0X40;
	GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB6_T0CCP0;
	PWM0_0_CTL_R &= 0X00000000;
	PWM0_0_GENA_R |= 0x0000008C;
	PWM0_0_LOAD_R = 0x0000018F;											// referring to the datasheet i made the frequency 25 
																									// but for sure we will change it to the required frequency which we will work on later
	PWM0_0_CMPA_R = VALUE;													// SET COUNTER VALUE AT WHICH CMPA TRIGGERS
																									// i will set this cmp depending on the required duty cycle
																									// depending on it i will control the rotation of the servo	
	PWM0_0_CTL_R |= 0X01;
	PWM0_ENABLE_R |= (PWM_ENABLE_PWM0EN);
}




void servoLeft(){
	PWM_init(0x0000012B);														// here i will send the value of cmpa which i will compare with 
																									// and it will be 25% from the duty cycle to make the motor rotate to the left
}

void servoRight (){
	PWM_init(0x00000063);														// here i will send the value of cmpa which i will compare with
																									// and it will be 75% from the duty cycle to make the motor rotate to the right
}
