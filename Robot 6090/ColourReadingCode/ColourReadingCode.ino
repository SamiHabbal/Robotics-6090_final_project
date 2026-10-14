#include <Wire.h>
#include <Adafruit_TCS34725.h>

const int LED_PIN = A4;   // drives the sensor's LED pin
const int INT_PIN = A3;   // INT is open-drain, active LOW

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);     // HIGH = onboard white LED on, LOW = off
  pinMode(INT_PIN, INPUT_PULLUP);  // pull-up needed since INT is open-drain

  if (!tcs.begin()) {
    Serial.println("TCS34725 not found. Check wiring (SDA=20, SCL=21, 3V3, GND).");
    while (1) delay(1000);
  }
  Serial.println("TCS34725 ready");
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  uint16_t colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  uint16_t lux = tcs.calculateLux(r, g, b);

  Serial.print("R: "); Serial.print(r);
  Serial.print("  G: "); Serial.print(g);
  Serial.print("  B: "); Serial.print(b);
  Serial.print("  Clear: "); Serial.print(c);
  Serial.print("  Lux: "); Serial.print(lux);
  Serial.print("  CT: "); Serial.print(colorTemp); Serial.print("K");
  Serial.print("  INT: "); Serial.println(digitalRead(INT_PIN));

  delay(1000);
}