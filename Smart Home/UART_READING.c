#include "UART_READING.h"
#include "tm4c123gh6pm.h"

void UART_INIT(){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	
	UART0_CTL_R &= ~UART_CTL_UARTEN;
	UART0_IBRD_R = 520;    													// those values will be set depending on the baudrate init from the other tiva
  UART0_FBRD_R = 53;															// those values will be set depending on the baudrate init from the other tiva
	UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R |= UART_CTL_UARTEN;
	
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) | (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	GPIO_PORTA_DEN_R |= 0x03;
}

uint8_t Reading (){
	// int x = (UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE ? 0:1;
	while (!((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE))
				return (uint8_t)(UART0_DR_R&0xFF);
	
}