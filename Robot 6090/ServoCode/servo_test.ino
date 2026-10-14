/*
  Servo tester: Arduino Mega 2560 + PCA9685 16-channel driver + MG996R servos

  Library: "Adafruit PWM Servo Driver Library" (install via Library Manager)

  Wiring (Mega -> PCA9685):
    5V      -> VCC   (logic power only)
    GND     -> GND
    20 SDA  -> SDA
    21 SCL  -> SCL
  Servo power: external 5-6 V supply into the green screw terminal (V+ / GND).
  Do NOT power the servos from the Arduino's 5V pin.

  Use: open Serial Monitor at 115200 baud, line ending "Newline".
    <ch> <angle>   move one servo, e.g.  0 90
    s <ch>         slow sweep of one servo between SWEEP_MIN and SWEEP_MAX
    a <angle>      move all servos to an angle
    off            stop sending pulses (servos go limp)
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const uint8_t NUM_SERVOS = 6;     // how many channels you have plugged in (0..N-1)
const int PULSE_MIN_US  = 600;    // pulse at 0 deg   (tune per servo if needed)
const int PULSE_MAX_US  = 2400;   // pulse at 180 deg
const int SWEEP_MIN     = 60;     // sweep range kept small so an arm
const int SWEEP_MAX     = 120;    //   doesn't hit its mechanical limits
const int STEP_DELAY_MS = 20;     // bigger = slower sweep

void setServo(uint8_t ch, int angle) {
  angle = constrain(angle, 0, 180);
  int us = map(angle, 0, 180, PULSE_MIN_US, PULSE_MAX_US);
  pwm.writeMicroseconds(ch, us);
}

void sweep(uint8_t ch) {
  Serial.print("Sweeping channel "); Serial.println(ch);
  setServo(ch, 90);
  delay(500);
  for (int a = 90; a <= SWEEP_MAX; a++) { setServo(ch, a); delay(STEP_DELAY_MS); }
  for (int a = SWEEP_MAX; a >= SWEEP_MIN; a--) { setServo(ch, a); delay(STEP_DELAY_MS); }
  for (int a = SWEEP_MIN; a <= 90; a++) { setServo(ch, a); delay(STEP_DELAY_MS); }
  Serial.println("Done");
}

void printHelp() {
  Serial.println(F("Commands:"));
  Serial.println(F("  <ch> <angle>  e.g. 0 90"));
  Serial.println(F("  s <ch>        sweep one servo"));
  Serial.println(F("  a <angle>     all servos to angle"));
  Serial.println(F("  off           release all servos"));
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Check the driver board answers on I2C
  Wire.beginTransmission(0x40);
  if (Wire.endTransmission() != 0) {
    Serial.println(F("PCA9685 not found at 0x40 - check SDA/SCL/VCC/GND wiring."));
    while (true) {}
  }

  pwm.begin();
  pwm.setOscillatorFrequency(25000000);  // tweak 23-27 MHz if angles are off
  pwm.setPWMFreq(50);                    // standard 50 Hz servo signal
  delay(10);

  Serial.println(F("PCA9685 found. Servos stay idle until you send a command."));
  printHelp();
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');
  line.trim();
  if (line.length() == 0) return;

  if (line == "off") {
    for (uint8_t ch = 0; ch < 16; ch++) pwm.setPWM(ch, 0, 4096);  // full off
    Serial.println(F("All outputs off"));
  } else if (line.startsWith("s ")) {
    int ch = line.substring(2).toInt();
    if (ch >= 0 && ch < 16) sweep(ch);
  } else if (line.startsWith("a ")) {
    int angle = line.substring(2).toInt();
    for (uint8_t ch = 0; ch < NUM_SERVOS; ch++) { setServo(ch, angle); delay(150); }
    Serial.print(F("All -> ")); Serial.println(angle);
  } else {
    int sp = line.indexOf(' ');
    if (sp < 0) { printHelp(); return; }
    int ch = line.substring(0, sp).toInt();
    int angle = line.substring(sp + 1).toInt();
    if (ch < 0 || ch > 15) { Serial.println(F("Channel must be 0-15")); return; }
    setServo(ch, angle);
    Serial.print(F("Ch ")); Serial.print(ch);
    Serial.print(F(" -> ")); Serial.println(angle);
  }
}
