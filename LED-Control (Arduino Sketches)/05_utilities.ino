/* 
 * function to adjust linear PWM values to curve-adjusted values 
 * Accepts LED number. 
 * Transforms linear values for specified LED in PWMtableA to curve-adjusted values and stores them to corresponding LED in PWMtableB.
 */
/* void curveAdjust (int LED) {
  PWMtableB[LED][0] = pgm_read_byte(&brightness[PWMtableA[LED][0]]);
  PWMtableB[LED][1] = pgm_read_byte(&brightness[PWMtableA[LED][1]]);
  PWMtableB[LED][2] = pgm_read_byte(&brightness[PWMtableA[LED][2]]);
  PWMtableB[LED][3] = pgm_read_byte(&brightness[PWMtableA[LED][3]]);
}


// Delay routine that doesn't use the timers
void Delay (int length) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 100; j++) {
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
 */