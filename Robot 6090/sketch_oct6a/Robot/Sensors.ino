#include <Wire.h>
#include <Adafruit_TCS34725.h>

const int triggerFront = 5;
const int triggerRight = 6;
const int triggerLeft = 7;
const int triggerColour = 8;

const int echo = 9;
const int echo2 = 10;
const int echo3 = 11;
const int echo4 = 12;

const int LED_PIN = A4;   // drives the sensor's LED pin
const int INT_PIN = A3;   // INT is open-drain, active LOW

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {

  // put your setup code here, to run once:  

  pinMode ( triggerFront , OUTPUT); 
  pinMode ( echo , INPUT);

  pinMode ( triggerRight , OUTPUT); 
  pinMode ( echo2 , INPUT);

  pinMode ( triggerLeft , OUTPUT); 
  pinMode ( echo3 , INPUT);

  pinMode ( triggerColours , OUTPUT); 
  pinMode ( echo4 , INPUT);

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);     // HIGH = onboard white LED on, LOW = off
  pinMode(INT_PIN, INPUT_PULLUP);  // pull-up needed since INT is open-drain

  if (!tcs.begin()) {
    Serial.println("TCS34725 not found. Check wiring (SDA=20, SCL=21, 3V3, GND).");
    while (1) delay(1000);
  }
  Serial.println("TCS34725 ready");

  Serial.begin (9600); 

}

int printColourData(){
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  
  if((a > b) && (a > c)){
    return a
  }
}

void loop() {
  // put your main code here, to run repeatedly:  

  digitalWrite(trigger,HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigger,LOW); 
  float t = pulseIn(echo, HIGH); 
  float distance = 0.0343*t/2; 
  Serial.print("Distance to Object (cm) is: "); 
  Serial.println(distance); 
  delay(1000); 



}
