# Daily Notes
## June 24, 2019
### Task 1: Disassembling Sensors
#### 1.1 Disassmebling the interior
 - Disconnect USBs and other wires
 - Unscrew the circuit boards from the sensor
 - Take out SD cards
 - Sort out parts into separate piles
#### 1.2 Disassembling exterior
 - Unscrew the lid of the sensor
 - Take out wires
 - Take apart the solar shields
 - Take out the circuit board and the wires

## June 25th, 2019
### Task 2: Set Up Arduino Environment
#### 2.1 Set up Arduino Development Envioronment
 - Go to the web development editor [here](https://www.arduino.cc/en/Main/Software) and create an account
 - Download the Arduino Create plugin [here](https://create.arduino.cc/getting-started/plugin?page=2)
#### 2.2 Do the first exercise
 - Write the following code in the editor:
````
/*
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
````
 - The serial monitor will now print "Hello MINTS: Multi-scale Integrated Sensing and Simulation" on loop
#### 2.3 Do another exercise
 - Change the code to:
 ````
 void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
````
 - The LED light now flashes every half second
 #### 2.4 Exercise 4
 - Try the following:
  ````
 // the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // Delay for 1000 miliseconds 
  if(random(1, 10) > 5)
    digitalWrite(LED_BUILTIN, LOW);
  else
    digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
}
````
#### 2.5 Set up Desktop Arduino IDE
 - Download the desktop IDE [here](https://www.arduino.cc/en/Main/Software)
 - Make sure to pause the plugin downloaded earlier
 - Try out the exercises from before

#### 2.6 Set up Atom environment
 - Download Atom [here](https://atom.io/)
 - Download the PlatformIO package within Atom. Details [here](https://platformio.org/install/ide?install=atom)
 - Search up Seeed BME280 in Libraries in PlatformIO and install

### Task 3: Check the Sensors
#### 3.1 Connect hardware of the BME280 Sensor
 - Connect the Arduino to the board
 - Connect the barometer sensor to the Arduino
   - SCL wire goes to A5
   - SDA to A4
   - UCC to 5V
   - GND to the GND hole on the board
#### 3.2 Create the program
 - Write the following code: 
 ````
 /*Test of the BME280 sensor, displaying temp, humidity, altitude, and pressure*/

#include <Arduino.h>
#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;

void setup() {
  Serial.begin(9600);
  Serial.println("Began")
  if(!bme280.init()){
    Serial.println("Device error!");
  }
}

// the loop function runs over and over again forever
void loop() {
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
````
 - Watch the temperature, pressure, altitude, and humidity being displayed on the serial monitor
   - Temp: 26.22C
   - Pressure: 99034.00Pa
   - Altitude: 192.48m
   - Humidity: 51%
#### 3.3 Use the SCD30 CO2 Sensor
 - Connect the four wires from the arduino to the sensor
 - Install SparkFun_SCD30_Arduino_Library
 - Write the following code:
 ````
/*Test of the SCD30 sensor, displaying CO2, temperature, and humidity*/
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
````
 - Temperature is around 26 degrees Celsius, humidity is 53.2%, which is relatively close to the measurements from the BME280 sensor
 - CO2 ppm seems to be oscillating from 600 to 1500
#### 3.4 Use the Sunlight Sensor
 - Connect the wires to the sensor
 - The library for this sensor is not in Atom
 - Type the following code:
````
#include "Arduino.h"
#include <Wire.h>
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
  Serial.print("Vis: ");
  Serial.println(SI1145.ReadVisible());
  Serial.print("IR: ");
  Serial.println(SI1145.ReadIR());
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  Serial.print("UV: ");
  Serial.println((float)SI1145.ReadUV()/100);
  delay(1000);
}
````
 - When exposed to the room's light, the sensor read:
   - Vis: 275
   - IR: 326
   - UV: 0.10
 - When covered, it read:
   - Vis: 259
   - IR: 253
   - UV: 0.01
