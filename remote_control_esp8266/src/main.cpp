#include <Arduino.h>

//Pins connected to the relays
int relay1 = 15;
int relay2 = 13;
int relay3 = 12;
int relay4 = 14;

void forward();
void reverse();

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
    //reverse();
}

void forward() {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
}

void reverse() {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
}