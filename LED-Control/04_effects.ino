/*
 * Fade function: accepts desired ending color values, # of steps to get there, and which LEDs to operate on.
 * Assumes all LEDs chosen are starting from the same color as the first one listed (LED_A).
 */
void Fade (int R_end, int G_end, int B_end, int W_end, int N_steps, int LED_A, int LED_B, int LED_C, int LED_D, int LED_E, int LED_F) 
{
  float R_float = (float) PWMtableA[LED_A][0];    // acquire starting color values as floating point variables
  float G_float = (float) PWMtableA[LED_A][1];
  float B_float = (float) PWMtableA[LED_A][2];
  float W_float = (float) PWMtableA[LED_A][3];

  float R_inc = (R_end - R_float) / N_steps;    // calculate size of increment needed for each color
  float G_inc = (G_end - G_float) / N_steps;
  float B_inc = (B_end - B_float) / N_steps;
  float W_inc = (W_end - W_float) / N_steps;

  for (int i = 0; i < N_steps; i++) {           // 
    R_float += R_inc;
    G_float += G_inc;
    B_float += B_inc;
    W_float += W_inc;

    PWMtableA[LED_A][0] = round(R_float);
    PWMtableA[LED_A][1] = round(G_float);
    PWMtableA[LED_A][2] = round(B_float);
    PWMtableA[LED_A][3] = round(W_float);
    curveAdjust(LED_A);
    
    if (LED_B != LEDnum) {
      PWMtableA[LED_B][0] = round(R_float);
      PWMtableA[LED_B][1] = round(G_float);
      PWMtableA[LED_B][2] = round(B_float);
      PWMtableA[LED_B][3] = round(W_float);
      curveAdjust(LED_B);
    }
    if (LED_C != LEDnum) {
      PWMtableA[LED_C][0] = round(R_float);
      PWMtableA[LED_C][1] = round(G_float);
      PWMtableA[LED_C][2] = round(B_float);
      PWMtableA[LED_C][3] = round(W_float);
      curveAdjust(LED_C);
    }
    if (LED_D != LEDnum) {
      PWMtableA[LED_D][0] = round(R_float);
      PWMtableA[LED_D][1] = round(G_float);
      PWMtableA[LED_D][2] = round(B_float);
      PWMtableA[LED_D][3] = round(W_float);
      curveAdjust(LED_D);
    }
    if (LED_E != LEDnum) {
      PWMtableA[LED_E][0] = round(R_float);
      PWMtableA[LED_E][1] = round(G_float);
      PWMtableA[LED_E][2] = round(B_float);
      PWMtableA[LED_E][3] = round(W_float);
      curveAdjust(LED_E);
    }
    if (LED_F != LEDnum) {
      PWMtableA[LED_F][0] = round(R_float);
      PWMtableA[LED_F][1] = round(G_float);
      PWMtableA[LED_F][2] = round(B_float);
      PWMtableA[LED_F][3] = round(W_float);
      curveAdjust(LED_F); 
    }

    Delay(100);
  }
}


// Rainbow Swirl algorithm
// Accepts 3 PWM values (Red, Green, Blue, NOT brightness-curve-adjusted)
// Modifies the values as necessary to create color swirl
void rainbow (int &R, int &G, int &B) {
  if (R == 0){
    if (G != 0) {
      B++;
      G--;
    } else {
      R++;
      B--;
    }
  }
  else if (G == 0) {
    if (B != 0) {
      R++;
      B--;
    } else {
      G++;
      R--;
    }
  }
  else if (B == 0) {
    if (R != 0) {
      G++;
      R--;
    } else {
      B++;
      G--;
    }
  }
}
