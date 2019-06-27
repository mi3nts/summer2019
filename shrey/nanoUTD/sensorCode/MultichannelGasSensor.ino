/*
Written by Shrey Joshi

Displays concentrations of NH3, CO, NO2, C3H8, C4H10, CH4, H2, C2H5OH.
*/

#include <Arduino.h>
#include <Wire.h>
#include "MutichannelGasSensor.h"

void setup()
{
    Serial.begin(9600);
    gas.begin(0x04); //the default I2C address of the slave is 0x04
    gas.powerOn();
}

void loop()
{
    char gasses[8] = {'NH3', 'CO', 'NO2', 'C3H8', 'C4H10', 'CH4', 'H2', 'C2H5OH'};
    float concentrations[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    for (int i = 0; i < 8; i++) {
        Serial.print("The concentration of ");
        Serial.print(gasses[i]);
        Serial.print(" is:");
        if (concentrations[i] >= 0) {
            Serial.print(concentrations[i]);
        } else {
            Serial.print("invalid");
        }
        Serial.println(" ppm\n");
    }
    delay(1000);
    Serial.println("---");
}
