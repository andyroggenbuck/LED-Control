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
    OCR0A = pwm_table_curved[0][0];    // timer0A (red PWM) duty cycle
    OCR0B = pwm_table_curved[0][1];    // timer0B (green PWM) duty cycle

    // configure timer1: output compare interrupt 
    TCCR1A = (1 << COM1A1) | (1 << WGM10);  // fast PWM, 8-bit, non-inverting
    TCCR1B = (1 << CS11) | (1 << WGM12);    // timer1 prescaler = 8
    OCR1A = 0;                              // timer1A output compare (point in cycle where MUX interrupt is triggered)
    TIMSK1 |= (1 << OCIE1A);                // enable timer1A compare interrupt

    // configure timer2: blue & white PWM
    TCCR2A = (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) |    // fast PWM mode, non-inverting
             (1 << COM2B0) | (1 << WGM20) | (1 << WGM21);
    TCCR2B = (1 << CS21);       // timer2 prescaler = 8
    OCR2A = pwm_table_curved[0][2];    // timer2A (blue PWM) duty cycle
    OCR2B = pwm_table_curved[0][3];    // timer2B (white PWM) duty cycle

    // synchronize timers
    GTCCR = (1 << TSM);                         // activate timer synch mode
    GTCCR |= (1 << PSRASY) | (1 << PSRSYNC);    // reset & hold prescalers
    TCNT0 = 0;                                  // clear all 3 counters
    TCNT1 = 0;
    TCNT2 = 0;
    GTCCR &= ~(1 << TSM);                       // start counters simultaneously

    UCSR0B &= ~(1 << RXEN0);        // disable UART receive on pin 0  

    // set PWM pins as output
    // PORTD3 = white, PORTD5 = green, PORTD6 = red
    // PORTB3 = blue
    DDRD |= (1 << PORTD3) | (1 << PORTD5) | (1 << PORTD6);
    DDRB |= (1 << PORTB3);

    // set shift register control pins as outputs
    // PORTD0 = RCK (latch), PORTDD2 = OE (output enable), PORTD4 = SR (serial data), PORTD7 = CLK (serial clock)
    DDRD |= (1 << PORTD0) | (1 << PORTD2) | (1 << PORTD4) | (1 << PORTD7);

    // set troubleshooting pin as output & initialize to 'off'
    // PORTB5 = Arduino pin 13
    DDRB |= (1 << PORTB5);
    PORTB &= ~(1 << PORTB5);

    led_mux = 0;     // initialize LED multiplex counter

    sei();    // enable interrupts

    // starting values for color swirl effect
    pwm_table_linear[0][0] = 0;
    pwm_table_linear[0][1] = 255;
    pwm_table_linear[0][2] = 0;

    pwm_table_linear[1][0] = 0;
    pwm_table_linear[1][1] = 159;
    pwm_table_linear[1][2] = 96;

    pwm_table_linear[2][0] = 0;
    pwm_table_linear[2][1] = 63;
    pwm_table_linear[2][2] = 192;

    pwm_table_linear[3][0] = 31;
    pwm_table_linear[3][1] = 0;
    pwm_table_linear[3][2] = 224;

    pwm_table_linear[4][0] = 127;
    pwm_table_linear[4][1] = 0;
    pwm_table_linear[4][2] = 128;

    pwm_table_linear[5][0] = 223;
    pwm_table_linear[5][1] = 0;
    pwm_table_linear[5][2] = 32;

    // execute color swirl
    while (1)
    {
        for (int i = 0; i < LED_NUM; i++)
        {
            // update values for current LED in linear PWM table
            rainbow(&pwm_table_linear[i][0], &pwm_table_linear[i][1], &pwm_table_linear[i][2]);
            // curve-adjust linear values & store them to pwm_table_curved
            curveAdjust(i);
        }
        delay(30);
    }
}


// Delay routine that doesn't use the timers
void delay (int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 100; j++)
        {
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        }
    }
}

void curveAdjust (int LED)
{
  pwm_table_curved[LED][0] = brightness[pwm_table_linear[LED][0]];
  pwm_table_curved[LED][1] = brightness[pwm_table_linear[LED][1]];
  pwm_table_curved[LED][2] = brightness[pwm_table_linear[LED][2]];
  pwm_table_curved[LED][3] = brightness[pwm_table_linear[LED][3]];
}

// Rainbow Swirl algorithm
// Accepts 3 PWM values (Red, Green, Blue, NOT brightness-curve-adjusted)
// Modifies the values as necessary to create color swirl
void rainbow (int *R, int *G, int *B)
{
    if (*R == 0)
    {
        if (*G != 0)
        {
            (*B)++;
            (*G)--;
        } 
        else
        {
            (*R)++;
            (*B)--;
        }
    }
    else if (*G == 0) 
    {
        if (*B != 0) 
        {
            (*R)++;
            (*B)--;
        }
        else
        {
            (*G)++;
            (*R)--;
        }
    }
    else if (*B == 0)
    {
        if (*R != 0)
        {
            (*G)++;
            (*R)--;
        }
        else
        {
            (*B)++;
            (*G)--;
        }
    }
}