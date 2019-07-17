import serial
import csv
import os
from datetime import datetime
import serialDefinitions as fl
import json
import serial.tools.list_ports

now = datetime.utcnow()

def fillDict(dict, data):
  curDat = [0] +  data.split(":")
  for key, dat in zip(dict.keys(), curDat):
      dict[key] = dat
  dict["utc-time"] = datetime.utcnow()

def makeCSV(dict, name):
    #Find/make directory
    dir = fl.getDirPath(now)
    if(not(os.path.exists(dir))):
        os.makedirs(dir)
    #Find/make file path
    filePath = fl.getFilePath(now, dir, name)
    makeHeader = not(os.path.isfile(filePath))

    #Get keys
    keys = list(dict.keys())
    #Input data to file
    with open(filePath, "a") as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=keys);
        if(makeHeader):
            writer.writeheader()
        writer.writerow(dict)
    csvFile.close()

def processData(data):
    print(data)
    data = data.split(">")
    try:
        if(data[0] == "#mintsO!PPD42NSDuo"):
            fillDict(PPD42NSDuo, data[1])
            jsonMaker("PPD42NSDuo.json", PPD42NSDuo)
            makeCSV(PPD42NSDuo, "PPD42NSDuo")
        elif(data[0] == "#mintsO!BME280"):
            fillDict(BME280, data[1])
            jsonMaker("BME280.json", BME280)
            makeCSV(BME280, "BME280")
        elif(data[0] == "#mintsO!MGS001"):
            fillDict(MGS001, data[1])
            jsonMaker("MGS001.json", MGS001)
            makeCSV(MGS001, "MGS001")
        elif(data[0] == "#mintsO!SCD30"):
            fillDict(SCD30, data[1])
            jsonMaker("SCD30.json", SCD30)
            makeCSV(SCD30, "SCD30")
        elif(data[0] == "#mintsO!OPCN2"):
            fillDict(OPCN2, data[1])
            jsonMaker("OPCN2.json", OPCN2)
            makeCSV(OPCN2, "OPCN2")
    except:
        print("Data cannot be processed")

def jsonMaker(fileName, dict):
    with open(fileName, 'w') as f:
        json.dump(dict, f, default=str)

#Create a dictionary for each sensor's variables
BME280 = {"utc-time": 0, "temperature": 0, "pressure": 0, "humidity": 0, "altitude": 0}
MGS001 = {"utc-time": 0, "nh3": 0, "co": 0, "no2": 0, "c3h8": 0, "c4h10": 0, "ch4": 0, "h2": 0, "c2h5oh": 0}
OPCN2 = {"utc-time": 0, "valid": 0, "binCount0": 0, "binCount1": 0, "binCount2": 0, "binCount3": 0, "binCount4": 0, "binCount5": 0, "binCount6": 0, "binCount7": 0,
         "binCount8": 0, "binCount9": 0, "binCount10": 0, "binCount11": 0, "binCount12": 0, "binCount13": 0, "binCount14": 0, "binCount15": 0,
         "bin1TimeToCross": 0, "bin3TimeToCross": 0, "bin5TimeToCross": 0, "bin7TimeToCross": 0, "sampleFlowRate": 0, "temperatureOrPressure": 0, "samplingPeriod": 0, "checkSum": 0,
         "pm1": 0, "pm2_5": 0, "pm10": 0}
SCD30 = {"utc-time": 0, "co2": 0, "temperature": 0, "humidity": 0}
PPD42NSDuo = {"utc-time": 0, "sampleTimeSeconds": 0, "LPOPmMid": 0, "LPOPm10": 0, "ratioPmMid": 0, "ratioPm10": 0, "concentrationPmMid": 0, "concentrationPm2_5": 0, "concentrationPm10": 0}



#Set up serial port
li = serial.tools.list_ports.comports()
connected = []
for element in li:
    connected.append(element.device)

ser = serial.Serial(port=connected[2], baudrate=9600, timeout=5)

#Read data
curData = ""
reading = False
while True:
    try:
        char = (ser.read(1)).decode('utf-8')
        if(char == '#'):
            reading = True
            curData = str(char)
        elif(char == '~'):
            processData(curData)
            curData = ""
            reading = False
        elif(reading):
            curData = curData + str(char)
        else:
            print(str(char), end = "")
    except:
        print("Data not received")
