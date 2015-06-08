const int trig01 = 3;
const int trig02 = 4;
const int button = 2;

int i, j;

boolean trigSwitch01 = true;
boolean trigSwitch02 = false;

void setup() {
  pinMode(trig01, OUTPUT);
  pinMode(trig02, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  while ( digitalRead(button) == LOW ){}
  delay(5000);
  
  digitalWrite(trig01, trigSwitch01);
  
  for (i=0; i<2; i++) {
    for (j=1; j<6; j++) {
      Serial.print(j);
      trigSwitch02 = !trigSwitch02;
      digitalWrite(trig02, trigSwitch02);
    
      delay(5000);
    }
  }
  
  trigSwitch01 = !trigSwitch01;
  digitalWrite(trig01, trigSwitch01);
  
  for(;;);

}
