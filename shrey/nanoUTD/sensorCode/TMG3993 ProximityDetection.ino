/*
Written by Shrey Joshi
*/
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
