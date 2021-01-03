import datetime
import re
import serial
from threading import Thread

def timeNow():
    return datetime.datetime.now().strftime("%H:%M:%S")

class Controller:
    def __init__(self, ae, aq):
        self.ser = serial.Serial(timeout=10000)
        self.events = {
            'headingBug': ae.find("HEADING_BUG_SET"),
            'altitudeBug': ae.find("AP_ALT_VAR_SET_ENGLISH"),
            'IAS': ae.find("AP_SPD_VAR_SET"),
            'VS': ae.find("AP_VS_VAR_SET_ENGLISH"),
            'autopilotOn': ae.find("AUTOPILOT_ON"),
            'autopilotOff': ae.find("AUTOPILOT_OFF")
        }

    def connect(self):
        self.ser.baudrate = 9600
        self.ser.port = "COM5"
        self.ser.open()
        if self.ser.isOpen:
            print(f'[{timeNow()}] INFO: Connected to port {self.ser.port}.')

    def setHeading(self, tmp):
        hdgValue = int(re.findall("HDG: \d+", tmp)[0][5:])
        print(f'[{timeNow()}] HDG: {hdgValue}')
        self.events['headingBug'](hdgValue)

    def setAltitude(self, tmp):
        altValue = int(re.findall("ALT: \d+", tmp)[0][5:]) * 100
        print(f'[{timeNow()}] ALT: {altValue}')
        self.events['altitudeBug'](altValue)

    def setIAS(self, tmp):
        IASValue = int(re.findall("IAS: \d+", tmp)[0][5:])
        print(f'[{timeNow()}] IAS: {IASValue}')
        self.events['IAS'](IASValue)

    def setVS(self, tmp):
        VSValue = int(re.findall("VSP: \d+|VSP: -\d+", tmp)[0][5:]) * 100
        print(f'[{timeNow()}] VSP: {VSValue}')
        self.events['VS'](VSValue)

    def setAPMaster(self, tmp):
        APValue = int(re.findall("AP: \d", tmp)[0][4:])
        if APValue == 1:
            self.events['autopilotOn']()
            print(f'[{timeNow()}] AP: ON')
        else:
            self.events['autopilotOff']()
            print(f'[{timeNow()}] AP: OFF')

    def commandsHandler(self):
        while True:
            try:
                tmp = self.ser.readline().decode('utf-8')
                if "HDG" in tmp:
                    self.setHeading(tmp)
                elif "ALT" in tmp:
                    self.setAltitude(tmp)
                elif "IAS" in tmp:
                    self.setIAS(tmp)
                elif "VSP" in tmp:
                    self.setVS(tmp)
                elif "AP" in tmp:
                    self.setAPMaster(tmp)
            except:
                continue

    def arduinoHandler(self):
        Thread(target=self.commandsHandler).start()