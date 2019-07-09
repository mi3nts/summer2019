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
 - Take out the circuit board and the wiresmega168 

## June 25, 2019
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
  Serial.println("Began");
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
#### 3.5 Use Light-Gesture-Color-Proximity Sensor
 - Connect the hardware
 - Download the library from [here](https://github.com/Seeed-Studio/Seeed_TMG3993)
 - Copy the folder with the library into the lib folder inside your project
 - Write the following code (found in the example from the library):
 ````
 #include <Arduino.h>
#include <Wire.h>
#include "Seeed_TMG3993.h"

TMG3993 tmg3993;

void setup()
{
  Serial.begin(9600);
  Serial.println("TMG3993 Proximity Example");

  Wire.begin();

  if (tmg3993.initialize() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }
  tmg3993.setupRecommendedConfigForProximity();
  tmg3993.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN);
}

void loop()
{
  if (tmg3993.getSTATUS() & STATUS_PVALID)
  {
    uint8_t proximity_raw = tmg3993.getProximityRaw();  //read the Proximity data will clear the status bit
    Serial.print("Proximity Raw: ");
    Serial.println(proximity_raw);
  }
  delay(1);
}
````
- Check that the output changes as you move your hand closer and further

### Task 4: Connect all sensors together in one program
#### 4.1 Connect hardware
 - Use wire bridges and some more boards to connect all of the sensors to the arduino
#### 4.2 Import necessary libraries
 - Import the seeed_TMG3993 and the MultichannelGasSensor libraries
 - Make sure you have installed all the necessary libraries for the other sensors
 - All of these libraries were refrenced earlie, with the exception of the MultichannelGasSensor library which can be found in this project.
#### 4.3 Create program
 - Type the following code, which will run all of the five sensors:
 ````
 #include <Arduino.h>
#include <Wire.h>

#include "Seeed_TMG3993.h"
#include "Seeed_BME280.h"
#include "SparkFun_SCD30_Arduino_Library.h"
#include "SI114X.h"
#include "MutichannelGasSensor.h"

TMG3993 tmg3993;
BME280 bme280;
SCD30 scd30;
SI114X SI1145 = SI114X();

void setup()
{
  Serial.begin(9600);
  Serial.println("TMG3993 Proximity Example");

  Wire.begin();

  //Initialize TMG3993 sensor
  if (tmg3993.initialize() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }
  tmg3993.setupRecommendedConfigForProximity();
  tmg3993.enableEngines(ENABLE_PON | ENABLE_PEN | ENABLE_PIEN);

  //Initialize BME 280 sensor
  if(!bme280.init()){
     Serial.println("Device error!");
  }

  scd30.begin();

  //Initialize SI1145
  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }

  //Initialize MutichannelGasSensor
  gas.begin(0x04);//the default I2C address of the slave is 0x04
  gas.powerOn();

}

void trybme280(){
  //Get BME280 reading
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
}

void loop()
{
  //Get TMG3993 reading
  if (tmg3993.getSTATUS() & STATUS_PVALID)
  {
    uint8_t proximity_raw = tmg3993.getProximityRaw();  //read the Proximity data will clear the status bit
    Serial.print("Proximity Raw: ");
    Serial.println(proximity_raw);
  }

  Serial.println("_________________________");
  trybme280();
  Serial.println("_________________________");

  if (scd30.dataAvailable())
   {
     Serial.print("co2(ppm):");
     Serial.print(scd30.getCO2());

     Serial.print(" temp(C):");
     Serial.print(scd30.getTemperature(), 1);

     Serial.print(" humidity(%):");
     Serial.print(scd30.getHumidity(), 1);

     Serial.println();
   }
   else
     Serial.println("No data");

  Serial.println("_________________________");

  Serial.print("Vis: ");
  Serial.println(SI1145.ReadVisible());
  Serial.print("IR: ");
  Serial.println(SI1145.ReadIR());
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  Serial.print("UV: ");
  Serial.println((float)SI1145.ReadUV()/100);
  Serial.println("_________________________");


  //Multichannel Gas Sensor Readings
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
  Serial.println("_________________________");


  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println();

}
````
 - Watch the output and check for correctness

## June 26, 2019 & July 2, 2019
### Task 5: Building Sensor
The follwoing procedures may have some errors or omissions
#### 5.1 Splitting wires
 - Take a four-wire cable and cut in the middle, and separate the four wires
 - Expose the ends of each wire
 - Hook the end of each wire and tie to combine with two more wires
 - Solder the wires together, to make each of the four wires split into two wires
 - Cover the exposed wire with heat shrink
#### 5.2 Prepare the two voltage sensors (one for the battery and one for the solar panel)
 - Attach a two-pin wire holder to each sensor and solder
 - For each of the sensor, attach four of the split wires into the designated holes (GND, VCC, SDA, SLC)
#### 5.3 Prepare the Sunny Buddy
 - Connect a two wire cable to the port on the Sunny Buddy
 - Connect the black wire from this cable to the "solar -" hole and solder. Solder another wire to its other side in order to extend it. Cover exposed wire with heat shrink.
#### 5.4 Connect Seeduino to voltage sensors
 - Connect a blue wire to the "solar +" hole on the Sunny Buddy
 - Connect this blue wire to the pin on the solar panel voltage sensor
 - Solder a bit of tin onto the address of the solar panel voltage sensor to change the address
 - Connect the red wire from the port on the Sunny Buddy to the battery sensor
#### 5.5 Finish up
 - Connect the four-wire cable to the main Seeduino
 - Connect one end of a two-wire cable to port of the Seeduino, and solder the other end to the load wire holes of the Sunny Buddy
 - Cover the Seeduino with a base shield

## July 8, 2019
### Task 6: Checking wire connections to sensors
#### 6.1 Connect wires to arduino
 - Connect the red wire to 5V
 - Black goes to GND
 - White tp D10
 - Blue to D11
 - Green to D12
 - Yellow wire to D13
 - Connect the wires to the sensor and connect the arduino to the computer with a USB cable
#### 6.2 Collect data
 - Type the following on the terminal: 
 ```` screen /dev/cu.usbserial-AH06AI47 ````
 - Check that the device provides the correct data. It should eventually print ```#mintsO!OPCN2>1:``` followed by some number, followed by a lot more data.
#### 6.3 Finish up
 - If wire collects data correctly, disconnect from the arduino and sensor, cover exposed wire with heat shrink, and heat. Then put aside.
 
### Task 7: Connect wires
 - Get 3 four-pin cable and one of the six-wire cables from task 6
 - Wrap all the red wires among these together and wrap with a copper solid wire around them. Do the same for the black wires.
 - Wrap all the yellow wires from the 4-pin cable together (DO NOT use the wire from the six-wire cable) and wrap with a solid wire. Do the same for the white wires.
 
## July 9-10, 2019
### Task 8: Assemble sensors
Mount a BME2800 sensor, a dust sensor, and a multichannel gas sensor, as well as two arduinos, on the sensor.

### Task 9: Write serial inputs to CSV
Full python program can be found in this directory, named "SerialReader.python"
#### 9.1 Get input
 - Type ```` screen /dev/cu.usbserial-AH06AI47 ```` to get serial inputs and copy-paste some of the data to a text file.
#### 9.2 Process data
 - Process serial data, splitting the string at ````#mintsO!````, in order to make it easier to transfer to a python dictionary.
````
#Get data
file = open(r"Data.txt", "r") #Read file
contents = file.read()
#Process data
contents.replace("~", "") #Get rid of the ~ in the string
contents = contents.split("#mintsO!B") #Split the file into a list of strings for each iteration of data
del contents[0] # Get rid of empty first string
````
#### 9.3 Make dictionaries
 - Make one dictionary for each sensor and set to 0
 ````
 #Create a dictionary for each sensor's variables
BME280 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "time": 0}
MGS001 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "var5": 0, "var6": 0, "var7": 0, "var8": 0, "time": 0}
OPCN2 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "var5": 0, "var6": 0, "var7": 0, "var8": 0, "var9": 0, "time": 0,
         "var10": 0, "var11": 0, "var12": 0, "var13": 0, "var14": 0, "var15": 0, "var16": 0, "var17": 0,
         "var18": 0, "var19": 0, "var20": 0, "var21": 0, "var22": 0, "var23": 0, "var24": 0, "var25": 0,
         "var26": 0, "var27": 0, "var28": 0, "time": 0}
SCD30 = {"var1": 0, "var2": 0, "var3": 0, "time": 0}
````
#### 9.4 Create a function to fill data into the dictionary
````
def fillDict(num, dict, data):
  curDat = [data[num].split(":")[0].split(">")[1]] +  data[num].split(":")[1:]
  for key, dat in zip(dict.keys(), curDat):
      dict[key] = dat
  dict["time"] = datetime.now()
````
#### 9.5 Create a function to make a csv file from each dictionary
````
def makeCSV(dict, fileName, makeHeaders):
    keys = list(dict.keys())
    with open(fileName, "a") as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=keys);
        if(makeHeaders):
            writer.writeheader()
            print()
        writer.writerow(dict)
    csvFile.close()
````
#### 9.6 Loop over each iteration of data and update csv files
````
for data in contents:
    #Split vars of into sensors
    data = data.split("~#mintsO!")

    #Put variables of each sensor into the list
    fillDict(0, BME280, data)
    fillDict(1, MGS001, data)
    fillDict(2, OPCN2, data)
    fillDict(3, SCD30, data)

    #Make the csv file for each sensor
    makeCSV(BME280, "BME280.csv", not(os.path.isfile("BME280.csv")))
    makeCSV(MGS001, "MGS001.csv", not(os.path.isfile("MGS001.csv")))
    makeCSV(OPCN2, "OPCN2.csv", not(os.path.isfile("OPCN2.csv")))
    makeCSV(SCD30, "SCD30.csv", not(os.path.isfile("SCD30.csv")))
````

