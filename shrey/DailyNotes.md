# Daily Notes

## Monday June 24, 2019

### Task 1: Disassembling Of Particulate Matter Sensor

Today's work consisted of disassembling particulate matter (PM) sensors. There were two sections within these sensors:

- A portion containing the sensor itself (Optical Particle Counter) and an Argon Arduino Board to manage it.
- A portion containing a GPS, camera module, and the processing units

#### 1.1: Processing Portion (Interior)

**Main Components:**

- G-Mouse GPS Module
- USB 3 Power Hub
- 5.0 MP USB Camera Module
- Linux Computer - Odroid XU4 - central computing unit
- PCB (Argon)
- C1+ Module (Argon) - encrypts data to be sent
- Light Sensor Module

**Dismantling Process**

1. Remove box lid
2. Remove 3D printed frame and all components from box
3. Remove USBs and Ethernet cables
4. Remove USB hub and Ethernet-USB converter
5. Remove wires attached to terminal blocks in PCB
5. Unscrew all circuit boards (XU4 is on underside; PCB is on top; camera and light sensor on side.)
6. Remove GPS module

#### 1.2: Sensor Portion (Exterior)

**Main Components:**

- Steven Sunshields
- Optical Particle Counter (OPC)
- PCB (Manage OPC)

**Dismantling Process:**
1. Free wires from the lid of the interior portion
3. Unscrew and remove all steven sunshields except the base one
4. Unscrew PCB
5. Unplug all wires and cut zipties

**Homework:**
- ~~Obtain basic familiarization with github~~
- ~~Finish daily notes~~
- ~~Chapter 2 Problems of C.M. book~~

___

## Tuesday June 25, 2019

### Task 2: Construction of Main Processing Unit For Shinyei Sensors

Work for today consisted of soldering and wiring circuit boards which would serve as the central management unit for the complete Shinyei<sup>[1]</sup> sensor.

The processes of soldering, applying heat shrinks, and stripping wires was learned today. Adam was expecting to have 5 of these 'guts' (as he referred to them) for the Shinyei built today betweeen the two of us, but we managed to produce 10 before we were burnt out.

Experience was acquired soldering & dealing with construction of permanent circuitry instead of the breadboard stuff done at home.


**Main Components:**
- Seeduino Microcontroleer
- Seeduino Base Shield - interfacing with sensors and OLED display
- Single Cell LiPO Charger (Sunny Buddy) - manages charging of battery from solar panel
- INA219 DC current sensor ([math]\times[\math] 2) - current and voltage sensor, one for each of battery and solar panel
- Molex Connector (4-pin)
- Molex Connector (2-pin) (x2)
- Terminal Block (2-pin) (x2)

#### 2.1: Solder Connections From Seeduino To INA219s

1. Solder a 2-pin terminal block to each of two INA219 current sensors.
2. Cut a 4-pin Molex to Molex connecter in half and attach one end to the outermost Molex receiver on the Seeduino.
3. Split each of the four wires coing from the Molex connecter attached to the Seeduino by soldering two wires onto each of the aforementioned four wires.
4. Solder a red split wire to VCC on an INA219.
5. Solder a black split wire to Gnd on the same INA219.
6. Solder a yellow split wire to Scl on the same INA219.
7. Solder a white split wire to Sda on the same INA219.
8. Repeat the previous four steps with the other INA219.

#### 2.2: Solder Connections From Single Cell LiPO Charger (Sunny Buddy)

9. Cut off a 2-pin Molex connecter from a LiPO battery.
10. Attach the Molex end to the Molex receiver on the Sunny Buddy.
11. Solder the black wire on the Molex wire to "Solar -" on the Sunny Buddy.
12. Solder a wire to "Solar -" from above the circuit board of the Sunny Buddy /9the other end is loose and will act as a central Gnd).
13. Connect the red wire from the 2-pin Molex to Vin- on an INA219.
14. Connect "Solar +" from the Sunny Buddy to Vin- on the other INA219

#### 2.3: Concluding Steps 

15. Push the Seeduino Base Shield onto the Seeduino and verify that the power switch is set to 3.3V.
16. Solder A0 on the INA219 to which "Solar +" was connected to change the address of an INA219 to have Seeduino be able to distinguish between the INA219s

Rough circuit sketch can be found on page 79 of research notebook.

**Homework:**
- ~~Finish Daily Notes~~
- ~~Learn Some C++ Syntax~~

**[1]:** These are cheap air quality sensors that Lakitha and Adam intend on calibrating with machine learning to achieve the same level of accuracy as more expensive sensors. They plan on acquiring data from the expensive sensors and using it to train various ML models. Whichever performs most desirably will be used with the Shinyei sensor data to yield high accuracy with a low cost hardware.

## Wednesday, June 26, 2019

Work done today was using the different air quality sensors and coding them to display meaningful data.

### Task 3: Complete Arduino Exercises Given On Github

- Logged into the Arduino web IDE
- Finished exercises 2, 3 and 5; they were trivial
- Arduino IDE, Atom IDE, and Platform.io were preinstalled on the Ubuntu computer that was used for this
- Initially there was some difficulty with Exercise 8, largely due to the fact that no prior knowledge or experience existed about Ubuntu OS and Atom IDE, but after some searching the problems were resolved.
- Most modules I had worked with in the past required specification of which pins were to be used. In the code provided, there was no such mention and therefore I thought the code was meant to be run without a sensor.
- Upon running the code, the outputs were all printing 0, so there was something wrong. Upon connecting the BME280 sensor, the readings became normal.


### Task 4: Obtain Familiarization With The Air Quality Sensors

These consisted of the following:
- BME280 - (Temperature, Pressure, Light, Humidity)
- TMG3993 - (Light, Gesture, RGBC, Proximity)
- SCD30 - (CO2 Concentration, Temperature, Humidity)
- Multichannel Gas Sensor - (Concentrations of NH<sub>3</sub>, CO, NO<sub>2</sub>, C<sub>3</sub>H<sub>8</sub>, C<sub>4</sub>H<sub>10</sub>, CH<sub>4</sub>, H<sub>2</sub>, C<sub>2</sub>H<sub>5</sub>OH)


#### 4.1: BME280 - Temperature, Pressure, Light, Humidity

Following is the code for Nano to print everything BME280 can sense with a update delay of 1 second

- Include libraries
- Initialize sensor as instance of BME280 object
- Void setup
- - Initialize Wire
- - Initialize Serial with baud rate 9600
- - If sensor fails to initialize then print error
- Void loop
- - Print all information acquired by sensor to Serial Monitor
- - Remember that altitude is calculated as a function of pressure

~~~~
#include <Wire.h>
#include "Seeed_BME280.h"

BME280 sensor;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("BME280 Temperature, Pressure, Altitude, and Humidity");
  if (!sensor.init()) {
    Serial.print("Error with sensor");
  }
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(sensor.getTemperature());
  Serial.print(" C\nPressure: ");
  Serial.print(sensor.getPressure());
  Serial.print(" Pa");
  Serial.print("\nAltitude: ");
  Serial.print(sensor.calcAltitude(sensor.getPressure()));
  Serial.print("m \nHumidity: ");
  Serial.print(sensor.getHumidity());
  Serial.print("% \n --- \n");
  delay(1000);
}
~~~~

#### 4.2: TMG3993 - Light, Gesture, Proximity, RGBC

Following is the code for proximity detection from the TMG3993. It prints when proximity is detected or removed and LED_BUILTIN flashes when status of proximity changes.

- Include libraries
- Initialize sensor as instance of TMG3993 object
- Initialize status of proximity as 0 (removed)
- Void setup
- - Initialize Serial with baud rate 9600 and print sensor info
- - Initialize Wire
- - If sensor fails to initialize then print error
- - Setup sensor for proximity detection
- Void loop
- - Run following code only if sensor status is acquired and is valid (working properly)
- - - Get proximity of object to sensor
- - - If proximity is above threshold and status of proximity is 0 (removed) then print detection to Serial and set new status of proximity as 1 (detected)
- - - If proximity is below threshold and status of proximity is 1 (detected) then print detection to Serial and set new status of proximity as 0 (removed)
- - Delay 1 millisecond for stability

~~~~
#include <Wire.h>

#include "Seeed_TMG3993.h"

TMG3993 sensor;
int proximity_status = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("TMG3993 Proximity and RGBC");

  Wire.begin();

  if (sensor.initialize() == false)
  {
    Serial.println("Check Wiring");
  }
  sensor.setupRecommendedConfigForProximity();
  sensor.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN);
}

void loop()
{
  if (sensor.getSTATUS() & STATUS_PVALID)
  {
    int proximity = sensor.getProximityRaw();

    if (proximity < 50 && proximity_status == 0) {
      Serial.println("Proximity Detected");
      proximity_status = 1;
    }

    if (proximity > 50 && proximity_status == 1) {
      Serial.println("Proximity Removed");
      proximity_status = 0;
    }
  }
  delay(1);
}

~~~~

Following is the code for reading RGBC data (C stands for clear) for same sensor (TMG3993)

- Include libraries
- Initialize sensor as instance of TMG3993 object
- Void setup
- - Initialize Serial with baud rate 9600 and print sensor info
- - Initialzie Wire
- - If sensor fails to initialize then print error
- - Set up sensor for sensing RGBC
- Void loop
- - Run following code only if sensor status is acquired and is valid (working properly)
- - - Initialize r, g, b, c, lux, cct
- - - Get RGBC data by passing pointers of r, g, b, c to getRGBCRaw function so that it may overwrite those values
- - - Pass r, g, b, c to getLux and getCCt functions to get illuminance in luxes and CCT (Correlated Color Temperature) in Kelvin
- - - Print all this info to Serial
- - Delay 1 second for stability and readability

~~~~
#include <Wire.h>

#include "Seeed_TMG3993.h"

TMG3993 sensor;

void setup()
{
  Serial.begin(9600);
  Serial.println("TMG3993 Proximity and RGBC");

  Wire.begin();

  if (sensor.initialize() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }
  sensor.setADCIntegrationTime(0xdb); // the integration time: 103ms
  sensor.enableEngines(ENABLE_PON | ENABLE_AEN | ENABLE_AIEN);
}

void loop()
{
  if (sensor.getSTATUS() & STATUS_AVALID)
  {
    int r,g,b,c;
    int lux, cct;
    sensor.getRGBCRaw(&r, &g, &b, &c);
    lux = sensor.getLux(r, g, b, c);
    cct = sensor.getCCT(r, g, b, c);

    Serial.print("R: ");
    Serial.print(r);
    Serial.print("\tG: ");
    Serial.print(g);
    Serial.print("\tB: ");
    Serial.print(b);
    Serial.print("\tC: ");
    Serial.println(c);

    Serial.print("Lux: ");
    Serial.print(lux);
    Serial.print("\tCCT: ");
    Serial.println(cct);
    Serial.println("----");

    sensor.clearALSInterrupts();
  }
  delay(1000);
}
~~~~

#### SCD30 - CO2 Concentration, Temperature, Humidity

- Here is code to detect all with measurement interval 2 seconds

~~~~
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h"

SCD30 sensor;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("SCD30 CO2, Temperature, and Humidity");
  sensor.begin();
  sensor.setMeasurementInterval(2);
}

void loop() {
  Serial.print("CO2 Concentration:");
  Serial.print(sensor.getCO2());
  Serial.print(" ppm\nTemperature: ");
  Serial.print(sensor.getTemperature());
  Serial.print(" C\nHumidity: ");
  Serial.print(sensor.getHumidity());
  Serial.print("%\n---\n");
}

~~~~

- Similarly we can use
~~~~
sensor.setAltitudeCompensation(altitude in meters);
~~~~
and
~~~~
setAmbientPressure(pressure in millibars)
~~~~
to set default altitude and pressure respectively.

- Next was using the Multichannel Gas Sensor. Here is the code for detecting all gasses detectable by the module.

~~~~
#include <Arduino.h>
#include <Wire.h>
#include "MutichannelGasSensor.h"

void setup()
{
    Serial.begin(9600);  // start serial for output
    gas.begin(0x04); //the default I2C address of the slave is 0x04
    gas.powerOn();
}

void loop()
{
    float c;

    c = gas.measure_NH3();
    Serial.print("The concentration of NH3 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_CO();
    Serial.print("The concentration of CO is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_NO2();
    Serial.print("The concentration of NO2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C3H8();
    Serial.print("The concentration of C3H8 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C4H10();
    Serial.print("The concentration of C4H10 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_CH4();
    Serial.print("The concentration of CH4 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_H2();
    Serial.print("The concentration of H2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c = gas.measure_C2H5OH();
    Serial.print("The concentration of C2H5OH is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");

    delay(1000);
    Serial.println("---");
}
~~~~

- Lastly there was the sunlight sensor (Grove Sunlight Sensor) which senses Visible, IR, and UV light.

~~~~
#include <Arduino.h>
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
  Serial.print("---\n");
  Serial.println("Vis: "); Serial.println(SI1145.ReadVisible());
  Serial.println("IR: "); Serial.println(SI1145.ReadIR());
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  Serial.println("UV: ");  Serial.println((float)SI1145.ReadUV()/100);
  delay(1000);
}
~~~~

- Baudrate had to be altered from 9600 to 115200 however due to unknown reasons, even when Serial.begin was run with an argument of 9600. It could be a bug in the Nano or maybe it is just how the sensor transmitts information.
