// Hygrometer Read - no OLED controll

const int relay = 3;    // relay for water valve at pin 3 of Arduino (pin 3 has pull down resistor)
int sensorPin = A0;  // hygrometer senor input pin
int sensorValue = 0;  // hygrometer sensor default value
int percent = 0;  // hygrometer sensor default percentage

void setup() 
{
  Serial.begin(9600);  // serial monitor start
    pinMode(relay,OUTPUT);  // changes pin 3 to an output
}

void loop() 
{  
  sensorValue = analogRead(sensorPin);  // read value from input sensor pin
  percent = convertToPercent(sensorValue);  // convert analog reading to a percentage
  printValuesToSerial();  // display value to serial monitor
  delay(1000);  // delay before running loop again

// valve controll
    
  if (percent < 15){  // start watering if soil humidity is < 15%
    digitalWrite(relay,HIGH); // turn on water valve
  }
  else {
      digitalWrite(relay,LOW);  // turn off water valve
  }
  delay(1000); // read delay
}


int convertToPercent(int value)
{
  int percentValue = 0;  // base value set from sensor pin
  percentValue = map(value, 1023, 465, 0, 100);  // equate reading to actual value
  return percentValue;  // return equated actual value
}

void printValuesToSerial()
{
  Serial.print("\n\nAnalog Value: ");  // call up two values ( raw sensor data and actual sensor data)
  Serial.print(sensorValue);  // value callup
  Serial.print("\nPercent: ");  // raw data
  Serial.print(percent);  // percent callup
  Serial.print("%");  // percentage data
}

