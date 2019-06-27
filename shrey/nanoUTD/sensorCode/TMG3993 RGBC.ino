/*
Adapted From example code

Displays RGBC data
*/

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
    Serial.println("Check wiring");
    while (1);
  }
  sensor.setADCIntegrationTime(0xdb);
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
