#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED

void stop_watchdog_timer(void);
void timer0_will_count_up_for_500ms(void);
void make_P10_red_LED_an_output(void);
void toggle_red_LED(void);
void clear_timer0_elapsed_flag(void);
void timer0_count_for_500ms(void);
void timer0_in_up_mode(void);

unsigned int timer0_500ms_elapsed(void);

main()
{
    stop_watchdog_timer();

    timer0_will_count_up_for_500ms();

    make_P10_red_LED_an_output();

    while(1)
    {
        if( timer0_500ms_elapsed() ) {
            toggle_red_LED();
            clear_timer0_elapsed_flag();
        }
    }
}

void stop_watchdog_timer(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer
}

void make_P10_red_LED_an_output(void) {
    P1DIR = RED_LED;
}

void toggle_red_LED(void) {
    P1OUT = P1OUT ^ RED_LED;
}

void clear_timer0_elapsed_flag(void) {
    TA0CTL = TA0CTL & (~TAIFG);
}

unsigned int timer0_500ms_elapsed(void) {
    return TA0CTL & TAIFG;
}

void timer0_will_count_up_for_500ms(void) {
    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0.000064 s = 64 us

    timer0_count_for_500ms();
    timer0_in_up_mode();
}

void timer0_count_for_500ms(void) {
    TA0CCR0 = 7812;
}

void timer0_in_up_mode(void) {
    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
}
