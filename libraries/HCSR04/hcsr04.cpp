#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "hcsr04.h"

HCSR04::HCSR04(uint8_t trigPin, uint8_t echoPin, unsigned long timeout = 1000000) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->timeout = timeout;
}

void HCSR04::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

unsigned long HCSR04::getDuration() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH, timeout);
}

unsigned int HCSR04::getDistanceMm() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return (unsigned int)((duration * 5) / 29);
  } else {
    return 0;
  }
}

float HCSR04::getDistanceMmFloat() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return duration / 5.8f;
  } else {
    return 0.0f;
  }
}

unsigned int HCSR04::getDistanceCm() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return (unsigned int)(duration / 58);
  } else {
    return 0;
  }
}

float HCSR04::getDistanceCmFloat() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return duration / 58.0f;
  } else {
    return 0.0f;
  }
}

unsigned int HCSR04::getDistanceInch() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return (unsigned int)(duration / 148);
  } else {
    return 0;
  }
}

float HCSR04::getDistanceInchFloat() {
  unsigned int duration = (unsigned int)getDuration();
  if (duration) {
    return duration / 148.0f;
  } else {
    return 0;
  }
}