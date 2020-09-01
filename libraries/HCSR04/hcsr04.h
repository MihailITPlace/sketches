/*
  micro-pi.ru
*/
#ifndef HCSR04_h
#define HCSR04_h

class HCSR04 {
  private:
    unsigned long timeout;
    uint8_t trigPin;
    uint8_t echoPin;

  public:
    HCSR04(uint8_t trigPin, uint8_t echoPin, unsigned long timeout = 1000000);
    void begin();
	
    unsigned int getDistanceMm();
    unsigned int getDistanceCm();
    unsigned int getDistanceInch();

    float getDistanceMmFloat();
    float getDistanceCmFloat();
    float getDistanceInchFloat();

  private:
    unsigned long getDuration();
};

#endif
