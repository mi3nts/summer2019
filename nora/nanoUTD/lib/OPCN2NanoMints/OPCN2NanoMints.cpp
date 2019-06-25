/***************************************************************************
  OPCN2NanoMints
  ---------------------------------
  Written by: Lakitha Omal Harindha Wijeratne
  - for -
  Mints: Multi-scale Integrated Sensing and Simulation
  ---------------------------------
  Date: April 19th, 2019
  ---------------------------------
  This library is written for the Alphasense OPCN2 optical particle counter.
  ----------------> http://www.alphasense.com/WEB1213/wp-content/uploads/2018/02/OPC-N3.pdf
  --------------------------------------------------------------------------
  https://github.com/mi3nts
  http://utdmints.info/

 ***************************************************************************/

#include "OPCN2NanoMints.h"
#include <Arduino.h>
#include <SPI.h>
/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 OPCN2NanoMints::OPCN2NanoMints(uint8_t chipSelect){
  alphaSlavePin  = chipSelect;
 }

// Alpha Sensor Functions
 void OPCN2NanoMints::begin()
{
    printMintsBegin();
    Serial.println("Initiating SPI ");
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    delay(1000);
    pinMode(alphaSlavePin,OUTPUT);
    digitalWrite(alphaSlavePin,HIGH);
    SPI.setDataMode(SPI_MODE1);
    SPI.setClockDivider(SPI_CLOCK_DIV32);
    delay(400);
    Serial.println("---------------------------- ");
    printMintsEnd();

}


bool OPCN2NanoMints::initialize(){

        delay(1000);
        begin();
        delay(1000);
        readDigitalPotStatus();
        delay(1000);
        readInformationString();
        delay(1000);
        readSerialNumber();
        delay(1000);
        readFirmwareVersion();
        delay(1000);
        readConfigurationVariables();
        delay(1000);
        readConfigurationVariables2();
        delay(1000);

        struct fanAndLaserStatus fanAndLaserState = setFanAndLaserStatus(true);
        delay(10000);
        struct digitalPotStatus digitalPotState = readDigitalPotStatus();
        readPMData() ;

    return (fanAndLaserState.valid&&fanAndLaserState.fanAndLaserOn)&&(digitalPotState.fanOn&&digitalPotState.laserOn);
}







  struct fanAndLaserStatus OPCN2NanoMints::setFanAndLaserStatus(bool status){

        printMintsBegin();
        Serial.println("Setting Fan and Laser Status");
        int  size = 1;
        byte validator = 0XF3;
        byte initial ;
        byte dataIn[size];
        byte inputByte  =  0X03;;

        if(status){
            Serial.println("Turning Fan and Laser On");
            beginTransfer();
            initial   = SPI.transfer(inputByte);
            delay(10);
            dataIn[0] = SPI.transfer(0X00);
            endTransfer();
        }else{

          Serial.println("Turning Fan and Laser Off");
          beginTransfer();
          initial   = SPI.transfer(inputByte);
          delay(10);
          dataIn[0] = SPI.transfer(0X01);
          endTransfer();
        }

       printBytesRead(initial,dataIn,size);

       fanAndLaserStatus dataOutput;
       dataOutput.valid                = comparator(validator, initial,1);
       dataOutput.fanAndLaserOn        = status;

       Serial.print("Validity: ");
       Serial.println(dataOutput.valid);
       Serial.print(dataOutput.fanAndLaserOn); Serial.print(" ");
       printMintsEnd();

       return dataOutput;
    }


    struct fanStatus OPCN2NanoMints::setFanStatus(bool status) {

      printMintsBegin();
      Serial.println("Setting Fan Status");
      int  size = 1;
      byte validator = 0XF3;
      byte initial ;
      byte dataIn[size];
      byte inputByte  =  0X03;;

      if(status){
          Serial.println("Turning Fan On");
          beginTransfer();
          initial   = SPI.transfer(inputByte);
          delay(10);
          dataIn[0] = SPI.transfer(0X04);
          endTransfer();
      }else{

        Serial.println("Turning Fan Off");
        beginTransfer();
        initial   = SPI.transfer(inputByte);
        delay(10);
        dataIn[0] = SPI.transfer(0X05);
        endTransfer();
      }

     printBytesRead(initial,dataIn,size);

     fanStatus dataOutput;
     dataOutput.valid                = comparator(validator, initial,1);
     dataOutput.fanOn        = status;

     Serial.print("Validity: ");
     Serial.println(dataOutput.valid);
     Serial.print(dataOutput.fanOn); Serial.print(" ");
     printMintsEnd();
     delay(1000);
     return dataOutput;
      }


struct laserStatus OPCN2NanoMints::setLaserStatus(bool status){

    printMintsBegin();
    Serial.println("Setting Laser Status");
    int  size = 1;
    byte validator = 0XF3;
    byte initial ;
    byte dataIn[size];
    byte inputByte  =  0X03;;

    if(status){

        Serial.println("Turning Laser On");
        beginTransfer();
        initial   = SPI.transfer(inputByte);
        delay(10);
        dataIn[0] = SPI.transfer(0X02);
        endTransfer();

    }else{

        Serial.println("Turning Laser Off");
        beginTransfer();
        initial   = SPI.transfer(inputByte);
        delay(10);
        dataIn[0] = SPI.transfer(0X03);
        endTransfer();
    }

       printBytesRead(initial,dataIn,size);

       laserStatus dataOutput;
       dataOutput.valid                = comparator(validator, initial,1);
       dataOutput.laserOn        = status;

       Serial.print("Validity: ");
       Serial.println(dataOutput.valid);
       Serial.print(dataOutput.laserOn); Serial.print(" ");
       printMintsEnd();
       delay(1000);
       return dataOutput;

  }

struct digitalPotStatus OPCN2NanoMints::readDigitalPotStatus() {
       printMintsBegin();
       Serial.println("Reading Digital Pot Status");
       int  size = 4;
       byte validator = 0XF3;
       byte initial ;
       byte dataIn[size];
       byte inputByte  =  0X13;;

       beginTransfer();
       initial = SPI.transfer(inputByte);
       delayMicroseconds(9990);
       for (int i = 0 ; i<size; i++)
          {
          delayMicroseconds(10);
          dataIn[i] = SPI.transfer(inputByte);
          }

     endTransfer();
     printBytesRead(initial,dataIn,size);


   digitalPotStatus dataOutput;
   memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
   dataOutput.valid  = comparator(validator, initial,1);
   Serial.print("Validity: ");
   Serial.println(dataOutput.valid);
   Serial.print(dataOutput.fanOn);    Serial.print(" ");
   Serial.print(dataOutput.laserOn);  Serial.print(" ");
   Serial.print(dataOutput.fanDACVal );  Serial.print(" ");
   Serial.print(dataOutput.laserDACVal);  Serial.print(" ");
   printMintsEnd();
   delay(1000);
   return dataOutput;
  }


struct informationString OPCN2NanoMints::readInformationString() {
    printMintsBegin();
    Serial.println("Reading information String");
    int  size = 60;
    byte validator = 0XF3;
    byte initial ;
    byte dataIn[size];
    byte inputByte  =  0X3F;

    beginTransfer();
    initial = SPI.transfer(inputByte);
    delayMicroseconds(9990);
    for (int i = 0 ; i<size; i++)
    {
      delayMicroseconds(10);
      dataIn[i] = SPI.transfer(inputByte);
    }
   endTransfer();

   printBytesRead(initial,dataIn,size);

    String info = "";
      for (int i = 0; i<size ; i++){
         info += String((char)dataIn[i]);
      }

     informationString dataOutput;
     dataOutput.valid        = comparator(validator, initial,1);
     dataOutput.information  = info;

     Serial.print("Validity: ");
     Serial.print(dataOutput.valid)      ;   Serial.println(" ");
     Serial.print(dataOutput.information);   Serial.print(" ");
     printMintsEnd();
       delay(1000);
    return dataOutput;
    }


struct serialNumber OPCN2NanoMints::readSerialNumber() {
    printMintsBegin();
    Serial.println("Reading Serial Number");
    int  size = 60;
    byte validator = 0XF3;
    byte initial ;
    byte dataIn[size];
    byte inputByte  =  0X10;

    beginTransfer();
    initial = SPI.transfer(inputByte);
    delayMicroseconds(9990);
    for (int i = 0 ; i<size; i++)
    {
    delayMicroseconds(10);
    dataIn[i] = SPI.transfer(inputByte);
    }
    endTransfer();

    printBytesRead(initial,dataIn,size);

    String info = "";
    for (int i = 0; i < size; i++){
       info += String((char)dataIn[i]);
    }

    serialNumber dataOutput;
    dataOutput.valid   = comparator(validator, initial,1);
    dataOutput.serial  = info;
          //

    Serial.print("Validity: ");
    Serial.print(dataOutput.valid) ;  Serial.println(" ");
    Serial.print(dataOutput.serial);  Serial.print(" ");
    printMintsEnd();
       delay(1000);
    return dataOutput;

}




struct firmwareVersion OPCN2NanoMints::readFirmwareVersion() {
    printMintsBegin();
    Serial.println("Reading Firmware Version ");
    int  size = 2;
    byte validator = 0XF3;
    byte initial ;
    byte dataIn[size];
    byte inputByte  =  0X12;

    beginTransfer();
    initial = SPI.transfer(inputByte);
    delayMicroseconds(9990);
    for (int i = 0 ; i<size; i++)
    {
      delayMicroseconds(10);
      dataIn[i] = SPI.transfer(inputByte);
    }
    endTransfer();

    printBytesRead(initial,dataIn,size);


    firmwareVersion dataOutput;
    memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
    dataOutput.valid  = comparator(validator, initial,1);

   Serial.print("Validity: ");
   Serial.print(dataOutput.valid)  ; Serial.println(" ");
   Serial.print(dataOutput.major);   Serial.print(" ");
   Serial.print(dataOutput.minor);   Serial.print(" ");
   printMintsEnd();
       delay(1000);
return  dataOutput;

}



void OPCN2NanoMints::readConfigurationVariables() {
  printMintsBegin();
  Serial.println("Reading Configeration Varibles ");
  int  size = 256;
  byte validator = 0XF3;
  byte initial ;
  byte dataIn[size];
  byte inputByte  =  0X3C;

  beginTransfer();
  initial = SPI.transfer(inputByte);
  delayMicroseconds(9990);
  for (int i = 0 ; i<size; i++)
  {
    delayMicroseconds(10);
    dataIn[i] = SPI.transfer(inputByte);
  }
  endTransfer();

  printBytesRead(initial,dataIn,size);

//
//   configurationVariables dataOutput;
//   memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
//   dataOutput.valid  = comparator(validator, initial,1);
//
//  Serial.print("Validity: ");
//  Serial.println(dataOutput.valid);
//  Serial.println("Bin Boundries");
//  Serial.print(dataOutput.binBoundries0);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries1);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries2);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries3);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries4);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries5);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries6);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries7);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries8);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries9);Serial.println(" ");
//  Serial.print(dataOutput.binBoundries10);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries11);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries12);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries13);Serial.print(" ");
//  Serial.print(dataOutput.binBoundries14);Serial.print(" ");
//
// Serial.println("-------------------------------------------------");
// Serial.println("Bin Boundries Spare");
// Serial.print(dataOutput.binBoundriesSpare);Serial.print(" ");
//
// Serial.println("-------------------------------------------------");
// Serial.println("Bin Particle Volumes");
// Serial.print(dataOutput.binParticleVolume0);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume1);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume2);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume3);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume4);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume5);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume6);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume7);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume8);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume9);Serial.println(" ");
// Serial.print(dataOutput.binParticleVolume10);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume11);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume12);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume13);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume14);Serial.print(" ");
// Serial.print(dataOutput.binParticleVolume15);Serial.print(" ");
// Serial.println("");
//
// Serial.println("-------------------------------------------------");
// Serial.println("Bin Particle Densities");
// Serial.print(dataOutput.binParticleDensity0);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity1);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity2);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity3);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity4);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity5);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity6);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity7);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity8);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity9);Serial.println(" ");
// Serial.print(dataOutput.binParticleDensity10);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity11);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity12);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity13);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity14);Serial.print(" ");
// Serial.print(dataOutput.binParticleDensity15);Serial.print(" ");
//
//
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Bin Sample Volume Weights ");
// Serial.print(dataOutput.binSampleVolumeWeight0);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight1);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight2);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight3);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight4);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight5);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight6);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight7);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight8);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight9);Serial.println(" ");
// Serial.print(dataOutput.binSampleVolumeWeight10);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight11);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight12);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight13);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight14);Serial.print(" ");
// Serial.print(dataOutput.binSampleVolumeWeight15);Serial.print(" ");
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Gain Scaling Coefficient");
// Serial.print(dataOutput.gainScalingCoefficient);Serial.print(" ");
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Sample Flow Rate");
// Serial.print(dataOutput.sampleFlowRate);Serial.print(" ");
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Laser DAC Val");
// Serial.print(dataOutput.laserDACVal);Serial.print(" ");
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Fan DAC Val");
// Serial.print(dataOutput.fanDACVal);Serial.print(" ");
// Serial.println("");
// Serial.println("-------------------------------------------------");
// Serial.println("Time of Flight to Sample Flow Rate conversion factor");
// Serial.print(dataOutput.tofToSfrFactor);Serial.print(" ");
//
// printMintsEnd();
   delay(1000);
// return  dataOutput;

}

void OPCN2NanoMints::readConfigurationVariables2() {
  printMintsBegin();
  Serial.println("Reading Configeration Varibles 2");
  int  size = 9;
  byte validator = 0XF3;
  byte initial ;
  byte dataIn[size];
  byte inputByte  =  0X3D;

  beginTransfer();
  initial = SPI.transfer(inputByte);
  delayMicroseconds(9990);
  for (int i = 0 ; i<size; i++)
  {
    delayMicroseconds(10);
    dataIn[i] = SPI.transfer(inputByte);
  }
  endTransfer();

  printBytesRead(initial,dataIn,size);


//   configurationVariables2 dataOutput;
//   memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
//   dataOutput.valid  = comparator(validator, initial,1);
//
//  Serial.print("Validity: ");
//  Serial.println(dataOutput.valid);
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Sampling Interval Count");
//  Serial.print(dataOutput.AMSamplingIntervalCount);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Idle Interval Count");
//  Serial.print(dataOutput.AMIdleIntervalCount);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Fan On In Idle");
//  Serial.print(dataOutput.AMFanOnInIdle);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Laser On In Idle");
//  Serial.print(dataOutput.AMLaserOnInIdle);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Max Data Arrays InFile");
//  Serial.print(dataOutput.AMMaxDataArraysInFile);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("AM Only Save PM Data");
//  Serial.print(dataOutput.AMOnlySavePMData);Serial.print(" ");
//
// printMintsEnd();
   delay(1000);
// return  dataOutput;

}

struct histogramData OPCN2NanoMints::readHistogramData() {
  // printMintsBegin();
  // Serial.println("Reading Histogram Data");
  int  size = 62;
  byte validator = 0XF3;
  byte initial ;
  byte dataIn[size];
  byte inputByte  =  0X30;

  beginTransfer();
  initial = SPI.transfer(inputByte);
  delayMicroseconds(9990);
  for (int i = 0 ; i<size; i++)
  {
    delayMicroseconds(10);
    dataIn[i] = SPI.transfer(inputByte);
  }
  endTransfer();

  // printBytesRead(initial,dataIn,size);


  histogramData dataOutput;
  memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
  dataOutput.valid  = comparator(validator, initial,1);
//
//  Serial.print("Validity: ");
//  Serial.println(dataOutput.valid);
//  Serial.println("Bin Counts");
//  Serial.print(dataOutput.binCount0);Serial.print(" ");
//  Serial.print(dataOutput.binCount1);Serial.print(" ");
//  Serial.print(dataOutput.binCount2);Serial.print(" ");
//  Serial.print(dataOutput.binCount3);Serial.print(" ");
//  Serial.print(dataOutput.binCount4);Serial.print(" ");
//  Serial.print(dataOutput.binCount5);Serial.print(" ");
//  Serial.print(dataOutput.binCount6);Serial.print(" ");
//  Serial.print(dataOutput.binCount7);Serial.print(" ");
//  Serial.print(dataOutput.binCount8);Serial.print(" ");
//  Serial.print(dataOutput.binCount9);Serial.println(" ");
//  Serial.print(dataOutput.binCount10);Serial.print(" ");
//  Serial.print(dataOutput.binCount11);Serial.print(" ");
//  Serial.print(dataOutput.binCount12);Serial.print(" ");
//  Serial.print(dataOutput.binCount13);Serial.print(" ");
//  Serial.print(dataOutput.binCount14);Serial.print(" ");
//  Serial.print(dataOutput.binCount15);Serial.print(" ");
//  Serial.println("");
//  Serial.println("-------------------------------------------------");
//  Serial.println("Time To Cross");
//  Serial.print(dataOutput.bin1TimeToCross);Serial.print(" ");
//  Serial.print(dataOutput.bin3TimeToCross);Serial.print(" ");
//  Serial.print(dataOutput.bin5TimeToCross);Serial.print(" ");
//  Serial.print(dataOutput.bin7TimeToCross);Serial.println(" ");
//
//  Serial.println("-------------------------------------------------");
//  Serial.println("Sample Flow Rate");
//  Serial.println(dataOutput.sampleFlowRate);
//  Serial.println("-------------------------------------------------");
//  Serial.println("Temperature Or Pressure");
//  Serial.println(dataOutput.temperatureOrPressure);
//  Serial.println("-------------------------------------------------");
//  Serial.println("Sampling Period");
//  Serial.println(dataOutput.samplingPeriod);
//  Serial.println("-------------------------------------------------");
//  Serial.println("Check Sum");
//  Serial.println(dataOutput.checkSum);
//  Serial.println("-------------------------------------------------");
//  Serial.println("pm1");
//  Serial.println(dataOutput.pm1);
//  Serial.println("-------------------------------------------------");
//  Serial.println("pm2.5");
//  Serial.println(dataOutput.pm2_5);
//  Serial.println("-------------------------------------------------");
//  Serial.println("pm10");
//  Serial.println(dataOutput.pm10);
//  Serial.println("-------------------------------------------------");
//
// printMintsEnd();

return  dataOutput;

}


struct pmData OPCN2NanoMints::readPMData() {
  printMintsBegin();
  Serial.println("Reading Pm Data");
  int  size = 12;
  byte validator = 0XF3;
  byte initial ;
  byte dataIn[size];
  byte inputByte  =  0X32;

  beginTransfer();
  initial = SPI.transfer(inputByte);
  delayMicroseconds(9990);
  for (int i = 0 ; i<size; i++)
  {
    delayMicroseconds(10);
    dataIn[i] = SPI.transfer(inputByte);
  }
  endTransfer();

  printBytesRead(initial,dataIn,size);


  pmData dataOutput;
  memcpy(&dataOutput, &dataIn, sizeof(dataOutput));
  dataOutput.valid  = comparator(validator, initial,1);



 Serial.print("Validity: ");
 Serial.println(dataOutput.valid);
 Serial.println("-------------------------------------------------");
 Serial.println("pm1");
 Serial.println(dataOutput.pm1);
 Serial.println("-------------------------------------------------");
 Serial.println("pm2.5");
 Serial.println(dataOutput.pm2_5);
 Serial.println("-------------------------------------------------");
 Serial.println("pm10");
 Serial.println(dataOutput.pm10);


printMintsEnd();

return  dataOutput;

}


bool OPCN2NanoMints::comparator(byte arrayOne[], byte arrayTwo[], int size)
  {

    bool valid = true;

    for (int i = 0; i < size; i++){
         if (arrayOne[i] != arrayTwo[i])
           {
            valid = false;
           }
    }

    return valid;
  }



void OPCN2NanoMints::beginTransfer() {

   digitalWrite(alphaSlavePin, LOW);
  delay(1);
   }

void OPCN2NanoMints::endTransfer() {
delay(1);
   digitalWrite(alphaSlavePin, HIGH);

}


void OPCN2NanoMints::printBytesRead(byte initial[], byte dataIn[], int sizeOfArray)
{
    Serial.println("--------------------------------");
    Serial.println("Printing Initial Bytes----------");
    Serial.print(initial[0],HEX);
    Serial.print(" ");
    Serial.println("--------------------------------");
    Serial.println("Printing Byte Array-------------");

    for (int i = 0 ; i<sizeOfArray; i++)
        {
            Serial.print(dataIn[i],HEX);
            Serial.print(" ");
            if(i%10==9)
              {
              Serial.println("");
              }
        }

  Serial.println("");
  Serial.println("--------------------------------");
}



void OPCN2NanoMints::printMintsBegin(){
  Serial.println("");
  Serial.println("--------------------------------");
  Serial.println("-------------MINTS--------------");

}


  void OPCN2NanoMints::printMintsEnd(){
    Serial.println("");
    Serial.println("-------------MINTS--------------");
    Serial.println("--------------------------------");
}
