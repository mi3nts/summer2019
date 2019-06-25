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

### Task 3: Use Barometer Sensor
#### 3.1 Connect hardware
 - Connect the Arduino to the board
 - Connect the barometer sensor to the Arduino
  - SCL wire goes to A5
  - SDA to A4
  - UCC to 5V
  - GND to the GND hole on the board
#### 3.2 Create the program
 - Write the following code: 
 ````
 /*Test of the BME280 sensor, displaying temp and pressure*/

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
