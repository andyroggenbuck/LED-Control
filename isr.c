/* ISR: Timer1 compare interrupt
 * disables LEDs, updates PWM duty,
 * shifts in data for next LED, enables LEDs
 */
ISR(TIMER1_COMPA_vect)
{
  PORTD |= (1 << OE);   // shift register output disable (LEDs off)
  
  /* update PWM duty values
   * [(led_mux + LED_NUM - 1) % LED_NUM] expression shifts LED number by 1,
   * which compensates for PWM duty changes not taking effect until next cycle
   */
  OCR0A = pwm_table_curved[(led_mux + LED_NUM + 1) % LED_NUM][0];    // red
  OCR0B = pwm_table_curved[(led_mux + LED_NUM + 1) % LED_NUM][1];    // green
  OCR2A = pwm_table_curved[(led_mux + LED_NUM + 1) % LED_NUM][2];    // blue  
  OCR2B = pwm_table_curved[(led_mux + LED_NUM + 1) % LED_NUM][3];    // white
  
  // update SER bit
  if (led_mux == 0)
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
  
  // advance led_mux to next LED number
  if (led_mux == (LED_NUM - 1))
    led_mux = 0;            // if last LED reached, reset led_mux
  else
    led_mux++;              // else increment led_mux
}
