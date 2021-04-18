import serial
from time import time

# Use ttyACM0 if it's on the Pi.
# /dev/cu.usbmodem143201
# /dev/cu.usbmodem144301
# usbmodem144201
ser = serial.Serial('/dev/cu.usbmodem141201', 9600, 8, 'N', 1, timeout=1)

while True:
    s = ser.readline().decode()
    if s != "":
        rows = [float(x) for x in s.split(',')]
        # Insert local time to list's first position
        rows.insert(0, int(time()))
        print(rows)
