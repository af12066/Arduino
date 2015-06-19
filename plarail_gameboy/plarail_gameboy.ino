const int trig01 = 3; // 測定開始・終了用
const int trig02 = 4; // 距離測定用
const int button = 2; // ボタンを押して開始

char c;

int i = 1;

boolean trigSwitch01 = true;
boolean trigSwitch02 = false;

void setup() {
  pinMode(trig01, OUTPUT);
  pinMode(trig02, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(button) == LOW) {}
  delay(5000);
  Serial.print("r");
  PORTD |= _BV(3);

  while (true) {
    if (Serial.available() > 0) {

      c = Serial.read();
      if ( c == i ) {
        trigSwitch02 = !trigSwitch02;
        digitalWrite(trig02, trigSwitch02);
        i++;
      }
      if (c == '4') {
        break;
      }

    }
  }


  PORTD &= ~_BV(3);
  //trigSwitch01 = !trigSwitch01;
  //digitalWrite(trig01, trigSwitch01);
  Serial.print(F("f"));
  for (;;);

}
