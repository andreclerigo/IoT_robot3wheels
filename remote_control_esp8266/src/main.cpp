#include <Arduino.h>

//Pins connected to the relays
int relay1 = 12;
int relay2 = 14;
int relay3 = 5;
int relay4 = 16;

void forward();
void reverse();
void left();
void right();
void stop();

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
}

void loop() {
    forward();
    delay(2000);
    reverse();
    delay(2000);
    left();
    delay(2000);
    right();
    delay(2000);
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