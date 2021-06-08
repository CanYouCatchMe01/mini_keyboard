// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// Joystic librery by Matthew Heironimus
// 2016-11-24
//
// Code by Marcus Cazzola
// 2020-02-05
//--------------------------------------------------------------------

#include <Keyboard.h>

byte shifting_pins[] = {A6, A7, A8, A9};
byte input_pins[] = {10,16,14,15,18};
byte joystick_button_pin = 18;
byte VRX = A1, VRY = A2;
byte ESCbuttonNum = 99;

byte len_shifting_pins = sizeof(shifting_pins)/sizeof(shifting_pins[0]); //sizeof() = memory size
byte len_input_pins = sizeof(input_pins)/sizeof(input_pins[0]); //sizeof() = memory size

void setup() {
  Serial.begin(9600);
  //----Initialize Button pins----
  //Input pins
  for (byte i = 0; i < len_input_pins; i++)
  {
    pinMode(input_pins[i], INPUT_PULLUP);
  }

  //All shifting pins sets to input
  for (byte i = 0; i < len_shifting_pins; i++)
  {
    pinMode(shifting_pins[i], OUTPUT);
    digitalWrite(shifting_pins[i], HIGH);
  }
}

void loop() {
  delay(100);
  //Reads buttons
  byte loop_times = 0;
  for(byte s = 0; s < len_shifting_pins; s++) //För varje input pin
  {
    digitalWrite(shifting_pins[s], LOW);
    for(byte i = 0; i < len_input_pins; i++) //Loop trought shifting_pins
    {
      Serial.print(loop_times);
      Serial.print(": ");
      Serial.println(digitalRead(input_pins[i]));
      loop_times++;
    }
    digitalWrite(shifting_pins[s], HIGH);
  }
}
