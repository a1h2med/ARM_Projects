#include "C:\Keil_v5\EE319Kware\inc\tm4c123gh6pm.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

void Duty_cycle(uint8_t duty_cycle){
	if(duty_cycle == 100){
		PWM1_3_CMPA_R = 1;
	} else if(duty_cycle == 0) {
		PWM1_3_CMPA_R = 1248;
	}else {
		PWM1_3_CMPA_R = (uint16_t)(1250 * (1 - (duty_cycle / 100.0)) - 1);
	}
}
