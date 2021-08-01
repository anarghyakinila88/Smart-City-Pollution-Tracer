#include <Servo.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

char ssid[] = " ";
char pass[] = " ";

WiFiClient client;

unsigned long myChannelNumber = 1451240;
const char * myWriteAPIKey = " ";
int i;
int sensorValue;
int sensorPin = A0;
Servo myServo;
String myStatus = " ";

void setup() {
Serial.begin(115200);
Serial.println();
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
WiFi.begin(ssid,pass);
Serial.print("Connecting");
while(WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println();
Serial.print("Connected, IP address: ");
Serial.println(WiFi.localIP());

pinMode(sensorPin, INPUT);
Serial.begin(9600);
myServo.attach(13);
}

void loop() {
for (int i=0; i<=180; i++) {
sensorValue = analogRead(sensorPin);
myServo.write(i);
delay(90);
Serial.print(i);
Serial.print(",");
Serial.println(sensorValue);
if (sensorValue > 600) {
Serial.println("Alert!!!!");
delay(2000);
ThingSpeak.setField(1, sensorValue);
ThingSpeak.setField(2,i);
ThingSpeak.setStatus(myStatus);

int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
if (x = 200) {
Serial.println("Channel update successful. ");
}
else {
Serial.println("Problem updating channel. HTTP error code" +String(x));
}
}
else  {
Serial.println("Normal");
delay(500);
}
}


for (int i=180; i>0; i--) {
sensorValue = analogRead(sensorPin);
myServo.write(i);
delay(90);
Serial.print(i);
Serial.print(",");
Serial.println(sensorValue);
if (sensorValue > 600) {
Serial.println("Alert!!!!");
delay(2000);
ThingSpeak.setField(1, sensorValue);
ThingSpeak.setField(2,i);
ThingSpeak.setStatus(myStatus);

int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
if (x = 200) {
Serial.println("Channel update successful. ");
}
else {
Serial.println("Problem updating channel. HTTP error code" +String(x));
}
}
else  {
Serial.println("Normal");
delay(500);
}
}
}
