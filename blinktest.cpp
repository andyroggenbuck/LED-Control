#include "avr/io.h"

void delay(unsigned long time) 
{
    while (time > 0) 
    {
        time--;
        __asm ("nop");
    }
}

int main(void) 
{
    DDRB |= (1 << PORTB5);      // port B pin 5 set to output

    while (1) 
    {
        PORTB ^= (1 << PORTB5);  // toggle port B pin 5
        delay(1000000);
    }

    return 0;
}

// adding stuff for 2nd commit