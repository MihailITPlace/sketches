// указываем аналоговый пин A0 в качестве входа
#define sensorPin 1
// Определяем напряжение питания Vcc (5 В или 3.3 В)
#define Vcc 5.0

float tempSensor(int pin, int volt)
{
  int reading = analogRead(pin);
  float voltage = reading * volt;
  voltage /= 1024.0;
  return (voltage - 0.5) * 100;  
}

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
 //Serial.println("All rigth!");
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read() - '0';

    switch (data)
    {
      case 0:
      {
        digitalWrite(13, LOW);
        //Serial.print("OFF");           
      }
      break;

      case 1:
      {
        digitalWrite(13, HIGH);
       // Serial.print("ON");                
      }
      break; 

      case 2:
      {
        float result = tempSensor(sensorPin, Vcc);
        Serial.print("TP");
        Serial.println(result);            
      }
      break;
    } 
  }
}
