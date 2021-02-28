import serial

ser = serial.Serial('/dev/cu.usbmodem144301', 9600, 8, 'N', 1, timeout=1)

while True:
    s = ser.readline().decode()
    if s != "":
        print(s)
