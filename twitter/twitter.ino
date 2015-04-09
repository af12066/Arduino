#include <SPI.h>
#include <Ethernet.h>
#include<EthernetUdp.h>
#include <Twitter.h> // Additional Library
#include <Time.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xF9, 0x3E};
IPAddress ip(192, 168, 1, 177);
Twitter twitter("1052573790-zakosPsq6auqf7a6zdisl1WuiuFIF15MrFn19Tb");
char msg[] = "Sent from Arduino Uno";

void setup()
{
  delay(1000);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop()
{
}
