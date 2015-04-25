int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    if(Serial.read() == 'K'){
      digitalWrite(led, HIGH);
    }
    else{
      digitalWrite(led, LOW);
    }
  }
}
