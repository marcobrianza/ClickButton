/* ClickButton library demo

  Blinks a LED according to different clicks on one button.
  
  Short clicks:

    Single click - Toggle LED on/off
    Double click - Blink      (Toggles LED 2 times/second)
    Triple click - Fast blink (Toggles LED 5 times/second)
    
  Long clicks (hold button for one second or longer on last click):
    
    Single-click - Slow blink   (Toggles LED every second)
    Double-click - Sloow blink  (Toggles LED every other second)
    Triple-click - Slooow blink (Toggles LED every three seconds)


  The circuit:
  - LED attached from pin 10 to resistor (say 220-ish ohms), other side of resistor to GND (ground)
  - pushbutton attached from pin 4 to GND
  No pullup resistor needed, using the Arduino's (Atmega's) internal pullup resistor in this example.

  Based on the Arduino Debounce example.

  2010, 2013 raron
 
 GNU GPLv3 license
*/

#include "ClickButton.h"

// the LED
const int ledPin = 10;
int ledState = 0;

// the Button
const int buttonPin1 = 4;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

// Arbitrary LED function 
int LEDfunction = 0;


void setup()
{
  pinMode(ledPin,OUTPUT);  

  // Setup button timers (all in milliseconds / ms)
  // (These are default if not set, but changeable for convenience)
  button1.debounceTime   = 20;   // Debounce timer in ms
  button1.multiclickTime = 250;  // Time limit for multi clicks
  button1.longClickTime  = 1000; // time until "held-down clicks" register
}


void loop()
{
  // Update button state
  button1.Update();

  // Save click codes in LEDfunction, as click codes are reset at next Update()
  if (button1.clicks != 0) LEDfunction = button1.clicks;
  

  // Simply toggle LED on single clicks
  // (Cant use LEDfunction like the others here,
  //  as it would toggle on and off all the time)
  if(button1.clicks == 1) ledState = !ledState;

  // blink faster if double clicked
  if(LEDfunction == 2) ledState = (millis()/500)%2;

  // blink even faster if triple clicked
  if(LEDfunction == 3) ledState = (millis()/200)%2;

  // slow blink (must hold down button. 1 second long blinks)
  if(LEDfunction == -1) ledState = (millis()/1000)%2;

  // slower blink (must hold down button. 2 second loong blinks)
  if(LEDfunction == -2) ledState = (millis()/2000)%2;

  // even slower blink (must hold down button. 3 second looong blinks)
  if(LEDfunction == -3) ledState = (millis()/3000)%2;


  // update the LED
  digitalWrite(ledPin,ledState);
}
