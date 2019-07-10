import serial
import csv
import os
from datetime import datetime

def fillDict(num, dict, data):
  curDat = [data[num].split(":")[0].split(">")[1]] +  data[num].split(":")[1:]
  for key, dat in zip(dict.keys(), curDat):
      dict[key] = dat
  dict["time"] = datetime.now()

def makeCSV(dict, fileName):
    makeHeader = not(os.path.isfile(fileName))
    keys = list(dict.keys())
    with open(fileName, "a") as csvFile:
        writer = csv.DictWriter(csvFile, fieldnames=keys);
        if(makeHeader):
            writer.writeheader()
        writer.writerow(dict)
    csvFile.close()


#Get data
file = open(r"Data.txt", "r") #Read file
contents = file.read()
#Process data
contents.replace("~", "") #Get rid of the ~ in the string
contents = contents.split("#mintsO!B") #Split the file into a list of strings for each iteration of data
del contents[0] # Get rid of empty first string

#Create a dictionary for each sensor's variables
BME280 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "time": 0}
MGS001 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "var5": 0, "var6": 0, "var7": 0, "var8": 0, "time": 0}
OPCN2 = {"var1": 0, "var2": 0, "var3": 0, "var4": 0, "var5": 0, "var6": 0, "var7": 0, "var8": 0, "var9": 0, "time": 0,
         "var10": 0, "var11": 0, "var12": 0, "var13": 0, "var14": 0, "var15": 0, "var16": 0, "var17": 0,
         "var18": 0, "var19": 0, "var20": 0, "var21": 0, "var22": 0, "var23": 0, "var24": 0, "var25": 0,
         "var26": 0, "var27": 0, "var28": 0, "time": 0}
SCD30 = {"var1": 0, "var2": 0, "var3": 0, "time": 0}

for data in contents:
    #Split vars of into sensors
    data = data.split("~#mintsO!")

    #Put variables of each sensor into the list
    fillDict(0, BME280, data)
    fillDict(1, MGS001, data)
    fillDict(2, OPCN2, data)
    fillDict(3, SCD30, data)

    #Make the csv file for each sensor
    makeCSV(BME280, "BME280.csv")
    makeCSV(MGS001, "MGS001.csv")
    makeCSV(OPCN2, "OPCN2.csv")
    makeCSV(SCD30, "SCD30.csv")
