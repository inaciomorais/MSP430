/*
 * delay_xs.h
 *
 * 11/2022
 *
 * A. Inácio Morais
 * anderson.morais@protonmail.com - inacio.morais@protonmail.com
 * +55 35 99161-9878
 *
 */


//***** Header Files **********************************************************
#include <msp430.h>

#ifndef DELAY_XS_H_
#define DELAY_XS_H_


//***** Prototypes ************************************************************
void delay_us(unsigned int us, char MHz);
void delay_ms(unsigned int ms, char MHz);
//MHz: System Clock [MHz]


//***** Defines ***************************************************************


//***** Global Variables ******************************************************


#endif /* DELAY_XS_H_ */
