/* ClickButton LED fader demo

 LED on/off and fading up/down via one button
 
 Short press turns LED on or off.
 Long press (over one second) fades the LED and changes direction for each press

 The circuit:
 - LED attached from pin 10 to resistor (say 220-ish ohms), other side of resistor to GND (ground)
 - Pushbutton attached from pin 4 to GND
 No pullup resistor needed, using the Arduino's (Atmega's) internal pullup resistor in this example.

 
 2013.02.17 - raron
*/

#include "ClickButton.h"


// the LED
const int ledPin = 10;
int ledState = 0;

// the Button
const int buttonPin1 = 4;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

// Fade variables
int fadeValue = 64;
boolean fadeUp = false;    // false means fade down
boolean oldFadeUp = fadeUp;
const long fadeDelay = 10; // Time in milliseconds between fade steps
long adjustFaderTime = 0;  // Time to adjust the fader

// other
long currentTime;
int function = 0;


void setup()
{
  pinMode(ledPin,OUTPUT);  
}


void loop()
{
  currentTime = (long)millis();

  button1.Update();

  if (button1.clicks != 0) function = button1.clicks;
  
  // Toggle LED on single clicks
  if(button1.clicks == 1) ledState = !ledState;

  // fade if button is held down during single-click
  if(function == -1 && button1.depressed == true)
  {
    ledState = true;  // force lights on, since we want to fade it up or down
    
    if (oldFadeUp == fadeUp) fadeUp = !fadeUp; // Switch direction
    
    if ( currentTime - adjustFaderTime > fadeDelay)
    {
      adjustFaderTime = currentTime + fadeDelay;
      if (fadeUp) fadeValue++; else fadeValue--;

      // Some boundary checking
      // Using signed ints, we can check for below 0 and above 255 (byte limit)
      if (fadeValue > 255) fadeValue = 255;
      if (fadeValue < 0)   fadeValue = 0;
      
    }

  } else {
    // Save old fade direction for next time
    oldFadeUp = fadeUp;
    // Reset function
    function = 0;
  }
  

  // update the LED
  if (ledState) analogWrite(ledPin,fadeValue); else analogWrite(ledPin, 0);
}
