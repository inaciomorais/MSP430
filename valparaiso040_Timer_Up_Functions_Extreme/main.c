#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
#define _SMCLK  0x0200
#define _UP     0x0010
#define _TAIFG  0x0001
//#define _ID_2   0x40        // Input divider - /2
//#define _ID_4   0x80        // Input divider - /4
#define _ID_8   0xC0        // Input divider - /8
//#define _DIV_2  0x02        // Divider for SMCLK - /2
//#define _DIV_4  0x04        // Divider for SMCLK - /4
#define _DIV_8  0x06        // Divider for SMCLK - /8
//_ID_8 and _DIV_8 = 0.00005818182 s

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
    TA0CTL = TA0CTL & (~_TAIFG);
}

unsigned int timer0_500ms_elapsed(void) {
    return TA0CTL & _TAIFG;
}

void timer0_will_count_up_for_500ms(void) {
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2
    timer0_count_for_500ms();
    timer0_in_up_mode();
}

void timer0_count_for_500ms(void) {
    TA0CCR0 = 8594;
}

void timer0_in_up_mode(void) {
    TA0CTL  = _SMCLK | _ID_8 | _UP;
}
