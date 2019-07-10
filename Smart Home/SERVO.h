#ifndef _SERVO_H
#define _SERVO_H
#include "stdint.h"

void PWM_init(uint16_t VALUE);
void servoRight();
void servoLeft ();

#endif