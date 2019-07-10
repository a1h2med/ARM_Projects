#include <stdint.h>
#include "C:\Keil\tm4c123gh6pm.h"
void init(){
	
	//temperature sensor
	/* enable clocks */
    SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
    SYSCTL_RCGCWTIMER_R |= 1;    /* enable clock to WTimer Block 0 */
 
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;          /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;
    ADC0_EMUX_R |= 0x5000;       /* timer trigger conversion seq 0 */
    ADC0_SSMUX3_R = 0;           /* get input from channel 0 */
    ADC0_SSCTL3_R |= 0x0E;       /* take chip temperature, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;           /* enable ADC0 sequencer 3 */
 
    /* initialize wtimer 0 to trigger ADC at 1 sample/sec */
    WTIMER0_CTL_R = 0;           /* disable WTimer before initialization */
    WTIMER0_CFG_R = 0x04;        /* 32-bit option */
    WTIMER0_TAMR_R = 0x02;       /* periodic mode and down-counter */
    WTIMER0_TAILR_R = 16000000;  /* WTimer A interval load value reg (1 s) */
    WTIMER0_CTL_R |= 0x20;       /* timer triggers ADC */
    WTIMER0_CTL_R |= 0x01;       /* enable WTimer A after initialization */
		
		
		
		
		
		

		/* UART1 initialization */
		
		
		SYSCTL_RCGCUART |= 2;     /* provide clock to UART1 */
    
 
		UART1_CTL = 0; /* disable UART1 */
                     UART1_IBRD = 104;   //need information about PR  
                     UART1_FBRD = 11;    //need information about PR
		UART1_CC = 0; /* use system clock */
		UART1_LCRH = 0x70; /* 8-bit, no parity, 1-stop bit, no FIFO */
		UART1_CTL = 0x301; /* enable UART1, TXE, RXE */
 
		
 
		
 
	
}
	
		
int main(void){
	 init();
	volatile int temperature;
	while(1) {
        while((ADC0_RIS_R & 8) == 0);   
                            			/* wait for conversion complete */
        temperature = 147 - (247 * ADC0_SSFIFO3_R) / 4096 ;
       			//kda m3ana eltemp hana5do w nb3to 3la el uart
	 while(UART_FR_R & 0x20 != 0){UART1_DATA_R= temperature ;}
				
		ADC0_ISC_R = 8;          /* clear completion flag */
	
		
			    }
	
}
