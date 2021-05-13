#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "ASUS_2.4G";
const char* password = "wifi1andar";
WiFiServer server(80);

void forward();
void reverse();
void left();
void right();
void stop();

//Pins connected to the relays
int relay1 = 12;
int relay2 = 14;
int relay3 = 5;
int relay4 = 16;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;
String header;
String forward_ = "off";
String reverse_ = "off";
String right_ = "off";
String left_ = "off";

void setup() {
    //Set the relay pins as output
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);

    //Motors off
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, HIGH); 
    digitalWrite(relay3, HIGH); 
    digitalWrite(relay4, HIGH);

    //Initialize serial monitor with 9600 baud
    Serial.begin(9600);
    delay(2000);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected.\nIP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) 
    {
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        currentTime = millis();
        previousTime = currentTime;
        while (client.connected() && currentTime - previousTime <= timeoutTime) 
        {
            currentTime = millis();         
            if (client.available()) 
            {  
                char c = client.read();   
                Serial.write(c);                    
                header += c;
                if (c == '\n') 
                {                    
                    if (currentLine.length() == 0) 
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        // turns the GPIOs on and off
                        if (header.indexOf("GET /Forward/on") >= 0) {
                            forward_ = "on";
                            forward();
                        } else if (header.indexOf("GET /Forward/off") >= 0) {
                            forward_ = "off";
                            stop();
                        } else if (header.indexOf("GET /Reverse/on") >= 0) {
                            reverse_ = "on";
                            reverse();
                        } else if (header.indexOf("GET /Reverse/off") >= 0) {
                            reverse_ = "off";
                            stop();
                        } else if (header.indexOf("GET /Right/on") >= 0) {
                            right_ = "on";
                            right();
                        } else if (header.indexOf("GET /Right/off") >= 0) {
                            right_ = "off";
                            stop();
                        } else if (header.indexOf("GET /Left/on") >= 0) {
                            left_ = "on";
                            left();
                        } else if (header.indexOf("GET /Left/off") >= 0) {
                            left_ = "off";
                            stop();
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
                        if (forward_=="off") {
                            client.println("<p><a href=\"/Forward/on\"><button class=\"button\">ON</button></a></p>");
                        } else {
                            client.println("<p><a href=\"/Forward/off\"><button class=\"button button2\">OFF</button></a></p>");
                        } 

                        client.print("Left------Right"); 
                        if (left_=="off") {
                            client.print("<p><a href=\"/Left/on\"><button class=\"button\">ON</button></a>");
                        } else {
                            client.print("<p><a href=\"/Left/off\"><button class=\"button button2\">OFF</button></a>");
                        }
                        
                        if (right_=="off") {
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

void forward() {
    stop();
    delay(10);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
}

void right() {
    stop();
    delay(10);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
}

void left() {
    stop();
    delay(10);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
}

void reverse() {
    stop();
    delay(10);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
}

void stop()
{
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, HIGH); 
    digitalWrite(relay3, HIGH); 
    digitalWrite(relay4, HIGH);
}