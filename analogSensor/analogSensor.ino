#include <SPI.h>
#include <Ethernet.h>

const int analogChannel = 1;
int sensorReading = 0;

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xF9, 0x3E};
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 6");  // refresh the page automatically every 3 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head><title>斧乃木余接</title><style type=\"text/css\">body{font-family:'メイリオ',Meiryo,Arial,sans-serif;}p{font-size:20px;}</style></head>");
          // output the value of each analog input pin
          sensorReading = analogRead(analogChannel);
          client.println("<body>");
          client.print("<p>analog input is ");
          client.print(sensorReading);
          client.println("<br />");
          if(sensorReading < 900){
            client.print("<b>斧乃木余接は座っています✌</b></p>");
            client.print("<br />");
          }
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
