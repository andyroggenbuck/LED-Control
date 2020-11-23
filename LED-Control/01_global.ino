// shift register serial communication pins
#define OE 2    // pin 2: SR output enable (G-bar)
#define RCK 0   // pin 0: SR RCK (latch)
#define SER 4   // pin 4: SR serial data
#define CLK 7   // pin 7: SR serial clock

// PWM output pins
#define Rpwm 6    // pin 6: red PWM
#define Gpwm 5    // pin 5: green PWM
#define Bpwm 11   // pin 11: blue PWM
#define Wpwm 3    // pin 3: white PWM

#define LEDnum 6  // number of LEDs

// dimming values for predefined colors
#define Amber 255, 50, 0, 0
#define Violet 50, 0, 255, 0

int LEDmux = 0;   // MUX counter

// table of RGB dimming values (linear 0-255) [# of LEDs][4 PWM channels]
int PWMtableA[LEDnum][4] = {
  {0,0,0,255},
  {0,0,0,255},
  {0,0,0,255},
  {0,0,0,255},
  {0,0,0,255},
  {0,0,0,255},
};

// table of RGB dimming values (brightness-curve-adjusted) [# of LEDs][4 PWM channels]
int PWMtableB[LEDnum][4] = {
  {255,255,255,255},
  {255,255,255,255},
  {255,255,255,255},
  {255,255,255,255},
  {255,255,255,255},
  {255,255,255,255}
};

// brightness adjustment curve lookup table
const uint8_t brightness[] PROGMEM = {
  255,255,255,255,255,254,254,254,254,254,253,253,253,252,252,252,252,251,251,250,250,
  250,249,249,249,248,248,247,247,246,246,246,245,245,244,244,243,243,242,242,241,241,
  240,240,239,239,238,237,237,236,236,235,235,234,233,233,232,232,231,230,230,229,228,
  228,227,226,226,225,224,224,223,222,222,221,220,220,219,218,217,217,216,215,215,214,
  213,212,212,211,210,209,208,208,207,206,205,205,204,203,202,201,200,200,199,198,197,
  196,195,195,194,193,192,191,190,190,189,188,187,186,185,184,183,182,182,181,180,179,
  178,177,176,175,174,173,172,171,170,169,169,168,167,166,165,164,163,162,161,160,159,
  158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,140,139,138,137,
  136,135,134,133,132,131,130,129,128,127,126,124,123,122,121,120,119,118,117,116,114,
  113,112,111,110,109,108,107,105,104,103,102,101,100,98,97,96,95,94,93,91,90,89,88,87,
  85,84,83,82,81,79,78,77,76,75,73,72,71,70,69,67,66,65,64,62,61,60,59,57,56,55,54,52,
  51,50,48,47,46,45,43,42,41,39,38,37,36,34,33
};

// Prototypes:
// Fade function
void Fade (int R_end, int G_end, int B_end, int W_end, int N_steps, 
  int LED_A, int LED_B = LEDnum, int LED_C = LEDnum, int LED_D = LEDnum, 
  int LED_E = LEDnum, int LED_F = LEDnum);

// Rainbow swirl algorithm: updates RGB PWM values
void rainbow (int &R, int &G, int &B);

// Brightness curve adjust function
void curveAdjust (int LED, int R, int G, int B, int W);

// blocking delay function that doesn't use the timers
void Delay (int length);
