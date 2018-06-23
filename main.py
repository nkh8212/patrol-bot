import serial

ser = serial.Serial("/dev/tty.usbmodem1411", 9600)

while True:
    op = input("insert op :")
    ser.write(op.encode())
    #print(ser.readline())
    #ser.close()
