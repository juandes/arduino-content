import serial

# Use ttyACM0 if it's on the Pi.
<<<<<<< Updated upstream
<<<<<<< Updated upstream
# /dev/cu.usbmodem143201
# /dev/cu.usbmodem144301
# usbmodem144201
ser = serial.Serial('/dev/cu.usbmodem143201', 9600, 8, 'N', 1, timeout=1)
=======
ser = serial.Serial('/dev/cu.usbmodem144201', 9600, 8, 'N', 1, timeout=1)
>>>>>>> Stashed changes
=======
ser = serial.Serial('/dev/cu.usbmodem144201', 9600, 8, 'N', 1, timeout=1)
>>>>>>> Stashed changes

while True:
    s = ser.readline().decode()
    if s != "":
        print(s.split(","))
