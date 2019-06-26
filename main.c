/**********************************************************************
 *
 * File Name: main.c
 * 
 * Author: Omar Emad
 *
 * Date Created: 12/3/2018
 *
 * Descriptio: this is the source file that include main fun. for Distance Meassure device 
 *
 ***********************************************************************/

#include "header.h"

int main(void)
{
    portA_Init();
    PortE_Init(); 
    PortD_Init();
	
	uint32_t distance ;
	uint32_t D1,D2,D3;
	uint32_t measure;
	
    //SYSCTL_RCGCGPIO_R |=(1U<<0); //Enable clock for PORTA 
    SYSCTL_RCGCGPIO_R |=(1U<<5); //Enable clock for PORTF 
    //GPIO_PORTA_DIR_R =TRIGGER; 
    GPIO_PORTF_DIR_R =BLUE_LED;
    //GPIO_PORTA_DEN_R |=(ECHO)|(TRIGGER);
    GPIO_PORTF_DEN_R |= BLUE_LED;
	
    while(1)
    {
        Timer0_init();
        distance=measureD();
	    measure=distance;
        
   	    D1=distance%10;  distance/=10;               //  D3 D2 D1
        D2=distance%10;  distance/=10;              //  D  E  A
        D3=distance%10;
	    D1*=4; D2*=2; D3*=2;
	   
        /* display the distance on 7 segmant */
        GPIO_PORTE_DATA_R =D2; 
        GPIO_PORTD_DATA_R =D3;
        GPIO_PORTA_DATA_R &=~0x3C;
        GPIO_PORTA_DATA_R |=D1;
	
        delay_Microsecond(10000);

    }
}