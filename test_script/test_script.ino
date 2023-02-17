byte shifting_pins[] = {A6, A7, A8, A9};
byte input_pins[] = {10,16,14,15,18};

byte len_shifting_pins = sizeof(shifting_pins)/sizeof(shifting_pins[0]); //sizeof() = memory size
byte len_input_pins = sizeof(input_pins)/sizeof(input_pins[0]); //sizeof() = memory size

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < len_input_pins; i++)
  {
    pinMode(input_pins[i], INPUT_PULLUP);
  }

  //All shifting pins sets to input
  for (byte i = 0; i < len_shifting_pins; i++)
  {
    pinMode(shifting_pins[i], OUTPUT);
    digitalWrite(shifting_pins[i], HIGH); //Make output LOW
  }

  digitalWrite(shifting_pins[1], LOW);

}

void loop() {
    for (byte i = 0; i < len_input_pins; i++)
  {
    Serial.print(i);
    Serial.print(" ");
    Serial.print(digitalRead(input_pins[i]));
    Serial.println();
  }

  delay(100);

}
