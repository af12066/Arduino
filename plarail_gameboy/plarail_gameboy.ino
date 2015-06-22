const int trig01 = 10; // 測定開始・終了用
const int trig02 = 11; // 距離測定用
const int button = 4; // ボタンを押して開始

char c;
char i = '1';

boolean trigSwitch01 = true;
boolean trigSwitch02 = true;

void setup() {
  pinMode(trig01, OUTPUT);
  pinMode(trig02, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  digitalWrite(trig02, trigSwitch02);
}

void loop() {
    while (digitalRead(button) == LOW) {} // ボタン操作が入るまで停止

    Serial.print("r");
    PORTB |= _BV(2); // digitalWrite(trig01, HIGH);

    while (true) {

        if (Serial.available() > 0) {

            c = Serial.read();

            if (c == i) {
                trigSwitch02 = !trigSwitch02; // 距離測定用トリガのHIGH,LOW切り替え
                digitalWrite(trig02, trigSwitch02);
                i++;
            }
            if (c == '4') { // ここで磁石を通る回数を指定
                break;
            }

        } // end if (Serial.available())

    } // end while

    PORTB &= ~_BV(2); // digitalWrite(trig01, LOW);
    Serial.print(F("f"));

    for (;;); // プログラムのくり返し阻止

}
