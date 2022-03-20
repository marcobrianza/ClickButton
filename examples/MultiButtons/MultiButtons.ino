/* ClickButton library demo

  Demo of multiple ClickButton objects in an array.
  Same as MultiClicks example, but with 3 buttons and 3 LED's.

  Short clicks:

    Single click - Toggle LED on/off
    Double click - Blink      (Toggles LED 2 times/second)
    Triple click - Fast blink (Toggles LED 5 times/second)
    
  Long clicks (hold button for one second or longer on last click):
    
    Single-click - Slow blink   (Toggles LED every second)
    Double-click - Sloow blink  (Toggles LED every other second)
    Triple-click - Slooow blink (Toggles LED every three seconds)


  The circuit:
  - LEDs attached from pin 10,11 and 12 to resistors (say 220-ish ohms), other side of resistors to GND (ground)
  - Pushbuttons attached from pin 4,5 and 6 to GND
  No pullup resistor needed, using the Arduino's (Atmega's) internal pullup resistor in this example.

  Based on the Arduino Debounce example.

  2010, 2013 raron
 
 GNU GPLv3 license
*/

#include "ClickButton.h"

// Nr. of buttons in the array
const int buttons = 3;

// the LED
const int ledPin[buttons] = { 10, 11, 12 }; // Arduino pins to the LEDs
int ledState[buttons]     = { 0, 0, 0 };
int LEDfunction[buttons]  = { 0, 0, 0 };

// Arduino input pins from the buttons (these are not in an array for simplicity just now)
const int buttonPin1 = 4;
const int buttonPin2 = 5;
const int buttonPin3 = 6;

// Instantiate ClickButton objects in an array
ClickButton button[3] = {
  ClickButton (buttonPin1, LOW, CLICKBTN_PULLUP),
  ClickButton (buttonPin2, LOW, CLICKBTN_PULLUP),
  ClickButton (buttonPin3, LOW, CLICKBTN_PULLUP),
};




void setup()
{
  for (int i=0; i<buttons; i++)
  {
    pinMode(ledPin[i],OUTPUT);  

    // Setup button timers (all in milliseconds / ms)
    // (These are default if not set, but changeable for convenience)
    button[i].debounceTime   = 20;   // Debounce timer in ms
    button[i].multiclickTime = 250;  // Time limit for multi clicks
    button[i].longClickTime  = 1000; // Time until long clicks register
  }
}


void loop()
{
  // Go through each button and set the corresponding LED function
  for (int i=0; i<buttons; i++)
  {
    // Update state of all buitton
    button[i].Update();
  
    // Save click codes in LEDfunction, as clicks counts are reset at next Update()
    if (button[i].clicks != 0) LEDfunction[i] = button[i].clicks;
  

    // Simply toggle LED on single clicks
    // (Cant use LEDfunction like the others here,
    //  as it would toggle on and off all the time)
    if(button[i].clicks == 1) ledState[i] = !ledState[i];

    // blink faster if double clicked
    if(LEDfunction[i] == 2) ledState[i] = (millis()/500)%2;

    // blink even faster if triple clicked
    if(LEDfunction[i] == 3) ledState[i] = (millis()/200)%2;

    // slow blink (must hold down button. 1 second long blinks)
    if(LEDfunction[i] == -1) ledState[i] = (millis()/1000)%2;

    // slower blink (must hold down button. 2 second loong blinks)
    if(LEDfunction[i] == -2) ledState[i] = (millis()/2000)%2;

    // even slower blink (must hold down button. 3 second looong blinks)
    if(LEDfunction[i] == -3) ledState[i] = (millis()/3000)%2;
  }


  // update the LEDs
  for (int i=0; i<buttons; i++)
  {
    digitalWrite(ledPin[i],ledState[i]);
  }

}




