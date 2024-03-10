#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float tension;
float intense;
float offset;
float ubat;
float puissance;
float timer;
float energy;
const int colorR = 255;
const int colorG = 0;
const int colorB = 100;
unsigned long startMillis = 0;
unsigned long previousMillis = 0;
const unsigned long period = 1000;
boolean Running = false;
unsigned long StartTime = 0;
unsigned long StopTime = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  sensorValue = analogRead(sensorPin);
  tension = sensorValue * 5.0/1024.0;
  offset = (tension - 2.5) / 0.185;
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  startMillis = millis();
}

void loop() {
  // read the value from the sensor:
  lcd.display();
  lcd.setCursor(0, 0);
  sensorValue = analogRead(sensorPin);
  tension = sensorValue * 5.0/1024.0;
  intense = ((tension - 2.5) / 0.185) - offset;
  Serial.println("Adc : " + String(sensorValue));
  Serial.println("Tension : " + String(tension) + " V");
  Serial.println("Intensité : " + String(intense) + " A");
  ubat = 12.48;
  puissance = (ubat * intense);
  Serial.println("Psys " + String(puissance) + " W");
  Serial.println("-----------------------------");
  lcd.print("Psys " + String(puissance) + " W");
  delay(600);
  unsigned long currentTime = millis();// set current time to millis

  if (! Running)
  {
    StartTime = currentTime;// when start event occurs set start time to current time
    Running = true;//and move to (Running)
  }
timer = ((currentTime - StartTime)/1000);
  if (! Running);
  {
    Serial.print("Timer = ");    
    Serial.println(timer);//This is where i get confused. aren't these the same? Both were made equal in first IF and are current Millis?
  }
  energy = (puissance * timer);
  Serial.print("Energy = ");
  Serial.println(energy);
}
