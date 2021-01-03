import sys
from SimConnect import *
from ArduinoConnect import *
from App import *

# Connecting to FS2020
try:
    sm = SimConnect()
    ae = AircraftEvents(sm)
    aq = AircraftRequests(sm, _time=300)
    print(f'[{timeNow()}] INFO: Connected to FS2020.')
except ConnectionError as e:
    print(f'[{timeNow()}] ERROR: {e}')
    sys.exit()

# Starting Web Application on thread 1
startWebApp()

# Connecting to Arduino
arduino = Controller(ae, aq)
try:
    arduino.connect()
except serial.SerialException as e:
    print(f'[{timeNow()}] ERROR: {e}')
    sys.exit()

# Handling Arduino controller on thread 2
arduino.arduinoHandler()

# Getting aircraft data on thread 3

