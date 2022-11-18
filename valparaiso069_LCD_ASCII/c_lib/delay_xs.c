/*
 * delay_xs.c
 *
 * 11/2022
 *
 * A. Inácio Morais
 * anderson.morais@protonmail.com - inacio.morais@protonmail.com
 * +55 35 99161-9878
 *
 */


// ***** Header Files *********************************************************
#include "delay_xs.h"


// ***** Functions ************************************************************
void delay_us(unsigned int us, char MHz)
{
    TA1CCR0 = us * MHz;

    TA1CTL  = (TASSEL_2 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                    // MC_1: Timer A mode control: 1 - Up to CCR0

    while((TA1CTL & TAIFG) == 0);
    TA1CTL = TA1CTL & (~TAIFG);
}

void delay_ms(unsigned int ms, char MHz)
{
    unsigned int i;
    for (i=0;i<ms;i++) {
        delay_us(1000, MHz);
    }
}
