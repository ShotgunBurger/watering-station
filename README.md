# watering-station
hygrometer controlled watering system using arduino and a water valve solenoid controlled via relay.

hygrometer is a soil humidity sensor from banggood.com
https://www.banggood.com/Soil-Hygrometer-Humidity-Detection-Module-Moisture-Sensor-For-Arduino-p-79227.html?rmmds=search
specs...
Operating voltage: 3.3V~5V.
Adjustable sensitivity (shown in blue digital potentiometer adjustment)
Dual output mode,analog output more accurate.
Power indicator (red) and digital switching output indicator (green).
Has a LM393 comparator chip, stable.
Panel PCB Dimension: 3cm x 1.5cm.
Soil Probe Dimension: 6cm x 2cm.
Cable Length: 21cm.

pin outs...
VCC: 3.3V-5V.
GND: GND.
DO: digital output interface(0 and 1).
AO: analog output interface.


water valve solenoid from banggood.com
https://www.banggood.com/34-inch-12V-DC-VDC-Slim-Brass-Electric-Solenoid-Valve-NPSM-Gas-Water-Air-NC-p-1161984.html?rmmds=search
specs...
Body Material: Cast high-quality solid brass
Operation Mode: N/C (normally closed)
Pipe Size: 3/4" NPSM
Voltage: 12V DC
Operation Type: 2-way 2-position direct lift diaphragm
Water pressure: 0.02-0.8Mpa
Size: 68*60*35mm
Operating Pressure Differential: 3-145 psi (0.02-1 MPa)
Operating Temperature: 15-125 °F (-10~50 °C)
Media Temperature: 15-180 °F (-10~80 °C)
Body: Brass
Insert: Stainless steel (plunger, spring, etc.)
Seal: NBR (aka Buna-N, Perbunan, and nitrile rubber)
Diaphragm: NBR with nylon support

relay controller module between arduino and solenoid from banggood.com
https://www.banggood.com/5V-1-Channel-Level-Trigger-Optocoupler-Relay-Module-For-Arduino-p-915614.html?rmmds=search
specs...
Maximum load: AC 250V/10A, DC 30V/10A
Trigger current: 5mA
Working voltage: 5V
Module size: 50 x 26 x 18.5mm (L x W x H)
Four mounting bolts holes, diameter 3.1mm

Module interface...
DC+: positive power supply (VCC)
DC-: negative power supply (GND)
IN: can be high or low level control relay

rlay outputs...
NO: normally open relay interface
COM: Common Interface Relays
NC: normally closed relay interface

hgh and low level trigger options...
It is low level trigger when jumper connect to LOW pin
It is high level trigger when jumper connect to HIGH pin

power comes from solar panel and stored power from LiPo battery
https://www.banggood.com/12V-3W-Polycrystalline-145mm-x-145mm-Solar-Panel-Photovoltaic-Panel-p-999719.html?rmmds=search
https://www.banggood.com/DIY-5V-2A-Voltage-Regulator-Junction-Box-Solar-Panel-Charger-Special-Kit-p-1035493.html?rmmds=search
https://www.banggood.com/4X-ZOP-Power-3_7V-1S-550mAh-45C-Lipo-Battery-White-Plug-p-1162464.html?rmmds=search
https://www.banggood.com/TP4056-1A-Lipo-Battery-Charging-Board-Charger-Module-Mini-USB-Interface-p-1027027.html?rmmds=search
https://www.banggood.com/DC-DC-3_7V-to-5V-Step-Up-Voltage-Booster-Regulator-Micro-Power-Module-For-Brushed-Racing-Quadcopter-p-1092602.html?rmmds=search

the solar panel delivers 12v to the control board to regulate the power and to the rely before the solenoid, the batteries are charged to keep the system working through the night for monitoring yet the lack of 12v at means the watering system won't work at night as it's an annoyance for sleeping. the batteries also mean that when the solenoid kicks in and the power drain is too much to run both systems, the arduino can still function. the step up daughter board means the 3.7v LiPo batteries will run the arduino.


Arduino code...

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
