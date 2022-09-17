#include <msp430.h> 

main()
{
    long ones = 0;
    long tens = 0;
    long huns = 0;
    long thou = 0;
    long tnth = 0;
    long km = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    while(1) {
        for (tnth=0; tnth<10; tnth++) {
            for (thou=0; thou<10; thou++) {
                for (huns=0; huns<10; huns++) {
                    for (tens=0; tens<10; tens++) {
                        for (ones=0; ones<10; ones++) {
                            km = 10000*tnth + 1000*thou + 100*huns + 10*tens + ones;
                        }
                    }
                }
            }

        }
    km = 0;
    }
}
