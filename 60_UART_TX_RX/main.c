// Plug a female-female wire onto the P1.2 (TXD) pin and the P1.1 (RXD) pin (same wire).

#include <msp430.h>

void clock_config(void);
void uart_settings(void);

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    P1DIR = BIT0;
    P1OUT = 0x00;

    clock_config();
    uart_settings();

    UCA0TXBUF = 0x56;

    while(1) {
        if(IFG2 & UCA0RXIFG) {
            if(UCA0RXBUF == 0x56)
            {
                P1OUT |= BIT0;
            }
            else P1OUT &= ~ BIT0;

            IFG2 = IFG2 & (~UCA0RXIFG);
        }
    }
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_8MHZ;      // 8MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_8MHZ;      // BCSCTL1 register settings)
}

void uart_settings(void)
{
    P1SEL  = BIT1 | BIT2;       // P1.1 - UCA0RXD - USCI_A0 UART mode: receive data input (MSP430FR6989 - P4.3)
    P1SEL2 = BIT1 | BIT2;       // P1.2 - UCA0TXD - USCI_A0 UART mode: transmit data output (MSP430FR6989 - P4.2)
                                // UCA0RXD - P1SEL.x (1) - P1SEL2.x (1)
                                // UCA0TXD - P1SEL.x (1) - P1SEL2.x (1)

    UCA0CTL1 |= UCSWRST;        /* USCI Software Reset */
    UCA0CTL1 |= UCSSEL_2;       /* USCI 0 Clock Source: 2 */
                                // Bits 7-6 - 10b - SMCLK

    //UCA0CTL0 = UCPEN | UCPAR | UC7BIT | UCSPB;  // Parity enabled | Even parity | 7-bit data | Two stop bits

                                // 9600 baud - Table 15-4
    UCA0BR0  = 0x41;            /* USCI A0 Baud Rate 0 */
    UCA0BR1  = 0x03;            /* USCI A0 Baud Rate 1 */
    UCA0MCTL = 0x22;            /* USCI A0 Modulation Control Register */
                                // UCBRSx = 2 (Table 15-4 and Table 15-2. BITCLK Modulation Pattern)

    UCA0CTL1 &= ~UCSWRST;       // Takes UART out of SoftWare ReSeT
}
