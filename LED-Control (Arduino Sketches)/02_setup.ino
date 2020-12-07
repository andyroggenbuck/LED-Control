/* void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:

  cli();    // disable interrupts

  // set timer0 PWM (red & green pwm)
  TCCR0A = (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00) | (1 << WGM01);   // fast PWM mode, inverting
  TCCR0B = (1 << CS01);   // timer0 prescaler = 8
  OCR0A = PWMtableB[0][0];    // timer0A (red PWM) duty cycle
  OCR0B = PWMtableB[0][1];    // timer0B (green PWM) duty cycle

  // set timer1 PWM (interrupt driver)
  TCCR1A = (1 << COM1A1) | (1 << WGM10);   // fast PWM, 8-bit, non-inverting
  TCCR1B = (1 << CS11) | (1 << WGM12);   // timer1 prescaler = 8
  OCR1A = 0;    // timer1A duty cycle (point in cycle at which MUX interrupt is triggered)
  TIMSK1 |= (1 << OCIE1A);    // enable timer1A compare interrupt

  // set timer2 PWM (blue & white pwm)
  TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20) | (1 << WGM21);   // fast PWM mode, non-inverting
  TCCR2B = (1 << CS21);   // timer2 prescaler = 8
  OCR2A = PWMtableB[0][2];   // timer2A (blue PWM) duty cycle
  OCR2B = PWMtableB[0][3];   // timer2B (white PWM) duty cycle

  // synchronize timers
  GTCCR = (1 << TSM);   // activate timer synch mode
  GTCCR |= (1 << PSRASY) | (1 << PSRSYNC);    // reset & hold prescalers
  TCNT0 = 0;    // clear counters
  TCNT1 = 0;
  TCNT2 = 0;
  GTCCR &= ~(1 << TSM);   // start timers simultaneously

  UCSR0B &= ~(1 << RXEN0);  // disable UART receive on pin 0  

  pinMode(OE,OUTPUT);
  pinMode(RCK,OUTPUT);
  pinMode(SER,OUTPUT);
  pinMode(CLK,OUTPUT);
  
  pinMode(Rpwm,OUTPUT);
  pinMode(Gpwm,OUTPUT);
  pinMode(Bpwm,OUTPUT);
  pinMode(Wpwm,OUTPUT);

  digitalWrite(OE,HIGH);    // disable SR outputs
  digitalWrite(RCK,LOW);    // latch pin low
  digitalWrite(SER,LOW);    // serial output pin low
  digitalWrite(CLK,LOW);    // clock pin low
  
  sei();    // enable interrupts  
}
 */