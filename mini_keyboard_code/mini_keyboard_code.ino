// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// Joystic librery by Matthew Heironimus
// 2016-11-24
//
// Code by Marcus Cazzola
// 2020-02-05
//--------------------------------------------------------------------

#include <Joystick.h>
#include <Keyboard.h>

byte shifting_pins[] = {10,16,14,15,18};
byte input_pins[] = {A6, A7, A8, A9}; //can use pins 4, 6, 8, 9, 10, 12 as analog pins. https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
byte joystick_button_pin = 18;
byte VRX = A1, VRY = A2;
byte ESCbuttonNum = 99;

char keys[] = {'z', 'a', 'q', '1', 'x', 's', 'w', '2', 'c', 'd', 'e', '3', 'v', 'f', 'r', '4', 'b', 'g', 't', '5'};

byte len_shifting_pins = sizeof(shifting_pins)/sizeof(shifting_pins[0]); //sizeof() = memory size
byte len_input_pins = sizeof(input_pins)/sizeof(input_pins[0]); //sizeof() = memory size

byte buttonsNum = len_shifting_pins * len_input_pins + 1; //"+1" becuse of joystick

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  buttonsNum, 0,       // Button Count, Hat Switch Count
  true, true, false,     // X, Y, Z Axis
  false, false, false,   // Rx, Ry, Rz (Rotation)
  false, false,          // rudder, throttle
  false, false, false);  // accelerator, brake, steering

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
    pinMode(shifting_pins[i], INPUT_PULLUP);
  }

  //joystick_button_pin set as input
  pinMode(joystick_button_pin, INPUT_PULLUP);

  Joystick.begin();
  Keyboard.begin();
}

void loop() {
  //Reads Joystick pins  
  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));

  if(analogRead(VRY) > 500+100)
  {
   Keyboard.press('9'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('9'); //97 = 'a'; 98 = 'b'
  }

    if(analogRead(VRY) < 500-100)
  {
   Keyboard.press('8'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('8'); //97 = 'a'; 98 = 'b'
  }

    if(analogRead(VRX) > 500+100)
  {
   Keyboard.press('7'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('7'); //97 = 'a'; 98 = 'b'
  }

    if(analogRead(VRY) < 500-100)
  {
   Keyboard.press('6'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('6'); //97 = 'a'; 98 = 'b'
  }
  

  //Reads buttons
  byte loop_times = 0;
  for(byte e = 0; e < len_input_pins; e++) //För varje input pin
  {
    for(byte i = 0; i < len_shifting_pins; i++) //Loop trought shifting_pins
    {
      pinMode(shifting_pins[i], OUTPUT); //Make shifing_pin an output
      digitalWrite(shifting_pins[i], LOW); //Make output LOW
      
        if(analogRead(input_pins[e]) < 700) //press button
        {
        Joystick.setButton(loop_times, 1); //For Debug
        Keyboard.press(keys[loop_times]); //97 = 'a'; 98 = 'b'
        }
        
        else //release button
        {
          Joystick.setButton(loop_times, 0); //For Debug
          Keyboard.release(keys[loop_times]); //97 = 'a'; 98 = 'b'
        }

      //Serial.println(analogRead(input_pins[e]));
      pinMode(shifting_pins[i], INPUT_PULLUP); //Make output an input again
      loop_times++;
    }
  }

  //Reads joystick_button_pin seperatly
  if(!digitalRead(joystick_button_pin)) //press button
      {
        Joystick.setButton(loop_times, 1); //For Debug
        Keyboard.press(97 + loop_times);
      }
      else //release button
      {
        Joystick.setButton(loop_times, 0); //For Debug
        Keyboard.release(97 + loop_times);
      }
}
