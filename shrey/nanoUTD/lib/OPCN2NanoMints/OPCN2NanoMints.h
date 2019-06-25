#ifndef OPCN2_NANO_MINTS_H
#define OPCN2_NANO_MINTS_H

#include <Arduino.h>
#include <SPI.h>

class OPCN2NanoMints
{
private:
    // attributes
    uint8_t alphaSlavePin;

public:

  OPCN2NanoMints(uint8_t chipSelect);
  // Alpha Sensor Functions
  void begin();
  bool initialize();
  void beginTransfer();
  void endTransfer();
  void printBytesRead(byte initial[],byte dataIn[], int sizeOfArray) ;

  struct fanAndLaserStatus setFanAndLaserStatus(bool status);
  struct fanStatus setFanStatus(bool status);
  struct laserStatus setLaserStatus(bool status);
  struct laserPower setLaserPower(byte laserPower);
  struct fanPower setFanPower(byte fanPower);

  struct digitalPotStatus readDigitalPotStatus();
  struct informationString readInformationString();
  struct serialNumber readSerialNumber();
  struct firmwareVersion readFirmwareVersion();

  // There are two
  void readConfigurationVariables();
  void readConfigurationVariables2();

  struct histogramData readHistogramData() ;
  struct pmData readPMData() ;

  void printMintsBegin();
  void printMintsEnd();
  bool comparator(byte arrayOne[], byte arraTwo[], int size);

};



    struct fanAndLaserStatus
    {
    bool fanAndLaserOn;
    bool valid;
    };

    struct fanStatus
    {
    bool fanOn;
    bool valid;
    };

    struct laserStatus
    {
    bool laserOn;
    bool valid;
    };

    struct fanPower
    {
    uint8_t fanPower;
    bool valid;
    };

    struct laserPower
    {
    uint8_t laserPower;
    bool valid;
    };

    struct digitalPotStatus
    {
    uint8_t fanOn;
    uint8_t laserOn;
    uint8_t fanDACVal;
    uint8_t laserDACVal;
    bool valid;

    };

    struct informationString
    {
    String information;
    bool valid;
    };

    struct serialNumber
    {
    String serial;
    bool valid;
    };

    struct firmwareVersion
    {
    uint8_t major;
    uint8_t minor;
    bool valid;
    };

  //
  //   struct configurationVariables
  //   {
  //
  //   uint16_t binBoundries0;
  //   uint16_t binBoundries1;
  //   uint16_t binBoundries2;
  //   uint16_t binBoundries3;
  //   uint16_t binBoundries4;
  //   uint16_t binBoundries5;
  //   uint16_t binBoundries6;
  //   uint16_t binBoundries7;
  //   uint16_t binBoundries8;
  //   uint16_t binBoundries9;
  //   uint16_t binBoundries10;
  //   uint16_t binBoundries11;
  //   uint16_t binBoundries12;
  //   uint16_t binBoundries13;
  //   uint16_t binBoundries14;
  //
  //   uint16_t binBoundriesSpare;
  //
  //   float binParticleVolume0;
  //   float binParticleVolume1;
  //   float binParticleVolume2;
  //   float binParticleVolume3;
  //   float binParticleVolume4;
  //   float binParticleVolume5;
  //   float binParticleVolume6;
  //   float binParticleVolume7;
  //   float binParticleVolume8;
  //   float binParticleVolume9;
  //   float binParticleVolume10;
  //   float binParticleVolume11;
  //   float binParticleVolume12;
  //   float binParticleVolume13;
  //   float binParticleVolume14;
  //   float binParticleVolume15;
  //
  //   float binParticleDensity0;
  //   float binParticleDensity1;
  //   float binParticleDensity2;
  //   float binParticleDensity3;
  //   float binParticleDensity4;
  //   float binParticleDensity5;
  //   float binParticleDensity6;
  //   float binParticleDensity7;
  //   float binParticleDensity8;
  //   float binParticleDensity9;
  //   float binParticleDensity10;
  //   float binParticleDensity11;
  //   float binParticleDensity12;
  //   float binParticleDensity13;
  //   float binParticleDensity14;
  //   float binParticleDensity15;
  //
  //   float binSampleVolumeWeight0;
  //   float binSampleVolumeWeight1;
  //   float binSampleVolumeWeight2;
  //   float binSampleVolumeWeight3;
  //   float binSampleVolumeWeight4;
  //   float binSampleVolumeWeight5;
  //   float binSampleVolumeWeight6;
  //   float binSampleVolumeWeight7;
  //   float binSampleVolumeWeight8;
  //   float binSampleVolumeWeight9;
  //   float binSampleVolumeWeight10;
  //   float binSampleVolumeWeight11;
  //   float binSampleVolumeWeight12;
  //   float binSampleVolumeWeight13;
  //   float binSampleVolumeWeight14;
  //   float binSampleVolumeWeight15;
  //
  //   float gainScalingCoefficient;
  //   float sampleFlowRate;
  //
  //   uint8_t laserDACVal;
  //   uint8_t fanDACVal;
  //   uint8_t tofToSfrFactor;
  //
  //   uint8_t spare0;
  //   uint8_t spare1;
  //   uint8_t spare2;
  //   uint8_t spare3;
  //   uint8_t spare4;
  //   uint8_t spare5;
  //   uint8_t spare6;
  //   uint8_t spare7;
  //   uint8_t spare8;
  //   uint8_t spare9;
  //   uint8_t spare10;
  //   uint8_t spare11;
  //   uint8_t spare12;
  //   uint8_t spare13;
  //   uint8_t spare14;
  //   uint8_t spare15;
  //   uint8_t spare16;
  //   uint8_t spare17;
  //   uint8_t spare18;
  //   uint8_t spare19;
  //   uint8_t spare20;
  //
  //   bool valid;
  //   };
  //
  //
  // struct configurationVariables2
  //       {
  //
  //       uint16_t AMSamplingIntervalCount;
  //       uint16_t AMIdleIntervalCount;
  //       uint8_t  AMFanOnInIdle;
  //       uint8_t  AMLaserOnInIdle;
  //       uint16_t AMMaxDataArraysInFile;
  //       uint8_t  AMOnlySavePMData;
  //
  //       bool valid;
  //       };

    struct histogramData
    {
    uint16_t binCount0  ;
    uint16_t binCount1  ;
    uint16_t binCount2  ;
    uint16_t binCount3  ;
    uint16_t binCount4  ;
    uint16_t binCount5  ;
    uint16_t binCount6  ;
    uint16_t binCount7  ;
    uint16_t binCount8  ;
    uint16_t binCount9  ;
    uint16_t binCount10 ;
    uint16_t binCount11 ;
    uint16_t binCount12 ;
    uint16_t binCount13 ;
    uint16_t binCount14 ;
    uint16_t binCount15 ;

    uint8_t bin1TimeToCross  ;
    uint8_t bin3TimeToCross  ;
    uint8_t bin5TimeToCross  ;
    uint8_t bin7TimeToCross  ;

    float sampleFlowRate ;
    uint32_t temperatureOrPressure ;
    float samplingPeriod ;

    uint16_t checkSum ;

    float pm1     ;
    float pm2_5   ;
    float pm10   ;

    bool valid;
    };

    struct pmData
    {
      float pm1    ;
      float pm2_5  ;
      float pm10   ;

      bool valid;

  };

#endif
