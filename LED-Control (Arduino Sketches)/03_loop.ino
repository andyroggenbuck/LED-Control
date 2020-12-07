/* void loop() {
  
  for (int i = 0; i < LEDnum; i++) {
    curveAdjust(i);  // curve-adjusts linear values & stores them to PWMtableB
  }
/*
  while (1) {
    Fade (Amber, 20, 0, 1);
    Fade (Amber, 20, 2, 3);
    Fade (Violet, 20, 0, 1);
    Fade (Amber, 20, 4, 5);
    Fade (Violet, 20, 2, 3);
    Fade (Violet, 20, 4, 5);
  }
*/


 /*
  // starting values for 8-LED color swirl  
  PWMtableA[0][0] = 0;
  PWMtableA[0][1] = 255;
  PWMtableA[0][2] = 0;

  PWMtableA[1][0] = 0;
  PWMtableA[1][1] = 159;
  PWMtableA[1][2] = 96;

  PWMtableA[2][0] = 0;
  PWMtableA[2][1] = 63;
  PWMtableA[2][2] = 192;

  PWMtableA[3][0] = 31;
  PWMtableA[3][1] = 0;
  PWMtableA[3][2] = 224;

  PWMtableA[4][0] = 127;
  PWMtableA[4][1] = 0;
  PWMtableA[4][2] = 128;

  PWMtableA[5][0] = 223;
  PWMtableA[5][1] = 0;
  PWMtableA[5][2] = 32;

  // execute 8-LED color swirl
  while (1) {
    for (int i = 0; i < LEDnum; i++) {
      rainbow(PWMtableA[i][0], PWMtableA[i][1], PWMtableA[i][2]);       // updates value of current LED in linear PWM table
      curveAdjust(i);  // curve-adjusts linear values & stores them to PWMtableB
    }
    Delay(10);
  }
  
}
 */