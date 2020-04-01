/*
  A PIR sensor-light mod for garage lights. Features:
  Two sensors and one light output.
  A user-settable duration using a potentiometer.
*/

const unsigned int DEFAULT_DURATION_MS = 3 * 60 * 1000;
const bool ON = true;
const bool OFF = false;

// IO Definitions
const int pirPinRollerdoor = 2;
const int pirPinPersonnel = 3;
const int relayPin = 4;
const int motionIndicator = 13;

void setup() {
  pinMode(pirPinPersonnel, INPUT);
  pinMode(pirPinRollerdoor, INPUT);
  pinMode(motionIndicator, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, OFF);
  digitalWrite(motionIndicator, false);
}

void loop() {
  static unsigned long start = 0;
  unsigned long now = millis();

  // Motion detected, reset timer, light:ON
  if (digitalRead(pirPinPersonnel) || digitalRead(pirPinRollerdoor)) {
    digitalWrite(motionIndicator, true);
    digitalWrite(relayPin, ON);
    start = now;
  } else {
    digitalWrite(motionIndicator, false);
  }

  // check timer expired, light:OFF
  unsigned long elapsed = now - start;
  if (elapsed >= DEFAULT_DURATION_MS) {
    digitalWrite(relayPin, OFF);
  }

  delay(500);

}
