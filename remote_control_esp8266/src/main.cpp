#include <Arduino.h>
#include <ESP8266WiFi.h>

// Setup Wifi credentials
const char* ssid = "ASUS_2.4G";
const char* password = "wifi1andar";
WiFiServer server(80);

void forward();
void reverse();
void left();
void right();
void stop();

// Pins connected to the relays
int relay1 = 12;
int relay2 = 14;
int relay3 = 5;
int relay4 = 16;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

// In the idle state the car is stopped
static String forward_ = "off";
static String reverse_ = "off";
static String right_ = "off";
static String left_ = "off";
String header;

void setup() 
{
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

void loop() 
{
    WiFiClient client = server.available();
    if (client) 
    {
        Serial.println("New Client.");          // Print a message out in the serial port
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
                        client.println("Connection: close\n");
                        
                        // turns the GPIOs ON and OFF
                        if (header.indexOf("GET /Forward/on") >= 0)
                            forward();
                        else if (header.indexOf("GET /Reverse/on") >= 0) 
                            reverse();
                        else if (header.indexOf("GET /Right/on") >= 0)
                            right();
                        else if (header.indexOf("GET /Left/on") >= 0)
                            left();
                        else if (header.indexOf("GET /Off") >= 0){
                            forward_ = "off";
                            reverse_ = "off";
                            right_ = "off";
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
                        client.println("<body><h1>My Car Robot</h1>");

                        client.println("Forward");
                        if (forward_=="off")
                            client.println("<p><a href=\"/Forward/on\"><button class=\"button\">ON</button></a></p>");
                        else 
                            client.println("<p><a href=\"/Off\"><button class=\"button button2\">OFF</button></a></p>");

                        client.println("Left --------------- Right"); 
                        if (left_ == "off")
                            client.print("<p><a href=\"/Left/on\"><button class=\"button\">ON</button></a>");
                        else 
                            client.print("<p><a href=\"/Off\"><button class=\"button button2\">OFF</button></a>");
                        
                        if (right_ == "off")
                            client.println("<a href=\"/Right/on\"><button class=\"button\">ON</button></a></p>");
                        else
                            client.println("<a href=\"/Off\"><button class=\"button button2\">OFF</button></a></p>");
                            
                        if (reverse_ == "off")
                            client.println("<p><a href=\"/Reverse/on\"><button class=\"button\">ON</button></a></p>");
                        else
                            client.println("<p><a href=\"/Off\"><button class=\"button button2\">OFF</button></a></p>");

                        client.println("Reverse");
                        client.println("</body></html>");
                        client.println();
                        break;
                    } else
                        currentLine = "";
                } else if (c != '\r')
                    currentLine += c;      
            }
        }
        header = "";
        client.stop();
        Serial.println("Client disconnected.\n");
    }
}

// Move both wheels in reverse
void reverse() {
    reverse_ = "on";            // Flag the reverse as ON
    stop();
    delay(10);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
}

// Move the right wheel forward to turn Left
void left() {                   
    left_ = "on";               // Flag the left as ON
    stop();
    delay(10);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
}

// Move the left wheel forward to turn Right
void right() {
    right_ = "on";              // Flag the right as ON
    stop();
    delay(10);
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
}

// Move both wheels forward
void forward() {
    forward_ = "on";            // Flag the forward as ON
    stop();
    delay(10);
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
}

// Stop both wheels
void stop()
{
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, HIGH); 
    digitalWrite(relay3, HIGH); 
    digitalWrite(relay4, HIGH);
}