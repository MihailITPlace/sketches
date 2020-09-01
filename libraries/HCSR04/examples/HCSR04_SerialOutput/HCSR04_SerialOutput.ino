#include <hcsr04.h>

#define TRIG_PIN 12
#define ECHO_PIN 13
#define TIMEOUT  30000

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, TIMEOUT);

void setup() {
  Serial.begin(9600);
  hcsr04.begin();
}

void loop() {
  Serial.print("Distance ");
  Serial.print(hcsr04.getDistanceMm());
  Serial.println(" mm");

  delay(250);
}