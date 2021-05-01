import csv
from time import time

import serial

# Use ttyACM0 if it's on the Pi.
# /dev/cu.usbmodem143201
# /dev/cu.usbmodem144301
# usbmodem144201
ser = serial.Serial('/dev/cu.usbmodem141301', timeout=1)

f = open("df.csv", "a+")
writer = csv.writer(f, delimiter=',')

while True:
    s = ser.readline().decode()
    if s != "":
        rows = [float(x) for x in s.split(',')]
        # Insert local time to list's first position
        rows.insert(0, int(time()))
        print(rows)
        writer.writerow(rows)
        f.flush()
