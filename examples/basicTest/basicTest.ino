
//use serial plotter to see the changes in time

#include "ClickButton.h"

const int buttonPin1 = 9;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);


void setup() {

  Serial.begin(115200);

}

void loop() {
  button1.Update();

  String s = String(button1.changed) + " " + String(button1.clicks);
  Serial.println(s);

  delay(10);
 
}
