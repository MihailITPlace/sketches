#include <hcsr04.h>
#include <Wire.h>
 
#define ECHO_PIN  12
#define TRIG_PIN  11
#define TIMEOUT  5000
#define SLAVE_ADDRESS 0x04

#define PIN_PHOTO_SENSOR A0
 

class Sonar {
public:
  Sonar(){}
  Sonar(int trig, int echo) {
    this->last_value = 0;
    this->hscr04 = new HCSR04(trig, echo, TIMEOUT);
    this->hscr04->begin();      
  }

  byte get_last_value() { return this->last_value; }

  void update_value() { this->last_value = byte(hscr04->getDistanceCm()); } 
  
private:
  byte last_value;
  HCSR04* hscr04;
};

class PhotoSensor {
public:
  PhotoSensor(){}
  PhotoSensor(int pin){ this->pin = pin; }
  
  byte get_last_value() { return this->last_value; }
  
  void update_value() { this->last_value = analogRead(pin); }
private:
  int last_value;
  byte pin;    
};

Sonar sonar_0; //левый борт передний
Sonar sonar_1; //левый борт средний
Sonar sonar_2; //левый борт задний

Sonar sonar_3; //правый борт передний
Sonar sonar_4; //правый борт средний
Sonar sonar_5; //правый борт задний

PhotoSensor photoSensor;
 
void setup() {  
  Serial.begin(9600);
  sonar_0 = Sonar(12, 13); //левый борт передний
  sonar_1 = Sonar(10, 11); //левый борт средний
  sonar_2 = Sonar(8, 9); //левый борт задний
  
  sonar_3 = Sonar(6, 7); //правый борт передний
  sonar_4 = Sonar(4, 5); //правый борт средний
  sonar_5 = Sonar(2, 3); //правый борт задний

  photoSensor = PhotoSensor(PIN_PHOTO_SENSOR);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(reply_to_receipt);  
}

int counter = 0;

void loop() {
  sonar_0.update_value();
  sonar_1.update_value();
  sonar_2.update_value();
  sonar_3.update_value();
  sonar_4.update_value();
  sonar_5.update_value();

  photoSensor.update_value();
  
  if (counter > 100){
    Serial.print(sonar_0.get_last_value());
    Serial.print(" ");
    Serial.print(sonar_1.get_last_value());
    Serial.print(" ");
    Serial.print(sonar_2.get_last_value());
    Serial.print(" ");
    Serial.print(sonar_3.get_last_value());
    Serial.print(" ");
    Serial.print(sonar_4.get_last_value());
    Serial.print(" ");
    Serial.print(sonar_5.get_last_value());
    Serial.println(" ");

    Serial.print("photo: ");
    Serial.println(photoSensor.get_last_value());
    counter = 0;
  }
  counter += 1;
}

void reply_to_receipt() {
  char chr = Wire.read();
  switch (chr) {
    case 1:
      send_left_sonar_values();
      break;
    case 2:
      send_right_sonar_values();
      break;
    case 3:
      send_photo_sensor_value();
      break;
    default:
      Serial.println("Unknow char");
  }
}

void send_left_sonar_values() {
  Wire.write(sonar_0.get_last_value());
  Wire.write(sonar_1.get_last_value());
  Wire.write(sonar_2.get_last_value());  
}

void send_right_sonar_values() {
  Wire.write(sonar_3.get_last_value());
  Wire.write(sonar_4.get_last_value());
  Wire.write(sonar_5.get_last_value());
}

void send_photo_sensor_value() {
  Wire.write(photoSensor.get_last_value());
}
