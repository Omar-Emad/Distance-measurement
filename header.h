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

#ifndef HEADER_H_
#define HEADER_H_

#include "C:/Keil/TM4C123Valvanoware/inc/tm4c123gh6pm.h"
#include <stdint.h>

/**********************************************************************
 *                 Preprocessor Configration                          *
 **********************************************************************/
#define _16MHz_1clock  62e-9 // Value of 1clock cycle in nanoseconds
#define MULTIPLIER  17400  // Derived from speed of sound  5882
#define ECHO (1U<<6) /* PB6  Echo pin of the ultrasonic */
#define TRIGGER (1U<<7) /* PA7 (OUTPUT) trigger pin of the ultrasonic */

/**********************************************************************
 *                   Functions Prototype                              *
 **********************************************************************/

void SystemInit (){}
void portA_Init();
void PortE_Init();
void PortD_Init();	
void delay_Microsecond(uint32_t time);
void Timer0_init(void);
uint32_t measureD(void);

#endif /* HEADER_H_ */