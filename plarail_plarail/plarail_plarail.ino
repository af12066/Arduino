const int inputPin01 = 8;
const int inputPin02 = 9;
const int pwmPin = 10;
const int ledPin = 12;
const int magnetPin = 13;

int value;
int value2;
int i = 1;

void setup() {
    Serial.begin(9600);
    pinMode(inputPin01, OUTPUT); // モータ用
    pinMode(inputPin02, OUTPUT); // モータ用
    pinMode(pwmPin, OUTPUT); // モータ速度制御
    pinMode(ledPin, OUTPUT); // LED点灯用
    pinMode(magnetPin, INPUT); // ホールIC用
    digitalWrite(ledPin, true); // 視覚刺激用LEDは常にON
}

void loop() {
  value = analogRead(A0);
  //value2 = digitalRead(magnetPin);
  if (Serial.available() > 0) {
    if (Serial.read() == 'r') {
      while( true ){
        value2 = digitalRead(magnetPin);
        forward(value);
        if (value2 == 0) {
          Serial.print(i);
          i++;
          while (digitalRead(magnetPin) == 0){}
        }
        if (Serial.read() == 'f') {
          finish();
          break;
        }
      }
    }
  }
}

void forward(int value) {
  digitalWrite(inputPin01, LOW); // inputPin01をLOW
  digitalWrite(inputPin02, HIGH); // inputPin02をHIGH
  analogWrite(pwmPin, value);
  delay(80);
  return;
}

void finish(void) { // プラレール停止用関数
    digitalWrite(inputPin01, LOW);
    digitalWrite(inputPin02, LOW);
    return;
}
