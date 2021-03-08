#include <ESP8266WiFi.h>
const char* ssid     = "ASUS_2.4G";
const char* password = "wifi1andar";
WiFiServer server(80);

String header;
String forward = "off";
String reverse_ = "off";
String right = "off";
String left = "off";

const int relay1 = 15;
const int relay2 = 12;
const int relay3 = 14;
const int relay4 = 16;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();         
      if (client.available()) {  
        char c = client.read();   
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /Forward/on") >= 0) {
              forward = "on";
              digitalWrite(relay1, LOW);
              digitalWrite(relay2, HIGH);
              digitalWrite(relay3, LOW);
              digitalWrite(relay4, HIGH);
            } else if (header.indexOf("GET /Forward/off") >= 0) {
              forward = "off";
              parar();
            } else if (header.indexOf("GET /Reverse/on") >= 0) {
              reverse_ = "on";
              digitalWrite(relay1, HIGH);
              digitalWrite(relay2, LOW);
              digitalWrite(relay3, HIGH);
              digitalWrite(relay4, LOW);
            } else if (header.indexOf("GET /Reverse/off") >= 0) {
              reverse_ = "off";
              parar();
            } else if (header.indexOf("GET /Right/on") >= 0) {
              right = "on";
              digitalWrite(relay1, HIGH);
              digitalWrite(relay2, HIGH);
              digitalWrite(relay3, LOW);
              digitalWrite(relay4, HIGH);
            } else if (header.indexOf("GET /Right/off") >= 0) {
              right = "off";
              parar();
            } else if (header.indexOf("GET /Left/on") >= 0) {
              left = "on";
              digitalWrite(relay1, LOW);
              digitalWrite(relay2, HIGH);
              digitalWrite(relay3, HIGH);
              digitalWrite(relay4, HIGH);
            } else if (header.indexOf("GET /Left/off") >= 0) {
              left = "off";
              parar();
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            client.println("<body><h1>My Robot</h1>");

            client.println("Forward");
            if (forward=="off") {
              client.println("<p><a href=\"/Forward/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Forward/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.print("Left------Right"); 
            if (left=="off") {
              client.print("<p><a href=\"/Left/on\"><button class=\"button\">ON</button></a>");
            } else {
              client.print("<p><a href=\"/Left/off\"><button class=\"button button2\">OFF</button></a>");
            }
            
            if (right=="off") {
              client.println("<a href=\"/Right/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<a href=\"/Right/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
                   
            if (reverse_=="off") {
              client.println("<p><a href=\"/Reverse/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Reverse/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("Reverse");
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void parar() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}
