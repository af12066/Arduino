#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Twitter.h> // Additional Library
#include <Time.h>

const int analogChannel = 1;
int sensorReading = 0;
bool isSitting = false;
bool tw = false;

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xF9, 0x3E}; // Arduino Ethernet SheldのMACアドレス
unsigned const int localPort = 8888; // UDPポート
IPAddress ip(192, 168, 1, 177); // Arduinoに割り振る任意のIP
IPAddress timeServer(133, 243, 238, 164); // NTPサーバのIP

const int NTP_PACKET_SIZE = 48; // NTP packet buffer size
byte packetBuffer[NTP_PACKET_SIZE];
EthernetUDP Udp;
unsigned long lastSendPacketTime = 0;

Twitter twitter("1052573790-zakosPsq6auqf7a6zdisl1WuiuFIF15MrFn19Tb"); // Twiiter token

void setup()
{
  delay(1000);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  Serial.print("Gateway IP address: ");
  Serial.println(Ethernet.gatewayIP());

  Serial.print("DNS IP address: ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println();
  
  Udp.begin(localPort);
  
  // 時刻リクエスト
  sendNTPpacket(timeServer);
  lastSendPacketTime = millis();
}

void loop()
{
  if ( millis() - lastSendPacketTime > 1000 ){
    // NTPサーバへ時刻リクエストを送信
    sendNTPpacket(timeServer);
    // 時間を更新
    lastSendPacketTime = millis();
  }
  
  // NTPサーバからのパケット受信
  if ( Udp.parsePacket() ) {
    // バッファに受信データを読み込む
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    // 時刻情報はパケットの40バイト目からはじまる4バイトのデータ
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    // NTPタイムスタンプは64ビットの符号無し固定小数点数（整数部32ビット、小数部32ビット）
    // 1900年1月1日0時との相対的な差を秒単位で表している
    // 小数部は切り捨てて、秒を求めている
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    // NTPタイムスタンプをUNIXタイムに変換する
    // UNITタイムは1970年1月1日0時からはじまる
    // 1900年から1970年の70年を秒で表すと2208988800秒になる
    const unsigned long seventyYears = 2208988800UL;
    // NTPタイムスタンプから70年分の秒を引くとUNIXタイムが得られる
    unsigned long epoch = secsSince1900 - seventyYears; 
    Serial.print("Unix time = ");
    Serial.println(epoch);

    // Timeライブラリに時間を設定(UNIXタイム)
    // 日本標準時にあわせるために+9時間しておく
    setTime(epoch + (9 * 60 * 60));
    
    String setYear = (String)year();
    String setMonth = (String)month();
    String setDay = (String)day();
    String setHour = (String)hour();
    String setMinute = (String)minute();
    String setSecond = (String)second();
    
    // センサの値を読みとる
    sensorReading = analogRead(analogChannel);
    Serial.print("analog input: ");
    Serial.println(sensorReading);
    
    String yotsugiStatus;
    
    // 余接の状態判定
    if(sensorReading < 900 && isSitting == false){
      isSitting = true;
      tw = false;
      yotsugiStatus = " :sit";
    }
    else if(sensorReading > 900 && isSitting == true){
      isSitting = false;
      tw = false;
      yotsugiStatus = " :stand";
    }
    
    // ポストする内容
    String s = "Sent from Arduino (" + setYear + "/" + setMonth + "/" + setDay + " " + setHour + ":" + setMinute + ":" + setSecond + ")" + yotsugiStatus;
    
    // ポストする文字列はchar型でなければならない => 変換
    char msg[50];
    s.toCharArray(msg, 50);
    
    // Twitterにポスト
    if (tw == false){
      if (twitter.post(msg)) {
        int status = twitter.wait();
        if (status == 200) {
          Serial.println("posted.");
          Serial.println(s);
          Serial.println();
        }
        else {
          Serial.print("failed : code ");
          Serial.println(status);
        }
      }
      else {
        Serial.println("connection failed.");
      }
      tw = true;
    }
  }
}

unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  // NTP requests are to port 123
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
