# LED-Control
**Multiplexing, dimming &amp; color mixing of RGBW LEDs**

This project has been an educational exercise that attempts to combine multiplexing and pulse width modulation to control the color and dimming of an array of RGBW LEDs without needing a separate PWM signal for every color of every LED. I began programming the project in the Arduino IDE, but I've converted it into C in Visual Studio Code, using command line tools (gcc and avrdude) for compiling and downloading code to the Arduino Uno. This is mainly in an effort to avoid the simplified interface of the Arduino IDE and learn some software tools and skills that might be more broadly useful for embedded programming.

<p>
    <img src="/images/LED Controller schematic-page-001.jpg" width="220" height="240" />
</p>

Six common-anode RGBW LED strips are used for the LEDs. Each strip has its anode connected to power by a high side p-channel MOSFET, while four low side n-channel MOSFETs switch all cathodes of the same color to ground. A particular color of a particular strip only turns on when that strip is powered by the high side switch *and* that color's cathode is grounded by the low side switch; this allows every color of every strip to be controlled individually with a minimum of outputs from the Arduino.

Four Arduino outputs control a shift register, whose outputs drive the high side MOSFETs, and four more outputs provide PWM signals for the four low side MOSFETs. Currently only six LED strips are connected to the shift register's outputs, but two more could be added (or even more if another shift register is added) without needing any more outputs from the Arduino.

The four PWM signals are synchronized and operate at the same frequency (7.8kHz), and the LED strips are turned on one at a time, switching from one to the next at the same frequency as the PWM signals. The result is each LED strip stays powered for the duration of a single PWM period; then it is switched off, the PWM duty cycles are changed, and the next LED strip is powered on as the next PWM cycle starts.

A timer driven interrupt service routine handles switching the LEDs and updating the PWM duty cycle values. Even while using the Arduino IDE, direct register programming was needed to keep the ISR fast enough. Register programming was also needed to configure and synchronize the timer modules to generate the interrupts and PWM signals, so moving the project out of the Arduino IDE didn't actually require changing much code -- hardly any Arduino functions were being used.

This was also the first project I've done that involved high(ish) speed MOSFET switching, so that's been another good educational experience. I built discrete BJT gate driver circuits for the six p-channel MOSFETs. A gate driver IC might be a more efficient choice here, but designing the discrete circuits was a good exercise.
