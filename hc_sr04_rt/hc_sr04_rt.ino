/*
  Включяем библиотеку для работы с HC-SR04
*/
#include <hcsr04.h>
 
#define ECHO_PIN  12
#define TRIG_PIN  13
#define TIMEOUT  30000
 
/*
  Создаём экземпляр класса HCSR04
*/
HCSR04 sonar_0(TRIG_PIN, ECHO_PIN, TIMEOUT);
 
void setup() {  
  Serial.begin(9600);
  sonar_0.begin();
}
 
void loop() {
  int cm;
  cm = sonar_0.getDistanceCm();
    
  Serial.print(byte(cm));
  Serial.print(" cm   "); 
  Serial.println();  
  delay(250);
}
