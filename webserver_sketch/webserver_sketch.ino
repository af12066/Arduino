#include <SPI.h>
#include <Ethernet.h>

boolean skip = false;
boolean catchGet = false;

// 出力ピン
int oPin = 9;

// IPアドレス、MACアドレスは適宜変更
byte ip [] = {192, 168, 1, 177};
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xF9, 0x3E};

// HTTP: 80番ポート
EthernetServer server = EthernetServer(80);

void setup() {
  pinMode(oPin, OUTPUT);
  digitalWrite(oPin, LOW);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  Serial.println(Ethernet.localIP());
  server.begin();
}


void loop() {
  // クライアントからのデータ受信
  EthernetClient client = server.available();
  
  // 受信がある場合の挙動
  if (client) {
    while (client.connected()) {
      
      if (client.available()) { // 受信データがある場合
        char c = client.read(); // 受信データを1文字ずつ読み込む
        Serial.write(c); // シリアルモニタに表示
        
        if (!skip && catchGet) {
          switch (c) {
            case '1' : digitalWrite(oPin, HIGH); break;
            case '0' : digitalWrite(oPin, LOW);  break;
            default  : continue;
          }
          skip = true;
        }
        
        if (c == '?'){ // 受信データに'?'があるとき
          catchGet = true;
        }
      }
      
      else{  
        HTML(client); // HTTPレスポンス
        break;
      }
    }
  }
  
  skip = false;
  catchGet = false;
  client.stop();
}

void HTML(EthernetClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>A Remote</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<form method=GET>");
  client.println("<input type=submit name=1 value=on /><br />");
  client.println("<input type=submit name=0 value=off />");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");
  
}
