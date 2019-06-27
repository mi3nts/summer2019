/*
Written by Shrey Joshi.

Displays Temperature in Celsius, Pressure in Pascals, Altitude in Meters, and Humidity.
Measurement Interval is 1 second.
*/

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
