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
#include <Joystick.h>

//Class that keeps track of key_value
//and don't spam "release", so PC can turn off.
class Switch{
 public:
 
 bool is_pressed = false;
 char key_value;
 
 Switch(char kv){
  key_value = kv;
 }
 
 void pres(){
  Keyboard.press(key_value);
  is_pressed = true;
 }

 void releas(){
  if (is_pressed){
    Keyboard.release(key_value);
    //is_pressed = false;
  }
 }
};

byte shifting_pins[] = {A6, A7, A8, A9};
byte input_pins[] = {10,16,14,15,18};
byte joystick_button_pin = 18;
byte VRX = A1, VRY = A2;

byte len_shifting_pins = sizeof(shifting_pins)/sizeof(shifting_pins[0]); //sizeof() = memory size
byte len_input_pins = sizeof(input_pins)/sizeof(input_pins[0]); //sizeof() = memory size

Switch switches[] = {
  (KEY_ESC), ('2'), ('3'), ('4'), ('5'),
  ('q'), ('w'), ('e'), ('r'), ('t'),
  ('a'), ('s'), ('d'), ('f'), ('g'),
  ('z'), ('x'), ('c'), ('v'), ('b')
  };

Switch joystick_btn('n'), forward('9'), back('8'), right('7'), left('7');

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,       // Button Count, Hat Switch Count
  true, true, false,     // X, Y, Z Axis
  false, false, false,   // Rx, Ry, Rz (Rotation)
  false, false,          // rudder, throttle
  false, false, false);  // accelerator, brake, steering

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  Keyboard.begin();
  
  //input_pins
  for (byte i = 0; i < len_input_pins; i++)
  {
    pinMode(input_pins[i], INPUT_PULLUP);
  }

  //shifting_pins
  for (byte i = 0; i < len_input_pins; i++)
  {
    pinMode(shifting_pins[i], OUTPUT);
    digitalWrite(shifting_pins[i], HIGH);
  }

  //joystick
  pinMode(joystick_button_pin, INPUT_PULLUP);
  pinMode(VRX, INPUT_PULLUP);
  pinMode(VRY, INPUT_PULLUP);
}

void read_main_buttons()
{
  byte loop_times = 0;
  for(byte s = 0; s < len_shifting_pins; s++) //För varje input pin
  {
    digitalWrite(shifting_pins[s], LOW);
    for(byte i = 0; i < len_input_pins; i++) //Loop trought shifting_pins
    {
      //Serial.print(loop_times);
      //Serial.print(": ");
      //Serial.println(digitalRead(input_pins[i]));
      if(!digitalRead(input_pins[i]))
      {
        switches[loop_times].pres();
      }
      else
      {
        switches[loop_times].releas();
      }
      loop_times++;
    }
    digitalWrite(shifting_pins[s], HIGH);
  }
}

void read_joystick_button()
{
  if(!digitalRead(joystick_button_pin))
  {
    joystick_btn.pres();
  }
  else
  {
    joystick_btn.releas();
  }
}

void read_joystick_controller()
{
  Joystick.setXAxis(analogRead(VRX));
  Joystick.setYAxis(analogRead(VRY));
}

void read_joystick_keys(int dead_zone = 100)
{
  if(analogRead(VRX) > 512 + dead_zone)
  {
    forward.pres();
  }
        
  else
  {
    forward.releas();
  }

    if(analogRead(A0) < 500-100)
  {
   Keyboard.press('8'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('8'); //97 = 'a'; 98 = 'b'
  }

    if(analogRead(A1) > 500+100)
  {
   Keyboard.press('7'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('7'); //97 = 'a'; 98 = 'b'
  }

    if(analogRead(A1) < 500-100)
  {
   Keyboard.press('6'); //97 = 'a'; 98 = 'b'
   }
        
  else //release button
  {
   Keyboard.release('6'); //97 = 'a'; 98 = 'b'
  }
}


void loop() {
  read_main_buttons();
  //read_joystick_button();
  //read_joystick_controller();
  
  
  
  delay(1);
}
