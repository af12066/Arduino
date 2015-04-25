void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print('H');
  delay(10000);
  Serial.print('L');
  delay(10000);
  // Serial.print('K');
  // delay(2000);
}
