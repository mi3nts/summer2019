import serial
import csv
import os
from datetime import datetime

def fillDict(dict, data):
  curDat = [0] +  data.split(":")
  for key, dat in zip(dict.keys(), curDat):
      dict[key] = dat
  dict["utc-time"] = datetime.utcnow()

def makeCSV(dict, fileName):
    makeHeader = not(os.path.isfile(fileName))
    keys = list(dict.keys())
    with open(fileName, "a") as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=keys);
        if(makeHeader):
            writer.writeheader()
        writer.writerow(dict)
    csvFile.close()

def processData(data):
    print(data)
    data = data.split(">")
    if(data[0] == "#mintsO!BME280"):
        fillDict(BME280, data[1])
        makeCSV(BME280, "BME280.csv")
    if(data[0] == "#mintsO!MGS001"):
        fillDict(MGS001, data[1])
        makeCSV(MGS001, "MGS001.csv")
    if(data[0] == "#mintsO!SCD30"):
        fillDict(SCD30, data[1])
        makeCSV(SCD30, "SCD30.csv")
    if(data[0] == "#mintsO!OPCN2"):
        fillDict(OPCN2, data[1])
        makeCSV(OPCN2, "OPCN2.csv")




#Create a dictionary for each sensor's variables
BME280 = {"utc-time": 0, "temperature": 0, "pressure": 0, "humidity": 0, "altitude": 0}
MGS001 = {"utc-time": 0, "nh3": 0, "co": 0, "no2": 0, "c3h8": 0, "c4h10": 0, "ch4": 0, "h2": 0, "c2h5oh": 0}
OPCN2 = {"utc-time": 0, "valid": 0, "binCount0": 0, "binCount1": 0, "binCount2": 0, "binCount3": 0, "binCount4": 0, "binCount5": 0, "binCount6": 0, "binCount7": 0,
         "binCount8": 0, "binCount9": 0, "binCount10": 0, "binCount11": 0, "binCount12": 0, "binCount13": 0, "binCount14": 0, "binCount15": 0,
         "bin1TimeToCross": 0, "bin3TimeToCross": 0, "bin5TimeToCross": 0, "bin7TimeToCross": 0, "sampleFlowRate": 0, "temperatureOrPressure": 0, "samplingPeriod": 0, "checkSum": 0,
         "pm1": 0, "pm2_5": 0, "pm10": 0}
SCD30 = {"utc-time": 0, "co2": 0, "temperature": 0, "humidity": 0}


#Set up serial port
ser = serial.Serial("/dev/cu.usbserial-A90837L7", 9600, timeout=5)

#Read Serial setup
i = 0
while i < 182:
    print(i, ser.readline())
    i = i + 1

print("SET UP COMPLETE\nREADING DATA")

#Read data
curData = ""
while True:
    char = (ser.read(1)).decode('utf-8')
    if(char == '~'):
        processData(curData)
        curData = ""
    else:
        curData = curData + str(char)
