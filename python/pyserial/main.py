import serial

# Use ttyACM0 if it's on the Pi.
# /dev/cu.usbmodem143201
# /dev/cu.usbmodem144301
ser = serial.Serial('/dev/cu.usbmodem143201', 9600, 8, 'N', 1, timeout=1)

while True:
    s = ser.readline().decode()
    if s != "":
        print(s.split(","))
