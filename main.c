#include "avr/io.h"
#include "avr/interrupt.h"
#include "main.h"
#include "isr.c"

void main(void)
{
    cli();    // disable interrupts

    // configure timer0: red & green PWM
    TCCR0A = (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) |    // fast PWM mode, inverting
             (1 << COM0B0) | (1 << WGM00) | (1 << WGM01);
    TCCR0B = (1 << CS01);       // timer0 prescaler = 8
    OCR0A = PWMtableB[0][0];    // timer0A (red PWM) duty cycle
    OCR0B = PWMtableB[0][1];    // timer0B (green PWM) duty cycle

    // configure timer1: output compare interrupt 
    TCCR1A = (1 << COM1A1) | (1 << WGM10);  // fast PWM, 8-bit, non-inverting
    TCCR1B = (1 << CS11) | (1 << WGM12);    // timer1 prescaler = 8
    OCR1A = 0;                              // timer1A output compare (point in cycle where MUX interrupt is triggered)
    TIMSK1 |= (1 << OCIE1A);                // enable timer1A compare interrupt

    // configure timer2: blue & white PWM
    TCCR2A = (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) |    // fast PWM mode, non-inverting
             (1 << COM2B0) | (1 << WGM20) | (1 << WGM21);
    TCCR2B = (1 << CS21);       // timer2 prescaler = 8
    OCR2A = PWMtableB[0][2];    // timer2A (blue PWM) duty cycle
    OCR2B = PWMtableB[0][3];    // timer2B (white PWM) duty cycle

    // synchronize timers
    GTCCR = (1 << TSM);                         // activate timer synch mode
    GTCCR |= (1 << PSRASY) | (1 << PSRSYNC);    // reset & hold prescalers
    TCNT0 = 0;                                  // clear all 3 counters
    TCNT1 = 0;
    TCNT2 = 0;
    GTCCR &= ~(1 << TSM);                       // start counters simultaneously

    UCSR0B &= ~(1 << RXEN0);        // disable UART receive on pin 0  

    // set PWM pins as output
    DDRD |= (1 << PORTD3) | (1 << PORTD5) | (1 << PORTD6);      // PD3 = white, PD5 = green, PD6 = red
    DDRB |= (1 << PORTB3);                                      // PB3 = blue

    // set shift register control pins as outputs
    // PD0 = RCK (latch), PD2 = OE (output enable), PD4 = SR (serial data), PD7 = CLK (serial clock)
    DDRD |= (1 << PORTD0) | (1 << PORTD2) | (1 << PORTD4) | (1 << PORTD7);

    sei();    // enable interrupts

    while (1)
    {
        __asm ("nop");
    }
}