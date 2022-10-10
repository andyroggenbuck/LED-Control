# LED Control

I did this project as an educational exercise to combine multiplexing and pulse width modulation to control the color and dimming of six RGBW LED strip lights. Although more practical solutions for lighting control already exist, this project gave me the opportunity to learn the timer modules of the ATmega328P in more detail, explore multiplexing using a shift register, and design some MOSFET switching circuits. I also used this project to learn how to program the Arduino without the Arduino IDE, instead using VS Code with command line tools GCC and AVRDUDE.

The simplified diagram below illustrates the hardware approach for controlling the LEDs. Each LED strip has a high side switch to connect its common anode to 12V, while each color has a low side switch to connect all cathodes of that color to ground. This allows each color of each LED strip to be controlled individually.

</br>
<p align="center">
  <img src="https://github.com/andyroggenbuck/LED-Control/blob/main/images/Block%20Diagram%20png.png" width="80%"></br>
  <i>Simplified hardware diagram</i>
</p>
</br>

The timing diagram below shows how this hardware scheme is used to implement multiplexed PWM. Each LED strip is powered on in sequence, while the synchronized PWM signals on the low side switches activate each color for the required duration for each strip. The switching frequency is about 7.8kHz. At the end of each cycle, an interrupt service routine changes the PWM duty cycles as required for the color of the next LED strip in the sequence. The PWM signals shown below are arbitrary; the actual pulse widths are determined by values stored in a lookup table. The program's main routine can create lighting effects by changing the values in the lookup table while the multiplexing routine runs.

</br>
<p align="center">
  <img src="https://github.com/andyroggenbuck/LED-Control/blob/main/images/Timing%20Diagram.png" width="90%"></br>
  <i>Timing diagram</i>
</p>
</br>

The schematic below shows the hardware in more detail. Six outputs from the shift register IC1 generate the LED Enable signals, while four outputs from the Arduino control the shift register. The LED Enable signals are level-shifted by discrete BJT gate driver circuits to drive the high side MOSFETS Q4 and Q12. A gate driver IC would likely be more economical, but building the discrete gate drivers was another good educational exercise. The Arduino generates the four PWM signals used to drive the low side MOSFETS Q5-Q8, which performed sufficiently well without gate drivers in this application. Pull-down resistors on the high side MOSFETS and pull-ups on the low side ensure that the LEDs turn off immediately when the MOSFETS turn off, eliminating any LEDs glowing when they're not supposed to.

</br>
<p align="center">
  <img src="https://github.com/andyroggenbuck/LED-Control/blob/main/images/LED%20Controller%20schematic%20v2.jpg" width = "100%"></br>
  <i>Schematic</i>
</p>
</br>

The device prototype, built on a breadboard, is shown below.

</br>
<p align="center">
    <img src="https://github.com/andyroggenbuck/LED-Control/blob/main/images/Breadboard%20photo.jpg" width = "90%"></br>
    <i>Device prototype</i>
</p>
</br>

## Conclusions

The benefit of using the shift register to implement multiplexing was minimal in this application. Four Arduino outputs were used to control six shift register outputs, saving only two Arduino pins. The output-saving benefit would be more significant if more LEDs were added -- the two unused shift register outputs could be utilized, and even more outputs could be gained by cascading another shift register. But the downside is that in this case only one LED is lit at a time, so as more are added, they all get dimmer and the overall multiplexing frequency gets slower. Still, a significant number of LEDs could be controlled individually in an application where high-intensity lighting is not required.
