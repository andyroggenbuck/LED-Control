/* ISR: Timer1 compare interrupt
 * disables LEDs, updates PWM duty,
 * shifts in data for next LED, enables LEDs
 */
ISR(TIMER1_COMPA_vect)
{
  PORTD |= (1 << OE);   // shift register output disable (LEDs off)
  
  /* update PWM duty values
   * [(LEDmux + LEDnum - 1) % LEDnum] expression shifts LED number by 1,
   * which compensates for PWM duty changes not taking effect until next cycle
   */
  OCR0A = PWMtableB[(LEDmux + LEDnum + 1) % LEDnum][0];    // red
  OCR0B = PWMtableB[(LEDmux + LEDnum + 1) % LEDnum][1];    // green
  OCR2A = PWMtableB[(LEDmux + LEDnum + 1) % LEDnum][2];    // blue  
  OCR2B = PWMtableB[(LEDmux + LEDnum + 1) % LEDnum][3];    // white
  
  // update SER bit
  if (LEDmux == 0)
    PORTD |= (1 << SER);   // if first LED, SER out = 1 (on)
  else
    PORTD &= ~(1 << SER);   // else SER out = 0 (off) 

  // Shift out SER bit:
  // pulse clock pin
  PORTD |= (1 << CLK);    // clock pin high
  PORTD &= ~(1 << CLK);   // clock pin low
  // pulse latch pin
  PORTD |= (1 << RCK);    // latch pin high
  PORTD &= ~(1 << RCK);   // latch pin low
  
  PORTD &= ~(1 << OE);    // enable SR outputs (LEDs)
  
  // advance LEDmux to next LED number
  if (LEDmux == (LEDnum - 1))
    LEDmux = 0;            // if last LED reached, reset LEDmux
  else
    LEDmux++;              // else increment LEDmux
}
