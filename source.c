/**********************************************************************
 *
 * File Name: header.h
 * 
 * Author: Omar Emad
 *
 * Date Created: 12/3/2018
 *
 * Descriptio: this is the header file for Distance Meassure device 
 *
 ***********************************************************************/

#include "header.h"

/**********************************************************************
 *                       Global Variable                              *
 **********************************************************************/

uint32_t highEdge,lowEdge;
uint32_t ddistance; // Distance in centimeters

/**********************************************************************
 *                       Functions Definitions                        *
 **********************************************************************/

uint32_t measureD(void)
{
 
    GPIO_PORTA_DATA_R &=~TRIGGER;    //trigger = 0
    delay_Microsecond(12);
    GPIO_PORTA_DATA_R |= TRIGGER;     // trigger = 1
    delay_Microsecond(12);
    GPIO_PORTA_DATA_R &=~TRIGGER;        // triger = 0

    // Capture firstEgde i.e. rising edge
    TIMER0_ICR_R =4;          //clear the flag
    while((TIMER0_RIS_R & 4)==0){}; // wait till the flag will be 1 --> it means that the edge has come   
    highEdge = TIMER0_TAR_R;

    // Capture secondEdge i.e. falling edge 
    TIMER0_ICR_R =4; //clear timer capture flag
    while((TIMER0_RIS_R & 4) ==0){};        //wait till the flag will be 1 --> it means that the edge has come
    lowEdge = TIMER0_TAR_R;

    ddistance = lowEdge -highEdge;
    ddistance = _16MHz_1clock *(double) MULTIPLIER *(double)ddistance;

    return ddistance;

} 

void Timer0_init(void)
{
    SYSCTL_RCGCTIMER_R |=(1U<<0);  // activate timer 0

    SYSCTL_RCGCGPIO_R |=(1U<<1);    // avtivate port B
    GPIO_PORTB_DIR_R &=~ECHO;
    GPIO_PORTB_DEN_R |=ECHO;
    GPIO_PORTB_AFSEL_R |=ECHO;
    GPIO_PORTB_PCTL_R &=~0x0F000000;
    GPIO_PORTB_PCTL_R |= 0x07000000;

    TIMER0_CTL_R &=~1;   // disable timer 0
    TIMER0_CFG_R =4;     // make it 16 or 32 bit mode
    TIMER0_TAMR_R = 0x17;   // set the mode of the timer (capture  mode + count up + edge time)
    TIMER0_CTL_R |=0x0C;      // set it on both edge mode
    TIMER0_CTL_R |=1;    // enable timer 
}

void delay_Microsecond(uint32_t time)
{
    int i;

    SYSCTL_RCGCTIMER_R	|= (1U<<1); 
        for(i=0;i<5;i++){}
            i=0;
    TIMER1_CTL_R=0;
    TIMER1_CFG_R=0x04;
    TIMER1_TAMR_R=0x02;
    TIMER1_TAILR_R= 16-1;       // 16 should be changed depending on the freq 
    TIMER1_ICR_R =0x1;
    TIMER1_CTL_R |=0x01;

    for(i=0;i<time;i++)
    { 
        while((TIMER1_RIS_R & 0x1)==0);
        TIMER1_ICR_R= 0x1; 
    }
}


void portA_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x00000001;  // 1) activate clock for Port A
    int x=10000 ;
    //GPIO_PORTD_PUR_R = 0xFF;
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R = 0x0FF;
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTA_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTA_DIR_R = 0xFF;          // 5) PF4,PF0 in, PF3-1 out
    GPIO_PORTA_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    //GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
    GPIO_PORTA_DEN_R = 0xFF;          // 7) enable digital I/O on PF4-0
	
}


void PortE_Init(void)
{ 
    SYSCTL_RCGCGPIO_R |= 0x000010;  // 1) activate clock for Port E
    int x=10000 ;
    //GPIO_PORTE_PUR_R = 0xFF; 
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R = 0xFF;           // allow changes to PF4-0
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTE_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTE_DIR_R = 0xFF;          // 5) PF4,PF0 in, PF3-1 out
    GPIO_PORTE_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    //GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
    GPIO_PORTE_DEN_R = 0xFF;          // 7) enable digital I/O on PF4-0
}


void PortD_Init(void)
{ 
    SYSCTL_RCGCGPIO_R |= 0x00000008;  // 1) activate clock for Port F
    int x=10000 ;
    //GPIO_PORTD_PUR_R = 0xFF;
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R = 0x1F;
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PF
    GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
    GPIO_PORTD_DIR_R = 0xFF;          // 5) PF4,PF0 in, PF3-1 out
    GPIO_PORTD_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
    //GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
    GPIO_PORTD_DEN_R = 0xFF;          // 7) enable digital I/O on PF4-0
}

