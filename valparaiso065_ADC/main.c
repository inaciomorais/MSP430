#include <msp430.h>

void adc_setup(void);

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    P1DIR = BIT0;

    adc_setup();

    while(1) {
        ADC10CTL0 |= ENC + ADC10SC;     /* ENC - ADC10 Enable Conversion */
                                        /* ADC10SC - ADC10 Start Conversion */

        if (ADC10MEM > 0x200) {         // if input > 1.65V
            P1OUT = BIT0;
        }
        else {
            P1OUT &= ~BIT0;
        }
    }
}

void adc_setup(void)
{
    ADC10CTL0 = ADC10SHT_2 | ADC10ON;    /*SREF_0 - VR+ = AVCC and VR- = AVSS */
                                         /* ADC10SHT_2 - 16 x ADC10CLKs */
                                         /* ADC10ON - ADC10 On/Enable */

    ADC10CTL1 = INCH_4;     /* INCH_4 - Selects Channel 4 (A4)*/
                            /* SHS_0 - ADC10SC */
                            /* ADC10SSEL_0 - ADC10OSC */
                            /* CONSEQ_0 - Single channel single conversion */
    ADC10AE0 = BIT4;        // Analog input enable (A4)
}
