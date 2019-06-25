# Daily Notes
## 06/24/2019 Monday
1.1 Learned how to assemble the Shinyei with soldering and wiring
1.1.1 The frayed wires are a pain
1.1.2 Adam discovered that by seprating the wires attached to the load so that they go to both of the sensors simultaneously (as 
oppose to being wired in parallel), accident rate (breaking solder) was cut down in addition to manufacturing time
1.2 Watched one Shinyei be put together (by Adam)
1.3 Helped Adam manufacture 3 Shinyeis (I did more of the soldering while he did more of the wiring)
## 06/25/2019 Tuesday
1.1 Created Arduino accaount
1.1.1 Ardiono Username: norad42; email: nora.desmond@aol.com; password: EdD785::
1.1.2 Github Username: norad02; email: norad.desmond@aol.com; password: EdD785::
2.1 Ran Lakitha's second Github exercise
2.1.1 
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
   // print out a String of your choice 
  Serial.println("Hello MINTS: Multi-scale Integrated Sensing and Simulation");
  // Delay for 1000 miliseconds 
  delay(1000);        // delay in between reads for stability
}
3.1 Ran Likitha's third Github exercise
3.1.1 void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
4.1 Downloaded the Arduino app on my computer
5.1 Download Atom and the PlatformIO
5.1.1 Code for the CO2 & Temperature & Humidity Sensor (SCD30)
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h"
SCD30 airSensor;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("SCD30 Example");
  airSensor.begin(); //This will cause readings to occur every two seconds
}
void loop()
{
  if (airSensor.dataAvailable())
  {
    Serial.print("co2(ppm):");
    Serial.print(airSensor.getCO2());
    
    Serial.print(" temp(C):");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();
  }
  else
    Serial.println("No data");
 delay(1000);
}
5.1.2 Code for the Barometer Sensor (BME280)
#include <Arduino.h>

#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

void setup()
{
  Serial.begin(9600);
  if(!bme280.init()){
    Serial.println("Device error!");
  }
}

void loop()
{
  float pressure;

  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols

  //get and print atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure = bme280.getPressure());
  Serial.println("Pa");

  //get and print altitude data
  Serial.print("Altitude: ");
  Serial.print(bme280.calcAltitude(pressure));
  Serial.println("m");

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");

  delay(1000);
}
5.1.3 Code for the Sunlight Sensor
#include <Wire.h>

#include "Arduino.h"
#include "SI114X.h"

SI114X SI1145 = SI114X();

void setup() {

  Serial.begin(9600);
  Serial.println("Beginning Si1145!");

  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }
  Serial.println("Si1145 is ready!");
}

void loop() {
  Serial.print("//--------------------------------------//\r\n");
  Serial.print("Vis: "); Serial.println(SI1145.ReadVisible());
  Serial.print("IR: "); Serial.println(SI1145.ReadIR());
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  Serial.print("UV: ");  Serial.println((float)SI1145.ReadUV()/100);
  delay(1000);
}
5.1.4 The library for the Light & Gesture & Color & Proximity Sensor is nowhere to be found on Atom/PlatformIO
5.1.4.1 Imbar says that Lakitha will show us later
6.1 The Github that I downloaded onto my Windows refused to run
