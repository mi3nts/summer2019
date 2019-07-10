from getmac import get_mac_address

macAddress = (get_mac_address()).replace(":","")

def getDirPath(time):
      dir = "MintsData/raw/" + str(macAddress) + "/" + str(time.year) + "/" + ('%02d' % time.month) + "/" + ('%02d' % time.day)
      return dir

def getFilePath(time, dir, name):
    filePath = dir + "/" + "MINTS_" + macAddress + "_" + name + "_" + str(time.year) + "_" + ('%02d' % time.month) + "_" + ('%02d' % time.day) + ".csv"
    return filePath
