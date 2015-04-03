const int ledPin1 = 9;
const int ledPin2 = 10;

const long interval = 5000;

boolean flag = true;

void setup(){
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop(){
  if (flag == true){
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  }
  else{
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
  }
  delay(interval);
  flag = !flag;
}
