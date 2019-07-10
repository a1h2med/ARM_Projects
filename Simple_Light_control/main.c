//#include <stdint.h>
//#include <stdbool.h>
//#include "G:/ARM/RV31/LIB/Luminary/driverlib/sysctl.h"
#include "tm4c123gh6pm.h"

#define GPIO_P_M				0xFFU 	//all Pins in any port (mask)
#define GPIO_PCTL_PD_M		(GPIO_PCTL_PD1_M | GPIO_PCTL_PD2_M | GPIO_PCTL_PD3_M) // To combine masks for push buttons

volatile int counter = 0 ;volatile int arm = 0 ;volatile int bit = 0 ;volatile int see = 0 ;
int yeah = 0 ;int say = 0 ;int donno = 0;int x = 0;int y =0;int z = 0;
void delay(void);
void System_Init(void);
void DisplayNumber_ThirdSeg(int num);
void DisplayNumber_SecondSeg(int num);
void DisplayNumber_FirstSeg(int num);
void delayMs(uint32_t ui32Ms);
void delayUs(uint32_t ui32Us);
void Push1(int hell);
void Push2(int hell);
void Push3(int hell);
void Systick_Wait(uint32_t name);
void Systick_Wait10ms (uint32_t name);
int decimalToBinary(int n);

int main(){
	System_Init();
	yeah  =  0 ; 																// that variable is made for Initializing the Count
	say   =  0 ;                  							// that variable is made for Initializing the Count
	donno =  0 ;                  							// that variable is made for Initializing the Count							
	y = 1;
	while(1){
		
		arm = GPIO_PORTD_DATA_R & 0x01;
		bit = GPIO_PORTD_DATA_R & 0x02;
		see = GPIO_PORTD_DATA_R & 0x04;
		Push1(arm);
		Push2(bit);
		Push3(see);
		}
}

void Push1(int hell)													// that function is made for increment
{							
	while (hell == 1)														// this loop will be true whenever the button is pressed
	{							
		if (yeah <= 9){														// checking whether the counter reached 9 or not
			/*if (y == 1){
				yeah = yeah - 2;
				y = 0;
			}*/
			if ( x== 1){
				yeah = yeah +1;
				DisplayNumber_FirstSeg(yeah);
				x = 0;
			}
			else {
			DisplayNumber_FirstSeg(yeah);						// here i will send the value of the counter to the first function
			yeah = yeah +1;													// increasing counter by 1
		}
	}
		else if (say < 9)					// if the counter reached 9 so i have to increase second 7-segment by 1
		{
			x = 1;
			yeah =0;																// i will set the first counter to 0 so in changing will be something like 10 or 20
			say = say +1;														// i will increase the second counter with one as a trick for counting
			DisplayNumber_FirstSeg(yeah);						// i will send the counting parameters to the functions to write it on 7-segment
			DisplayNumber_SecondSeg(say);           // i will send the counting parameters to the functions to write it on 7-segment
		}
		else 																			// if the counter is higher than 99 so we are at the third 7-segment
		{
			x = 1;
			yeah = 0;                               // i will set the first counter to 0  
			say = 0;																// i will set the second counter to 0 
			donno = donno +1;												// i will increase the third counter with one as a trick for counting
			DisplayNumber_FirstSeg(yeah);						// i will send the counting parameters to the functions to write it on 7-segment
			DisplayNumber_SecondSeg(say);           // i will send the counting parameters to the functions to write it on 7-segment
			DisplayNumber_ThirdSeg(donno);          // i will send the counting parameters to the functions to write it on 7-segment
		}
		Systick_Wait10ms (20);										// here we called the delay function to check on the state of the button
		hell = GPIO_PORTD_DATA_R & 0x01;					// here we are reading our inputs to decide whether we will continue or do another thing
		bit = GPIO_PORTD_DATA_R & 0x02;     			// here we are reading our inputs to decide whether we will continue or do another thing
		see = GPIO_PORTD_DATA_R & 0x04;     			// here we are reading our inputs to decide whether we will continue or do another thing
		
		if (hell == 1)														// here we are checking whether the button is still pressed or not... if yes we will continue in our loop
			continue;	
		else{ 																		// else we will check on what should we do
			if (bit == 0b00000010)									// if the second button is pressed i will call the second function
				Push2(bit);														
			else																		// if the third button is pressed i will call the third function
				Push3(see);
		break;																		
	}
	}
}


void Push2(int hell)					 								// that function is made for decrement
{								
	if (hell == 0b00000010 && y == 1){			
				y = 0;
		
		 if(say == 0 && yeah == 0 && donno == 0){
				DisplayNumber_FirstSeg(0);
						DisplayNumber_SecondSeg(0);
						DisplayNumber_ThirdSeg(0);
			}else if (yeah > 0){													// here am checking whether i have a number like 123 or not, if yes i will decrease it to 122
			
		yeah = yeah- 1;			

			}
			else if (say > 0 && yeah == 0){					// here am checking whether i have a number like 120 or not, if yes i will decrease it to 119 
				say = say -1;
						z = 1;
						yeah = 9;
						DisplayNumber_FirstSeg(9);
						DisplayNumber_SecondSeg(say);
						DisplayNumber_ThirdSeg(donno);
			
					}
			else if (say == 0 && yeah == 0){																	// here am checking whether i have a number like 100 or nor, if yes i will decrease it to 99
				donno = donno - 1;
						yeah = 9;
						say = 9;
						DisplayNumber_FirstSeg(yeah);
						DisplayNumber_SecondSeg(say);
						DisplayNumber_ThirdSeg(donno);
			
			}
			
			Systick_Wait10ms(40);
		hell = GPIO_PORTD_DATA_R & 0x02 ;					// here we are reading our inputs to decide whether we will continue or do another thing
		arm = GPIO_PORTD_DATA_R & 0x01;     			// here we are reading our inputs to decide whether we will continue or do another thing
		see = GPIO_PORTD_DATA_R & 0x04;     			// here we are reading our inputs to decide whether we will continue or do another thing
		
		//if (hell == 0b00000010)														// here we are checking whether the button is still pressed or not... if yes we will continue in our loop
			//continue;	
		//else{ 																		// else we will check on what should we do
			if (arm == 0x01)									// if the second button is pressed i will call the second function
				Push1(bit);														
			else																		// if the third button is pressed i will call the third function
				Push3(see);
		//eak;																		
	//}
	}
	else if (hell == 0b00000000)
			y = 1;
	 }	


void Push3(int hell)				  // that function is made for 
{
	if (hell == 0b00000100){							// if the reset button is pressed i will reset all the pins
		yeah  =  0 ;
		say   =  0 ;
		donno =  0 ;
		DisplayNumber_FirstSeg(yeah);
		DisplayNumber_SecondSeg(say);	
		DisplayNumber_ThirdSeg(donno);
	}
}

 
void System_Init(void){	volatile unsigned long delay;
	
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;  // PortA clock enable
  delay = SYSCTL_RCGCGPIO_R;        				// Delay 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;  // PortB clock enable
  delay = SYSCTL_RCGCGPIO_R;        				// Delay 
//  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;  // Portc clock enable
// delay = SYSCTL_RCGCGPIO_R;        				// Delay 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;  // PortD clock enable
  delay = SYSCTL_RCGCGPIO_R;        				// Delay 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;  // PortE clock enable
  delay = SYSCTL_RCGCGPIO_R;        				// Delay 
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  // PortF clock enable
  delay = SYSCTL_RCGCGPIO_R;


  
  GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortA Commit register
  GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortB Commit register
//  GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortC Commit register
  GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortD Commit register
  GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortE Commit register
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortF Commit register  
  
	
	
  GPIO_PORTA_CR_R |= GPIO_P_M;              // Allow changes to PORT A
  GPIO_PORTB_CR_R |= GPIO_P_M;              // Allow changes to PORT B
 // GPIO_PORTC_CR_R |= GPIO_P_M;              // Allow changes to PORT c
  GPIO_PORTD_CR_R |= GPIO_P_M;              // Allow changes to PORT D
  GPIO_PORTE_CR_R |= GPIO_P_M;              // Allow changes to PORT E   
	GPIO_PORTF_CR_R |= GPIO_P_M;              // Allow changes to PORT F
  
	
	
	GPIO_PORTA_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
	GPIO_PORTB_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
//	GPIO_PORTC_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
	GPIO_PORTD_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
	GPIO_PORTE_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
	GPIO_PORTF_AMSEL_R &= ~GPIO_P_M;      // Disable analog function
	
	
	
  GPIO_PORTA_DEN_R |= GPIO_P_M;         // Enable digital pins
  GPIO_PORTB_DEN_R |= GPIO_P_M;         // Enable digital pins
//  GPIO_PORTC_DEN_R |= GPIO_P_M;         // Enable digital pins
  GPIO_PORTD_DEN_R |= GPIO_P_M;         // Enable digital pins
  GPIO_PORTE_DEN_R |= GPIO_P_M;         // Enable digital pins
	GPIO_PORTF_DEN_R |= GPIO_P_M;         // Enable digital pins
	
	
	
	
  GPIO_PORTD_PCTL_R &= ~GPIO_PCTL_PD_M;     // GPIO clear bit PCTL  (the 3 push button)



  GPIO_PORTA_AFSEL_R &= ~GPIO_P_M;      // No alternate function
	GPIO_PORTB_AFSEL_R &= ~GPIO_P_M;      // No alternate function
//	GPIO_PORTC_AFSEL_R &= ~GPIO_P_M;      // No alternate function
	GPIO_PORTD_AFSEL_R &= ~GPIO_P_M;      // No alternate function
	GPIO_PORTE_AFSEL_R &= ~GPIO_P_M;      // No alternate function
	GPIO_PORTF_AFSEL_R &= ~GPIO_P_M;      // No alternate function
	
	
	
	GPIO_PORTF_DIR_R |= GPIO_P_M;         // PA output
	GPIO_PORTB_DIR_R |= GPIO_P_M;         // PB output
	GPIO_PORTE_DIR_R |= GPIO_P_M;         // PE output
	
	GPIO_PORTD_DIR_R &= ~GPIO_P_M;				// PD Input		
	
	
	
  GPIO_PORTF_DATA_R &= ~GPIO_P_M;				// Initalize the first 7 seg to be off
	GPIO_PORTB_DATA_R &= ~GPIO_P_M;				// Initalize the sec 7 seg to be off
	GPIO_PORTE_DATA_R &= ~GPIO_P_M;				// Initalize the third 7 seg to be off
}
 
 
 


void Systick_Wait(uint32_t name){
		NVIC_ST_CTRL_R = 0;
		NVIC_ST_RELOAD_R = name-1;
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x00000005;
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}


void Systick_Wait10ms (uint32_t name){
		uint32_t i;
		for (i = 0; i < name ; i++)
				Systick_Wait(160000);
}

void DisplayNumber_FirstSeg(int num)
{
	switch (num) {
		case 0:
			GPIO_PORTF_DATA_R |= 0b00000000;						// 0
		  GPIO_PORTF_DATA_R &= 0b11110000;
		break;                 
		case 1:                
			GPIO_PORTF_DATA_R |= 0b00000001;						// 1
		  GPIO_PORTF_DATA_R &= 0b11110001;	
		break;                 
		case 2:                
			GPIO_PORTF_DATA_R |= 0b00000010;					// 2
			GPIO_PORTF_DATA_R &= 0b11110010;
		break;                 
		case 3:                
			GPIO_PORTF_DATA_R |= 0b00000011;					// 3
		  GPIO_PORTF_DATA_R &= 0b11110011;
		break;                 
		case 4:                
			GPIO_PORTF_DATA_R |= 0b00000100;					// 4
			GPIO_PORTF_DATA_R &= 0b11110100;
		break;                 
		case 5:                
			GPIO_PORTF_DATA_R |= 0b00000101;					// 5 
			GPIO_PORTF_DATA_R &= 0b11110101;
		break;                 
		case 6:                
			GPIO_PORTF_DATA_R |= 0b00000110;					// 6
			GPIO_PORTF_DATA_R &= 0b11110110;
		break;                 
		case 7:          
			//	if (y != 1){
			GPIO_PORTF_DATA_R |= 0b00000111;					// 7
			GPIO_PORTF_DATA_R &= 0b11110111;//}
			//	else{ y = 0;} 
		break;                 
		case 8:                
			GPIO_PORTF_DATA_R |= 0b00001000;					// 8
			GPIO_PORTF_DATA_R &= 0b11111000;
		break;                 
		case 9:                
			GPIO_PORTF_DATA_R |= 0b00001001;					// 9
			GPIO_PORTF_DATA_R &= 0b11111001;
		break;                 
		default:               
			GPIO_PORTF_DATA_R |= 0b00000000;
		  GPIO_PORTF_DATA_R &= 0b11110000;
		break;
	}
}


void DisplayNumber_SecondSeg(int num)
{
	switch (num) {
		
		case 0:
			GPIO_PORTB_DATA_R |= 0b00000000;
		  GPIO_PORTB_DATA_R &= 0b11110000;
		break;
		case 1:
			GPIO_PORTB_DATA_R |= 0b00000001;
		  GPIO_PORTB_DATA_R &= 0b11110001;
		break;
		case 2:
			GPIO_PORTB_DATA_R |= 0b00000010;
		  GPIO_PORTB_DATA_R &= 0b11110010;
		break;
		case 3:
			GPIO_PORTB_DATA_R |= 0b00000011;
		  GPIO_PORTB_DATA_R &= 0b11110011;
		break;
		case 4:
			GPIO_PORTB_DATA_R |= 0b00000100;
		  GPIO_PORTB_DATA_R &= 0b11110100;
		break;
		case 5:
			GPIO_PORTB_DATA_R |= 0b00000101;
		  GPIO_PORTB_DATA_R &= 0b11110101;
		break;
		case 6:
			GPIO_PORTB_DATA_R |= 0b00000110;
		  GPIO_PORTB_DATA_R &= 0b11110110;
		break;
		case 7:
			GPIO_PORTB_DATA_R |= 0b00000111;
		  GPIO_PORTB_DATA_R &= 0b11110111;
		break;
		case 8:
			GPIO_PORTB_DATA_R |= 0b00001000;
		  GPIO_PORTB_DATA_R &= 0b11111000;
		break;
		case 9:
			GPIO_PORTB_DATA_R |= 0b00001001;
		  GPIO_PORTB_DATA_R &= 0b11111001;			
		break;
		default: 
			GPIO_PORTB_DATA_R |= 0b00000000;
		  GPIO_PORTB_DATA_R &= 0b11110000;
		break;
	}
}


void DisplayNumber_ThirdSeg(int num)
{
	switch (num) {
		
		case 0:
			GPIO_PORTE_DATA_R |= 0b00000000;
		  GPIO_PORTE_DATA_R &= 0b11110000;
		break;
		case 1:
			GPIO_PORTE_DATA_R |= 0b00000001;
		  GPIO_PORTE_DATA_R &= 0b11110001;
		break;
		case 2:
			GPIO_PORTE_DATA_R |= 0b00000010;
		  GPIO_PORTE_DATA_R &= 0b11110010;
		break;
		case 3:
			GPIO_PORTE_DATA_R |= 0b00000011;
		  GPIO_PORTE_DATA_R &= 0b11110011;
		break;
		case 4:
			GPIO_PORTE_DATA_R |= 0b00000100;
		  GPIO_PORTE_DATA_R &= 0b11110100;
		break;
		case 5:
			GPIO_PORTE_DATA_R |= 0b00000101;
		  GPIO_PORTE_DATA_R &= 0b11110101;
		break;
		case 6:
			GPIO_PORTE_DATA_R |= 0b00000110;
		  GPIO_PORTE_DATA_R &= 0b11110110;
		break;
		case 7:
			GPIO_PORTE_DATA_R |= 0b00000111;
		  GPIO_PORTE_DATA_R &= 0b11110111;
		break;
		case 8:
			GPIO_PORTE_DATA_R |= 0b00001000;
		  GPIO_PORTE_DATA_R &= 0b11111000;
		break;
		case 9:
			GPIO_PORTE_DATA_R |= 0b00001001;
		  GPIO_PORTE_DATA_R &= 0b11111001;			
		break;
		default: 
			GPIO_PORTE_DATA_R |= 0b00000000;
		  GPIO_PORTE_DATA_R &= 0b11110000;
		break;	
	}
}
 int decimalToBinary(int n) {
    int remainder; 
 int binary = 0, i = 1;
  
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}
